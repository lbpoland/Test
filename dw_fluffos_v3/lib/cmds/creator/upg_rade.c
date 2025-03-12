mixed cmd(string str) {
  seteuid(geteuid(this_player()));
  (clone_object("/secure/login"))->do_upgrade(this_player());
  return 1;
}
void dest_me() {
  destruct(this_object());
}
void clean_up() {
  dest_me();
}
void reset() {
  dest_me();
}