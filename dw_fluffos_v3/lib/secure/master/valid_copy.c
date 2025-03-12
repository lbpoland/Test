int valid_copy(string path, mixed euid, string func) {
  object master_ob;
  string *bits = explode(path, "/") - ({ "", "." });
  mapping perms;
  perms = permission_match_path(permissions, path);
  if(sizeof(bits) < 2 || bits[0] == "open" || bits[0] == "doc" ||
     bits[0] == "log" || bits[0] == "mudlib" || bits[0] == "w")
    return check_permission(euid, func, path, perms, READ_MASK);
  master_ob = find_object("/d/" + bits[1] + "/master");
  if((master_ob && master_ob->copy_with_read(path, euid, func)) ||
     (!master_ob && master()->query_senior(euid)))
    return check_permission(euid, func, path, perms, READ_MASK);
  else
    return check_permission(euid, func, path, perms, WRITE_MASK);
}