#include <player.h>
#include <clothing.h>
inherit "/cmds/base";
#define TP this_player()
int use_count = 0;
private string _zone_str;
void create() {
   string zone;
   _zone_str = "face|hair";
   foreach (zone in keys(CLOTHING_HANDLER->query_all_clothing_zones())) {
      _zone_str += "|" + zone;
   }
}
int cmd(string str) {
   string desc;
   string zone;
   desc = TP->query_desc();
   if (!str) {
      if (desc) {
         write("Description reads:\n" + TP->query_cap_name() + " " +
               desc + "\n");
      } else {
         write("No description set.\n");
      }
      if (sizeof(TP->query_zone_desc_names())) {
         foreach (zone in TP->query_zone_desc_names()) {
            write("$I$5=$C$" + zone + ": " + TP->query_zone_desc(zone) + "\n");
         }
         if (!desc) {
            write("%^YELLOW%^Warning! Your zone descriptions will not be "
                  "displayed unless you also have a main description.%^RESET%^\n");
         } else {
            write("Each zone description is a sentence, or multiple "
                  "sentences.  If you do not do this then the descriptions "
                  "will look wrong.\n");
         }
      } else {
         write("No zone descriptions setup.\n");
      }
      return 1;
   }
   else if (str == "clear") {
      write("Description cleared.\n");
      TP->set_desc(0);
      return 1;
   }
   else if (str == "edit") {
     if (desc) {
         this_player()->do_edit(sprintf("%-=*s", this_player()->query_cols(),
                                        this_player()->query_cap_name() + " " +
                                        replace(strip_colours(desc), "\n",
                                                "\n\n") + "\n"),
                                "finish_desc_edit");
     } else
       this_player()->do_edit("", "finish_desc_edit");
     ++use_count;
     return 1;
   }
   else if (strlen(str) > MAX_DESC) {
      notify_fail("Description unchanged.  Given description was too long.  "
                  "Maximum allowed length is " + MAX_DESC+ ".\n");
      return 0;
   }
   TP->set_desc(strip_colours(str));
   write("Description set.\n");
   return 1;
}
void finish_desc_edit(string str) {
   string cname;
   --use_count;
   if (!str) {
      write("Description unchanged.\n");
     return;
   }
   cname = this_player()->query_cap_name();
   if (str[0 .. strlen(cname)] == cname + " ")
      str = str[strlen(cname) + 1 .. 10000];
   str = strip_colours(str);
   str = replace(str, ({ "\n\n", "$NEW_LINE$", "\n", " " }));
   str = replace(str, "$NEW_LINE$", "\n");
   if (strlen(str) > MAX_DESC) {
      write("Description unchanged.  Given description was too long.  "
            "Maximum allowed length is " + MAX_DESC+ ".\n");
      return;
   }
   TP->set_desc(str);
   write("Description set.\n");
   return;
}
int cmd_zone(string zone, string desc) {
   this_player()->set_zone_desc(zone, desc);
   write("Set the description for the zone " + zone + " as \"" + desc + "\".\n");
   return 1;
}
int cmd_zone_clear(string zone) {
   this_player()->set_zone_desc(zone, 0);
   write("Cleared the description for the zone " + zone + ".\n");
   return 1;
}
mixed *query_patterns()  {
   return ({ "", (: cmd(0) :),
             "main <string'description'>", (: cmd($4[0]) :),
             "edit", (: cmd("edit") :),
             "clear", (: cmd("clear") :),
             "zone {" + _zone_str + "} <string'description'>",
                  (: cmd_zone($4[0], $4[1]) :),
             "zone {" + _zone_str + "} clear",
                  (: cmd_zone_clear($4[0]) :),
               });
}