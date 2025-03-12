#include <language.h>
inherit "/cmds/base";
varargs string create_text( object thing, int label );
mixed cmd( object *things ) {
   string gendstr;
   string text;
   string read;
   string reader;
   string *others;
   string r_short;
   object thing;
   mapping hide_invis;
   int dark;
   dark = this_player()->check_dark(environment(this_player())->query_light());
   if (dark < 0) {
      add_failed_mess("It is too dark to read $I.\n", things);
      return 0;
   }
   if (dark > 0) {
      add_failed_mess("It is too bright to read $I.\n", things);
      return 0;
   }
   reader = "";
   others = ({ });
   foreach( thing in things ) {
      if (!is_in_me_or_environment(thing, this_player())) {
          add_failed_mess("You cannot read $I.\n", ({ thing }));
          continue;
      }
      text = thing->query_readable_message(this_player());
      read = thing->query_read_short();
      if (!read) {
         read = "$name$";
      }
      if ( !text) {
        if (living(thing)) {
            gendstr = thing->query_objective();
        } else {
           gendstr = "it";
        }
        r_short = thing->query_read_short();
        if (!r_short) {
           r_short = "$name$";
        }
        if (!thing->command_control("read")) {
            if (thing != this_player()) {
               reader += "$C$"+ replace_string(r_short,
                                        "$name$",
                                        thing->a_short()) +
                     " does not have anything written on " +
                     gendstr + ".\n";
            } else {
               reader += "You cannot read yourself.\n";
            }
         } else {
            others += ({ replace( read, "$name$", (string)thing->a_short() ) });
            reader += "";
         }
         continue;
      }
      reader += "You read "+ replace_string( read, "$name$",
            (string)thing->the_short() ) +":\n"+ text + "\n";
      if ( read == "$name$" ) {
          others += ({ thing });
      }
      else {
          others += ({ replace( read, "$name$", (string)thing->a_short() ) });
      }
   }
   if ( !sizeof( others ) ) {
      add_failed_mess(reader);
      return 0;
   }
   write( "$P$Read$P$"+ reader );
   hide_invis = this_player()->query_hide_invis();
   if(!hide_invis["hiding"]) {
      add_succeeded_mess(({ "", "$N read$s $I.\n" }), others);
   }
   return 1;
}
mixed *query_patterns() {
   return ({ "<indirect:object>", (: cmd($1) :) });
}