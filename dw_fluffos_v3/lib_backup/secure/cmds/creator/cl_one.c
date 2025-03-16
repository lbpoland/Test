#include <creator.h>
inherit "/cmds/base";
mixed cmd(string str) {
    object ob;
    string err, *filenames, obvarname;
    int loop, mov;
    if (!str) {
        notify_fail("Clone what ?\n");
        return 0;
    }
    obvarname = (string)0;
    sscanf(str, "%s=%s", obvarname, str);
    filenames = this_player()->get_cfiles(str);
    if (!sizeof(filenames))  {
        notify_fail("No such file.\n");
        return 0;
    }
    for(loop = 0; loop < sizeof(filenames); loop++) {
       str = filenames[loop];
       if (file_size(str) < 0 && file_size(str + ".c") < 0) {
          notify_fail("No such file.\n");
          return 0;
       }
       ob = clone_object(str);
       if (obvarname) this_player()->set_obvar(obvarname, ob);
       if (ob) {
          err = catch((mov = (int)ob->move(this_player())));
          this_player()->handle_error(err, "move(this_player())");
          if (err || mov) {
             err = catch(ob -> move(environment(this_player())));
             this_player()->handle_error(err, "move(environment())");
          }
          printf("Ok.  Object %O cloned and put in "+
             (environment(ob)==this_player() ? "you" :
              (environment(ob)==environment(this_player()) ? "here" : WIZ_PRESENT->desc_object(environment(ob))))+
             ".\n", ob);
          say((string)this_player()->query_cap_name() + " fetches " +
            (string)ob->one_short() + " from another dimension.\n");
       } else {
          printf("Failed to clone.\n");
       }
    }
    return 1;
}