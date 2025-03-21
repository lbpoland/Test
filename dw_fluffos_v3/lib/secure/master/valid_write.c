#define WRITE_FILE_STATS 1
private nosave mapping write_stats;
int valid_write(string path, mixed euid, string func) {
  mapping perms;
  string tmp;
  string *bits, rcspath;
  string prev;
  if (path && (path[<2..] == ",v")) {
    return 0;
  }
  if (func == "remove_file" && path[0..13] == "/save/players/") {
     if (objectp(euid)) {
        log_file("/d/admin/log/DELETE_PLAYER", "Deleting " +
                path + " by " + file_name(previous_object()) +
                "->" + call_stack(2)[0] + "\n");
     } else {
        log_file("/d/admin/log/DELETE_PLAYER", "Deleting " +
                path + " by " + euid + " (" + file_name(previous_object()) +
                "->" + call_stack(2)[0] + ")\n");
     }
  }
  if (euid == master())
    return 1;
  if (path[0] != '/')
    path = "/" + path;
#ifdef WRITE_FILE_STATS
  if(!write_stats)
    write_stats = ([ ]);
  if(previous_object()) {
    prev = base_name(previous_object());
    if(!write_stats[prev])
      write_stats[prev] = ([ path : 1 ]);
    else
      write_stats[prev][path] += 1;
  }
#endif
  bits = explode(path, "/");
  if(euid &&
     (file_size(path) > 0) &&
     (!previous_object() ||
        file_name(previous_object()) != "/secure/cmds/creator/rcso_ut") &&
     (!objectp(euid) || file_name(euid) != "/secure/ftpd") &&
     path[<2..] != ".o" &&
     (bits[0] != "log" && bits[0] != "save" && bits[0] != "players") ) {
    if(sizeof(bits) > 2) {
      rcspath = "/" + implode(bits[0..sizeof(bits)-2], "/") + "/RCS/";
    } else if(sizeof(bits) == 2) {
      rcspath = "/" + bits[0] + "/RCS/";
    } else
      rcspath = "/";
    rcspath += bits[sizeof(bits)-1] + ",v";
    if(file_size(rcspath) > 0) {
#ifdef DEBUG
      if(stringp(euid))
        tell_object(find_player("ceres"), sprintf("Checking perms: %s [%s](string)\n", rcspath, euid ));
      else if(objectp(euid))
        tell_object(find_player("ceres"), sprintf("Checking perms: %s [%s](object)\n", rcspath, file_name(euid )));
      else
        tell_object(find_player("ceres"), sprintf("Checking perms: %s [%O](unknown)\n", rcspath, euid ));
#endif
      tmp = read_file(rcspath, 4, 1);
      if(tmp == "locks\n") {
        string lockname ;
        tmp = read_file(rcspath, 5, 1);
        sscanf(tmp, "\t%s:", lockname);
        if((objectp(euid) && euid->query_name() != lockname) ||
           (stringp(euid) && euid != lockname)) {
          int i, ok;
          object *stack;
          stack = previous_object(-1);
          i = sizeof(stack);
          while(--i) {
            if(geteuid(stack[i]) == lockname) {
              ok = 1;
            }
          }
          if(!ok) {
#ifdef DEBUG
          if(objectp(euid))
            tell_object(find_player("ceres"), sprintf("Write denied to %O or %O Locked by %s\n", euid, previous_object(-1), lockname));
          else
            tell_object(find_player("ceres"), sprintf("Write denied to %s or %O Locked by %s\n", euid, previous_object(-1), lockname));
#endif
          return 0;
          } else {
#ifdef DEBUG
            tell_object(find_player("ceres"), "Write allowed to "+geteuid(stack[i])+" Locked by:"+lockname +" on file "+path+"\n");
#endif
          }
        } else {
#ifdef DEBUG
          if(objectp(euid))
            tell_object(find_player("ceres"), sprintf("Write allowed by %O Locked by %s\n", euid, lockname));
          else
            tell_object(find_player("ceres"), sprintf("Write allowed by %s Locked by %s\n", euid, lockname));
#endif
        }
      } else {
#ifdef DEBUG
          tell_object(find_player("ceres"), "No locks found\n");
#endif
          return 0;
      }
    }
  }
  perms = permission_match_path(permissions, path);
  return check_permission(euid, func, path, perms, WRITE_MASK);
}
mapping query_write_stats() { return copy(write_stats); }
void reset() {
  write_stats = ([ ]);
  read_stats = ([ ]);
}