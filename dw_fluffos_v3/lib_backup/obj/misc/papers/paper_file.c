inherit "/obj/misc/paper";
string file_name;
void create() {
  seteuid(getuid());
  ::create();
}
void set_file_name(string fname) {
  file_name = fname;
}
string query_file_name() {
  return file_name;
}
mixed *query_read_mess() {
  return read_file(file_name);
}
void init() {
  this_player()->add_command("read", this_object());
  ::init();
}