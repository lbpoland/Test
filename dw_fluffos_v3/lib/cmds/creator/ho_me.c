mixed cmd(string str) {
  write("Usage : alias home goto <wherever> :)\n");
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