mixed cmd(string str) {
   seteuid(geteuid(this_player()));
   if (!str || str == "") {
      notify_fail("Make what directory?\n");
      return 0;
      }
   str = this_player()->get_path(str);
   str = replace(str, " ", "_");
   if (!str)
      return 1;
   if (file_size(str) != -1) {
      notify_fail(str + " already exists.\n");
      return 0;
      }
   if (!mkdir(str)) {
      notify_fail("Couldn't make dir.\n");
      return 0;
   }
   write("Ok.\n");
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