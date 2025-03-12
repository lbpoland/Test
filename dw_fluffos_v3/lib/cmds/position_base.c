inherit "/cmds/base";
#include <position.h>
string position;
string up_down;
string position_type;
int query_position_command() {
   return 1;
}
string query_up_down() {
   return up_down;
}
string query_position() {
   return position;
}
string query_position_type() {
   return position_type;
}
void setup_position(string pos, string up, string type) {
   position = pos;
   up_down = up;
   position_type = type;
}
int position(object person, int silent) {
   string pos_type;
   if (person->query_position() == position_type) {
      if (person == this_player()) {
         add_failed_mess("You are already "+position_type+".\n");
      }
      return 0;
   }
   if (!environment(person) ||
       !environment(person)->is_allowed_position(position_type)) {
      if (person == this_player()) {
         add_failed_mess("You cannot " + position +  " " + up_down +
                         " here.\n");
      }
      return 0;
   }
   if (!silent) {
      if (up_down != "") {
         if (person->query_position_on()) {
            pos_type = person->query_position_type();
            tell_object(person, "You " + position+" " + up_down +
                             " " + pos_type + " " +
                             person->query_position_on_short() + ".\n");
            tell_room(environment(person),
                      person->one_short() + " $V$0=" + pluralize(position) + ","+
                      position+"$V$ "  + up_down +
                      " " + pos_type + " " +
                      person->query_position_on_short() + ".\n",
                      ({ person }));
         } else {
            tell_object(person, "You " + position+" " + up_down + ".\n");
            tell_room(environment(person),
               person->one_short() + " $V$0=" + pluralize(position) + "," +
                      position+"$V$ " +
                      up_down + ".\n",
                      ({ person }));
         }
      } else {
         if (person->query_position_on()) {
            pos_type = person->query_position_type();
            tell_object(person, "You " + position +
                             " " + pos_type + " " +
                             person->query_position_on_short() + ".\n");
            tell_room(environment(person),
               person->one_short() + " $V$0=" + pluralize(position) + ","+position+
                             "$V$ " + pos_type + " " +
                             person->query_position_on_short() + ".\n",
               ({ person }));
         } else {
            tell_object(person, "You " + position + ".\n");
            tell_room(environment(person),
               person->one_short() + " $V$0=" + pluralize(position) + ","+
                      position+"$V$.\n",
               ({ person }));
         }
      }
   }
   person->set_position(position_type);
   return 1;
}
int position_floor(object person, int silent) {
   if (!environment(person) ||
       !environment(person)->is_allowed_position(position_type)) {
      if (person == this_player()) {
         add_failed_mess("You cannot " + position +  " " + up_down +
                         " here.\n");
      }
      return 0;
   }
   if (person->query_position_on()) {
      if (!silent) {
         if (up_down != "") {
            tell_object(person, "You get off " +
                person->query_position_on_short() +
                " and " + position + " " + up_down + ".\n");
            tell_room(environment(person),
                person->one_short() + " gets off " +
                person->query_position_on_short() +
                " and $V$0=" + pluralize(position) + ","+position+"$V$ " + up_down + ".\n",
                ({ person }));
         } else {
            tell_object(person, "You get off " +
                person->query_position_on_short() +
                " and " + position + ".\n");
            tell_room(environment(person),
                person->one_short() + " gets off " +
                person->query_position_on_short() +
                " and $V$0=" + pluralize(position) + ","+position+"$V$.\n",
                ({ person }));
         }
      }
      person->set_position(position_type);
      person->set_position_on(0);
      person->set_position_type(0);
      person->set_position_multiple(0);
      return 1;
   }
   return position(person, 0);
}
string *query_position_strings(object person) {
   string bit;
   string bit_other;
   switch (person->query_position_type()) {
      case AT_TYPE :
      case BESIDE_TYPE :
         bit = "move away from";
         bit_other = "moves away from";
         break;
      case ON_TYPE :
      default :
         bit = "get off";
         bit_other = "gets off";
         break;
   }
   return ({ bit, bit_other });
}
int position_object(object *obs, string pos_type, object person) {
   int i;
   int mult;
   string rabbit;
   string *pos_strings;
   if (!environment(person) ||
       !environment(person)->is_allowed_position(position_type)) {
      if (person == this_player()) {
         add_failed_mess("You cannot " + position +  " " + up_down +
                         " here.\n");
      }
      return 0;
   }
   pos_strings = query_position_strings(person);
   for (i = 0; i < sizeof(obs); i++) {
      if (obs[i]->query_property(CAN_POSITION_PROPERTY)) {
         mult = obs[i]->query_property(MULTIPLE_POSITION_PROPERTY);
         if (person->query_position_on()) {
            if (person->query_position_on() == obs[i] &&
                person->query_position_type() == pos_type) {
               if (person->query_position() != position_type) {
                  return position(person, 0);
               }
               if (person == this_player()) {
                  add_failed_mess("You are already " + position_type + " " +
                                  pos_type + " $I.\n",
                                  obs[i..i]);
               }
               return 0;
            }
            tell_object(person, "You " + pos_strings[0] + " " +
                person->query_position_on_short() +
                " and " + position + " " + pos_type+" "+
                obs[i]->a_short()+".\n");
            tell_room(environment(person),
                person->one_short() + " " + pos_strings[1] + " " +
                person->query_position_on_short() +
                " and $V$0=" + pluralize(position) + ","+position+"$V$ " + pos_type + " " +
                obs[i]->a_short() + ".\n",
                ({ person }));
            person->set_position(position_type);
            person->set_position_on(obs[i]);
            person->set_position_type(pos_type);
            person->set_position_multiple(mult);
            return 1;
         }
         tell_object(person, "You " + position + " " + pos_type +
                             " " + obs[i]->a_short()+".\n");
         tell_room(environment(person),
                   person->one_short() + " $V$0=" + pluralize(position) + ","+position+
                   "$V$ " + pos_type + " " +
                   obs[i]->a_short() + ".\n",
                   ({ person }));
         person->set_position(position_type);
         person->set_position_on(obs[i]);
         person->set_position_type(pos_type);
         person->set_position_multiple(mult);
         return 1;
      } else  {
         rabbit = obs[i]->query_position_string(position_type);
         if (rabbit) {
            mult = obs[i]->query_position_multiple(position_type);
            if (person->query_position_on()) {
               if (person->query_position_on() == rabbit &&
                   person->query_position_type() == pos_type) {
                  if (person->query_position() != position_type) {
                     return position(person, 0);
                  }
                  add_failed_mess("You are already " + position_type + " " +
                                  pos_type + " $I.\n",
                                  obs[i..i]);
                  return 0;
               }
               tell_object(person, "You " + pos_strings[0] +  " " +
                   person->query_position_on_short() +
                   " and " + position + " " + pos_type + " " +
                   rabbit + ".\n");
               tell_room(environment(person),
                         person->one_short() + " " + pos_strings[1] + " " +
                         person->query_position_on_short() +
                         " and $V$0=" + pluralize(position) + ","+position+"$V$ " +
                         pos_type + " " +
                         rabbit + ".\n",
                         ({ person }));
               person->set_position(position_type);
               person->set_position_on(rabbit);
               person->set_position_type(pos_type);
               person->set_position_multiple(mult);
               return 1;
            }
            tell_object(person, "You "+position+" " + pos_type + " " +
                                 rabbit + ".\n");
            tell_room(environment(person),
                person->one_short() + " $V$0=" + pluralize(position) + ","+position+
                      "$V$ "+pos_type + " " +rabbit + ".\n",
                      ({ person }));
            person->set_position(position_type);
            person->set_position_on(rabbit);
            person->set_position_type(pos_type);
            person->set_position_multiple(mult);
            return 1;
         }
      }
   }
   return 0;
}
mixed *query_patterns() {
   return ({ "", (: position(this_player(), 0) :),
             "on [the] floor", (: position_floor(this_player(), 0) :),
             "{on|at|in|beside} <indirect:object>",
                    (: position_object($1, $4[0], this_player()) :) });
}