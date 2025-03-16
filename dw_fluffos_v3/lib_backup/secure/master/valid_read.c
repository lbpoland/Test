#define FILE_STATS 1
private nosave mapping read_stats;
int valid_read(string path, mixed euid, string func) {
  mapping perms;
  string prev;
  if (euid == master())
    return 1;
  if ((func == "file_size") || (func == "stat"))
    return 1;
  if (path[0] != '/')
    path = "/" + path;
  if (path[<1] == 'c' && base_name(euid)[0..2] == "/w/")
    return 0;
#ifdef FILE_STATS
  if(!read_stats)
    read_stats = ([ ]);
  if(previous_object()) {
    prev = base_name(previous_object());
    if(!read_stats[prev])
      read_stats[prev] = ([ path : 1 ]);
    else
      read_stats[prev][path] += 1;
  }
#endif
  perms = (mapping)permission_match_path(permissions, path);
  return check_permission(euid, func, path, perms, READ_MASK);
}
mapping query_read_stats() { return copy(read_stats); }