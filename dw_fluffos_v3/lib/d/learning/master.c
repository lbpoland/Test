#define LORD "taffyd"
#define DOMAIN "learning"
inherit "/std/dom/base_master";
string info = "";
string query_lord() {
  return LORD;
}
string author_file(string *path) {
  return capitalize(DOMAIN);
}
int check_permission(string euid, string *path, int mask) {
  if (euid == query_lord())
    return 1;
  return ::check_permission(euid, path, mask);
}
int copy_with_read(string path, string euid, string func) {
  return 1;
}
int add_member(string name) {
  if (geteuid(this_player(1)) != query_lord())
    return 0;
  return ::add_member(name);
}
int remove_member(string name) {
  if (geteuid(this_player(1)) != query_lord())
    return 0;
  return ::remove_member(name);
}
int set_project(string name, string pro) {
  if (geteuid(this_player(1)) != query_lord())
    return 0;
  return ::set_project(name, pro);
}
int query_member(string name) {
  return !undefinedp(members[name]) || name == LORD;
}
string log_who(string where) {
   return LORD;
}
void set_info( string words ) {
  info = words;
  save_me();
}
string query_info() {
  return info;
}