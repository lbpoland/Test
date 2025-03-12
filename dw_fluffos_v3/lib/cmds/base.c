void create() {
  seteuid(getuid(this_object()));
}
void dest_me() {
  if(this_object())
    destruct(this_object());
}
int clean_up() {
  dest_me();
  return 1;
}
void reset() {
  dest_me();
}