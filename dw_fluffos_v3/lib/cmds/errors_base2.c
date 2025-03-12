#include <db.h>
#include <log.h>
#include <config.h>
private class report {
  int row;
  string newstatus;
  string newdir;
  string newtype;
  int changed;
}
private class bugs {
  mixed* errors;
  string user;
  int changed;
}
private nosave mapping _globvars;
protected varargs mixed get_row(mixed key, int row, int nomap);
protected varargs string init_errors(mixed key, string user, int replace) {
  string ret;
  if (!mapp(_globvars)) {
    _globvars = ([ ]);
  } else {
    if (!(replace || undefinedp(_globvars[key]))) {
      return "key already in use";
    }
  }
  _globvars[key] = new(class bugs);
  _globvars[key]->user = user;
  _globvars[key]->errors = ([ ]);
  return 0;
}
protected string finish_errors(mixed key) {
  string ret;
  if (!classp(_globvars[key])) {
    return "unknown key";
  }
  map_delete(_globvars, key);
  return ret;
}
void event_finished_get_fields(string key) {
}
private void finished_get_fields(mixed key, int type, mixed* data) {
   _globvars[key]->errors = data;
   event_finished_get_fields(key);
}
protected void get_fields(mixed key, string directory,
                          string fields, string type) {
  string query;
  string temp;
  mixed ret;
  if (!strlen(type)) {
    type = "OPEN";
  }
  _globvars[key]->errors = ({ });
  fields += ", Directory";
  query = sprintf("SELECT %s FROM errors WHERE Directory = '%s' AND "
                  "Status = '%s' ORDER BY DirEntryDate;", fields, directory,
                  type);
  MYSQL_HANDLER->make_sql_request("errors", USER, "", query,
                                  (: finished_get_fields($(key), $1, $2) :));
}
void event_finish_get_forwards(mixed key, int row) {
}
protected void finish_get_forwards(mixed key, int row, int type, mixed* data) {
   _globvars[key]->forwards[row] = data;
   event_finish_get_forwards(key, row);
}
protected void get_forwards(mixed key, int row) {
  string query, err;
  mixed ret;
  mapping forwards;
  ret = _globvars[key]->errors[row];
  if (_globvars[key]->forwards[row]) {
     return _globvars[key]->forwards[row];
  }
  query = sprintf("SELECT ForwardDate, Forwarder, OldDirectory FROM forwards "
                  "WHERE Id = %d ORDER BY ForwardDate;", ret["Id"]);
  MYSQL_HANDLER->make_sql_request("errors", USER, "", query,
                                  (: finished_get_forwards($(key), $(row),
                                     $1, $2) :));
}
void event_finish_get_comments(mixed key, int row) {
}
protected void finish_get_comments(mixed key, int row, int type, mixed* data) {
   _globvars[key]->comments[row] = data;
   event_finish_get_comments(key, row);
}
protected void get_comments(mixed key, int row) {
  string query, err;
  mixed ret;
  mapping comments;
  int fd;
  ret = _globvars[key]->errors[row];
  if (_globvars[key]->comments[row]) {
     return _globvars[key]->comments[row];
  }
  query = sprintf("SELECT CommentDate, Commenter, Comment FROM comments "
                  "WHERE Id = %d ORDER BY CommentDate;", ret["Id"]);
  MYSQL_HANDLER->make_sql_request("errors", USER, "", query,
                                  (: finished_get_comments($(key), $(row),
                                     $1, $2) :));
}
protected void get_row(mixed key, int row) {
  mixed *res;
  string ret, *keys;
  mapping rowvals;
  return _globvars[key]->errors[row];
}
protected int set_status(mixed key, int row, string status) {
  int realrow = ROWS[row];
  if (!classp(_globvars[key]->changes[row])) {
    _globvars[key]->changes[row] = new(class _report, row : realrow);
  }
  _globvars[key]->changes[row]->newstatus = status;
  _globvars[key]->changes[row]->changed = 1;
  return 1;
}
protected int set_type(mixed key, int row, string type) {
  if (!classp(_globvars[key]->changes[row])) {
    _globvars[key]->changes[row] = new(class _report, row : realrow);
  }
  _globvars[key]->changes[row]->newtype = status;
  _globvars[key]->changes[row]->changed = 1;
  return 1;
}
protected int forward_bug(mixed key, int row, string directory) {
  int realrow = ROWS[row];
  while (directory[<1] == '/') {
    directory = directory[0..<2];
  }
  if (!classp(_globvars[key]->changes[row])) {
    _globvars[key]->changes[row] = new(class _report, row : realrow);
  }
  _globvars[key]->changes[row]->newdir = directory;
  _globvars[key]->changes[row]->changed = 1;
  return 1;
}
protected string comment_bug(mixed key, int row, string who, string comment) {
  string query, err;
  int fd;
  mixed ret;
  query = sprintf("INSERT LOW_PRIORITY INTO comments VALUES "
                  "(%d, %d, '%s', '%s');",
                  ret["Id"], time(), who, comment);
  MYSQL_HANDLER->make_sql_request("errors", USER, "", query);
  return 0;
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
    MYSQL_HANDLER->make_sql_request("errors", USER, "", query);
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