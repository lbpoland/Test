int save_ed_setup(object wiz, int setup) {
  wiz->set_ed_setup(setup);
  return 1;
}
int retrieve_ed_setup(object wiz) {
  return (int)wiz->query_ed_setup();
}
string make_path_absolute(string str) {
  if (this_player()) {
    return (string)this_player()->get_path(str);
  }
}
string get_save_file_name(string file, object who) {
  string *file_ar;
  if (!objectp(who))
    return 0;
  file_ar = explode(file,"/") - ({ "" });
  file = file_ar[<1];
  write("File saved in \"/w/.dead_ed_files/" +
        who->query_name() + "-" + file + "\"\n");
  return "/w/.dead_ed_files/" + who->query_name() + "-" + file;
}