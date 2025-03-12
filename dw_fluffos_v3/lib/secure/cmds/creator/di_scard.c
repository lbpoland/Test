#include <creator.h>
inherit "/cmds/base";
void ask_discard(object *obs);
mixed cmd(string str) {
  string *file_names, err;
  object *no_dis, discard_obj;
  file_names = this_player()->get_cfiles(str);
  no_dis = ({ });
  if (!sizeof(file_names)) {
    add_failed_mess("No such object: " + str + "\n");
    return 0;
  }
  foreach (str in file_names) {
    discard_obj = find_object(str);
    if (!discard_obj) {
      printf("%s is not loaded.\n", str);
      continue;
    }
    err = catch(discard_obj->dest_me());
    this_player()->handle_error(err, "dest_me");
    if (discard_obj) {
      no_dis += ({ discard_obj });
    }
  }
  if (sizeof(no_dis)) {
    ask_discard(no_dis);
    return 1;
  }
  write("Ok.\n");
  return 1;
}
void ask_discard(object *obs) {
  if (!arrayp(obs) || !sizeof(obs)) {
    printf("Nothing left to be discarded.\n");
    return;
  }
  printf("%s has a violent objection to being dested.\n"
         "Are you sure you want to do this? ",
         WIZ_PRESENT->desc_object(obs[0]));
  input_to("no_discard", 0, obs);
}
void no_discard(string s, object *obs) {
   string err, name;
   name = (string)WIZ_PRESENT->desc_object(obs[0]);
   if (this_player()->affirmative(s)) {
      err = catch(obs[0]->dwep());
      this_player()->handle_error(err, "DWEP");
      if (obs[0]) {
         printf("%s REALLY doesn't want to be discarded.\n", name);
         catch(destruct(obs[0]));
         if (obs[0]) {
            printf("%s didn't destruct.\n", name);
            return;
         }
      }
   }
   printf("%s discarded.\n", name);
   ask_discard(obs[1..]);
}
mixed* query_patterns() {
   return ({ "<string>", (: cmd($4[0]) :) });
}