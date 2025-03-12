#include <creator.h>
private nosave mapping obvar;
void create() {
   obvar = ([ ]);
}
protected void wiz_commands() {
}
int affirmative(string s)
{
    s = lower_case(s);
    return (s == "y" || s == "yes" || s == "ok" || s == "please");
}
void handle_error(string erm, string desc) {
    if (erm) {
         write(desc + " failed : " + erm);
    }
}
void set_obvar(string key, object value) {
  obvar[key] = value;
}
void del_obvar(string key) {
  map_delete(obvar, key);
}
object get_obvar(string key) {
  return obvar[key];
}
mapping get_obvars() {
  return obvar;
}
string desc_object(mixed o) {
  log_file("WIZ_PRESENT", sprintf("desc_object() called by %O.\n",
      previous_object()));
  return "";
}
string desc_f_object(mixed o) {
  log_file("WIZ_PRESENT", sprintf("desc_f_object() called by %O.\n",
      previous_object()));
  return "";
}
object *wiz_present(string str, object onobj, int nogoout) {
  log_file("WIZ_PRESENT", sprintf("wiz_present() called by %O.\n",
      previous_object()));
  return ({});
}