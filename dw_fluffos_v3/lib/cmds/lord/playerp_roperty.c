#include <parser.h>
#include <player_handler.h>
inherit "/cmds/base";
mapping map_prop;
mixed cmd(string str) {
   string name;
   string value;
   string player;
   mixed *args;
   if (!str) {
      return notify_fail("You must give a property...\n");
   }
   if (sscanf(str, "%s \"%s\" %s", player, name, value) == 3) {
      seteuid("Root");
      unguarded( (: restore_object("/players/" + $(player[0..0]) +
                                   "/" + $(player)) :));
      if (PLAYER_HANDLER->test_user(player)) {
         args = PARSER->parse_args(value);
         if (args && sizeof(args[0]) > 0) {
            map_prop[name] = args[0][0];
            unguarded( (: write_file("/players/" + $(player[0..0]) +
                               "/" + $(player) + ".o",
                       "map_prop "+save_variable(map_prop)+"\n") :));
            write(sprintf("Added property %s to %s; value = %O\n",
                          name, player, args[0][0]));
         } else {
            write("No useful args...\n");
         }
      } else {
         write("Unable to find player "+player+".\n");
      }
   } else {
      write("Syntax: player_add_property <name> \"<prop>\" <value>\n");
   }
   return 1;
}