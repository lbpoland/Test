#define LORD "pinkfish"
#define DOMAIN "dist"
inherit "/std/dom/base_master";
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
int valid_read(string *path, string euid, string funct);
int valid_write(string *path, string euid, string funct);
int query_member(string name) {
  return !undefinedp(members[name]) || name == LORD;
}
string log_who(string where) {
  return LORD;
}
string query_info() {
  return "";
}