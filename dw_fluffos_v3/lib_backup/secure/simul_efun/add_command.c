varargs void add_command(string verb, string pattern, function func) {
   if (!verb) {
      write("Need to specify a verb for add_command.\n");
      return ;
   }
   if (!pattern) {
      write("Need to specify a pattern for add_command.\n");
   }
   if (this_player()) {
      this_player()->add_command(verb, previous_object(), pattern, func);
   }
}
void add_succeeded_mess(mixed mess, object *indir) {
   if (!indir) {
     indir = ({ });
   }
   this_player()->add_succeeded_mess(previous_object(), mess, indir);
}
void add_succeeded_ob(object ob) {
   this_player()->add_succeeded(ob);
}
void add_failed_mess(mixed mess, object *indir) {
   if (!indir) {
     indir = ({ });
   }
   this_player()->add_failed_mess(previous_object(), mess, indir);
}