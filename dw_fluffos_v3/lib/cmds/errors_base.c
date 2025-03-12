#include <db.h>
#include <log.h>
#include <config.h>
private class _report {
  int row;
  string newstatus;
  string newdir;
  string newtype;
  int changed;
}
private class _bugs {
  int fd;
  mapping errors;
  int *rows;
  string *fieldnames;
  int changed;
}
#define FD ((class _bugs)globvars[key])->fd
#define ERRORS ((class _bugs)globvars[key])->errors
#define ROWS ((class _bugs)globvars[key])->rows
#define FIELDNAMES ((class _bugs)globvars[key])->fieldnames
#define CHANGED ((class _bugs)globvars[key])->changed
private nosave mapping globvars;
protected varargs mixed get_row(mixed key, int row, int nomap);
protected varargs string init_errors(mixed key, string user, int replace) {
  string ret;
  if (!mapp(globvars)) {
    globvars = ([ ]);
  } else {
    if (!(replace || undefinedp(globvars[key]))) {
      return "key already in use";
    }
    if (globvars[key]) {
      catch(db_close(FD));
    }
  }
  globvars[key] = new(class _bugs);
  if ((ret = catch(FD = db_connect("localhost", "errors", user)))) {
    map_delete(globvars, key);
    return ret;
  }
  return 0;
}
protected string finish_errors(mixed key) {
  string ret;
  if (!classp(globvars[key])) {
    return "unknown key";
  }
  ret = catch(db_close(FD));
  map_delete(globvars, key);
  return ret;
}
protected varargs mixed sql_query(mixed key, string query, mixed *args ...) {
  string error;
  mixed ret;
  ERRORS = 0;
  ROWS = 0;
  FIELDNAMES = 0;
  error = catch(ret = db_exec(FD, query, args ...));
  if (error) {
    return error;
  }
  if (stringp(ret)) {
    return ret;
  }
  if (ret) {
    ROWS = allocate(ret + 1, (: $1 :));
  }
  return ret;
}
protected varargs mixed get_fields(mixed key, string directory,
                                   string fields, string type) {
  string query, temp;
  mixed ret;
  if (!strlen(type)) {
    type = "OPEN";
  }
  ERRORS = 0;
  ROWS = 0;
  FIELDNAMES = 0;
  fields += ", Directory";
  query = sprintf("SELECT %s FROM errors WHERE Directory = '%s' AND "
                  "Status = '%s' ORDER BY DirEntryDate;", fields, directory,
                  type);
  temp = catch(ret = db_exec(FD, query));
  if (temp) {
    return temp;
  }
  if (stringp(ret)) {
    return ret;
  }
  if (ret) {
    ROWS = allocate(ret + 1, (: $1 :));
  }
  return ret;
}
protected mixed get_forwards(mixed key, int row) {
  string query, err;
  mixed ret;
  mapping forwards;
  int fd;
  ret = get_row(key, row);
  if (stringp(ret)) {
    return ret;
  }
  err = catch(fd = db_connect("localhost", "errors", CONFIG_DB_USER));
  if (err) {
    return err;
  }
  query = sprintf("SELECT ForwardDate, Forwarder, OldDirectory FROM forwards "
                  "WHERE Id = %d ORDER BY ForwardDate;", ret["Id"]);
  err = catch(ret = db_exec(fd, query));
  if (err) {
    catch(db_close(fd));
    return err;
  }
  if (stringp(ret)) {
    catch(db_close(fd));
    return ret;
  }
  if (ret) {
    err = catch {
      int *dates, i;
      string *forwarders, *dirs;
      mixed *vals;
      dates = allocate(ret);
      forwarders = allocate(ret);
      dirs = allocate(ret);
      for (i = 0; i < ret; i++) {
        vals = db_fetch(fd, i + 1);
        dates[i] = vals[0];
        forwarders[i] = vals[1];
        dirs[i] = vals[2];
      }
      forwards = allocate_mapping(3);
      forwards["ForwardDate"] = dates;
      forwards["Forwarder"] = forwarders;
      forwards["OldDirectory"] = dirs;
    };
    if (err) {
      catch(db_close(fd));
      return err;
    }
  }
  catch(db_close(fd));
  return forwards;
}
protected mixed get_comments(mixed key, int row) {
  string query, err;
  mixed ret;
  mapping comments;
  int fd;
  ret = get_row(key, row);
  if (stringp(ret)) {
    return ret;
  }
  err = catch(fd = db_connect("localhost", "errors", CONFIG_DB_USER));
  if (err) {
    return err;
  }
  query = sprintf("SELECT CommentDate, Commenter, Comment FROM comments "
                  "WHERE Id = %d ORDER BY CommentDate;", ret["Id"]);
  err = catch(ret = db_exec(fd, query));
  if (err) {
    catch(db_close(fd));
    return err;
  }
  if (stringp(ret)) {
    catch(db_close(fd));
    return ret;
  }
  if (ret) {
    err = catch {
      int *dates, i;
      string *commenters, *texts;
      mixed *vals;
      dates = allocate(ret);
      commenters = allocate(ret);
      texts = allocate(ret);
      for (i = 0; i < ret; i++) {
        vals = db_fetch(fd, i + 1);
        dates[i] = vals[0];
        commenters[i] = vals[1];
        texts[i] = vals[2];
      }
      comments = allocate_mapping(3);
      comments["CommentDate"] = dates;
      comments["Commenter"] = commenters;
      comments["Comment"] = texts;
    };
    if (err) {
      catch(db_close(fd));
      return err;
    }
  }
  catch(db_close(fd));
  return comments;
}
protected varargs mixed get_row(mixed key, int row, int nomap) {
  mixed *res;
  string ret, *keys;
  mapping rowvals;
  if (!arrayp(FIELDNAMES)) {
    ret = catch(res = db_fetch(FD, 0));
    if (ret)
      return ret;
    keys = res;
    FIELDNAMES = res;
  } else {
    keys = FIELDNAMES;
  }
  if (!nomap) {
    row = ROWS[row];
  }
  ret = catch(res = db_fetch(FD, row));
  if (ret)
    return ret;
  if (sizeof(keys) != sizeof(res)) {
    return "Database engine lost results(?)\n";
  }
  rowvals = allocate_mapping(keys, res);
  return rowvals;
}
protected int set_status(mixed key, int row, string status) {
  int realrow = ROWS[row];
  if (!mapp(ERRORS))
    ERRORS = ([ ]);
  if (!classp(ERRORS[realrow])) {
    ERRORS[realrow] = new(class _report, row : realrow);
  }
  ((class _report)ERRORS[realrow])->newstatus = status;
  ((class _report)ERRORS[realrow])->changed = 1;
  ROWS = delete(ROWS, row, 1);
  CHANGED = 1;
  return 1;
}
protected int set_type(mixed key, int row, string type) {
  if (!mapp(ERRORS))
    ERRORS = ([ ]);
  row = ROWS[row];
  if (!classp(ERRORS[row])) {
    ERRORS[row] = new(class _report, row : row);
  }
  ((class _report)ERRORS[row])->newtype = type;
  ((class _report)ERRORS[row])->changed = 1;
  CHANGED = 1;
  return 1;
}
protected int forward_bug(mixed key, int row, string directory) {
  int realrow = ROWS[row];
  if (!mapp(ERRORS))
    ERRORS = ([ ]);
  if (!classp(ERRORS[realrow])) {
    ERRORS[realrow] = new(class _report, row : realrow);
  }
  while (directory[<1] == '/') {
    directory = directory[0..<2];
  }
  ((class _report)ERRORS[realrow])->newdir = directory;
  ((class _report)ERRORS[realrow])->changed = 1;
  ROWS = delete(ROWS, row, 1);
  CHANGED = 1;
  return 1;
}
protected string comment_bug(mixed key, int row, string who, string comment) {
  string query, err;
  int fd;
  mixed ret;
  ret = get_row(key, row);
  if (stringp(ret)) {
    return ret;
  }
  err = catch(fd = db_connect("localhost", "errors", CONFIG_DB_USER));
  if (err) {
    return err;
  }
  comment = db_escape(comment);
  query = sprintf("INSERT LOW_PRIORITY INTO comments VALUES "
                  "(%d, %d, '%s', '%s');",
                  ret["Id"], time(), who, comment);
  err = catch(ret = db_exec(fd, query));
  if (stringp(ret)) {
    err = ret;
  }
  catch(db_close(fd));
  return err;
}
private string save_status(mixed key, int *ids, string user, string status) {
  string query, ret, err;
  mixed res;
  ret = "";
  if (sizeof(ids)) {
    if (sizeof(ids) == 1) {
      query = sprintf("UPDATE LOW_PRIORITY errors SET Status = '%s', "
                      "FixDate = %d, Fixer = '%s' WHERE Id = %d;", status,
                      time(), user, ids[0]);
    } else {
      query = sprintf("UPDATE LOW_PRIORITY errors SET Status = '%s', "
                      "FixDate = %d, Fixer = '%s' WHERE Id IN (%s);", status,
                      time(), user, implode(ids, (: "" + $1 + ", " + $2 :)));
    }
    err = catch(res = db_exec(FD, query));
    if (err) {
      ret += err;
    }
    if (stringp(res)) {
      ret += res;
    }
  }
  return ret;
}
protected string save_changes(mixed key, string user) {
  class _report *reports, report;
  string query, *queries, ret, err;
  int *ids_fixed, *ids_denied, *ids_fixing, *ids_considering, *ids_open, ftime;
  mixed res, row;
  if (!CHANGED) {
    return 0;
  }
  reports = filter(values(ERRORS), (: ((class _report)$1)->changed :));
  ids_fixed = ids_denied = ids_fixing = ids_considering = ids_open = queries = ({ });
  ret = "";
  foreach (report in reports) {
    row = get_row(key, report->row, 1);
    if (stringp(row)) {
      ret += row;
      continue;
    }
    switch (report->newstatus) {
    case "FIXED":
      ids_fixed += ({ row["Id"] });
      break;
    case "DENIED":
      ids_denied += ({ row["Id"] });
      break;
    case "FIXING":
      ids_fixing += ({ row["Id"] });
      break;
    case "CONSIDERING":
      ids_considering += ({ row["Id"] });
      break;
    case "OPEN":
      ids_open += ({ row["Id"] });
      break;
    case 0:
    case "":
      if (report->newdir) {
        ftime = time();
        query = sprintf("UPDATE LOW_PRIORITY errors SET Directory = '%s', "
                        "DirEntryDate = %d WHERE Id = %d;",
                        report->newdir, ftime, row["Id"]);
        queries += ({ query });
        query = sprintf("INSERT LOW_PRIORITY INTO forwards VALUES "
                        "(%d, %d, '%s', '%s');",
                        row["Id"], ftime, user, row["Directory"]);
        queries += ({ query });
      }
      if (report->newtype) {
        query = sprintf("UPDATE LOW_PRIORITY errors SET Type = '%s' "
                        "WHERE Id = %d;", report->newtype, row["Id"]);
        queries += ({ query });
      }
      break;
    default:
      ret += sprintf("Unknown report status: %s\n", report->newstatus);
      break;
    }
  }
  ret += save_status(key, ids_fixed, user, "FIXED");
  ret += save_status(key, ids_denied, user, "DENIED");
  ret += save_status(key, ids_fixing, user, "FIXING");
  ret += save_status(key, ids_considering, user, "CONSIDERING");
  ret += save_status(key, ids_open, user, "OPEN" );
  foreach (query in queries) {
    err = catch(db_exec(FD, query));
    if (err) {
      ret += err;
    }
    if (stringp(res)) {
      ret += res;
    }
  }
  if (ret == "") {
    ret = 0;
  }
  return ret;
}