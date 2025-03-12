mixed cmd(string str) {
  int i;
  string *files;
  seteuid(geteuid(this_player()));
  if (!str)
    return notify_fail("Usage: head <file>\n");
  files = this_player()->get_files(str);
  if (!sizeof(files))
    return notify_fail("File does not exist.\n");
  str = files[0];
  i = file_length(str);
  if (i < 0) {
    printf("File not found.\n");
    return 1;
  }
  if (i > 20) i=20;
  write(read_file(str,1,i));
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