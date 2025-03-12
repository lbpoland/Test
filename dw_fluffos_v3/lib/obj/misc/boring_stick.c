inherit "/std/held";
#include <move_failures.h>
int state;
void set_state(int state);
void setup() {
  set_name("stick");
  set_state(0);
  set_weight(2);
  set_value(10);
}
void init() {
  this_player()->add_command("turn", this_object(),
                                "<direct:object> {on|off}");
  this_player()->add_command("flick", this_object(),
                                "switch on <direct:object>");
  this_player()->add_command("press", this_object(),
                                "switch on <direct:object>");
  this_player()->add_command("push", this_object(),
                                "switch on <direct:object>");
  this_player()->add_command("flick", this_object(),
                                "<direct:object>");
  this_player()->add_command("turn", this_object(),
                                "switch {on|off} on <direct:object>");
  this_player()->add_command("switch", this_object(),
                                "<direct:object> {on|off}");
}
void set_state(int new_state) {
  state = new_state;
  if (state) {
    set_long(
"The long straight black stick vibrates slightly in your hands, you "
"get a nice massage from it.  There is something which looks a bit "
"like a switch down near the base of the stick.  Flashing lights "
"rush up and down the side of the stick in a mad progression.\n");
  } else {
    set_long(
"The long straight black stick vibrates slightly in your hands, you "
"get a nice massage from it.  There is something which looks a bit "
"like a switch down near the base of the stick.\n");
  }
  if (environment())
    if (state) {
      if (living(environment()))
        environment()->add_extra_look(this_object());
    } else
      environment()->remove_extra_look(this_object());
}
string extra_look() {
  return capitalize(previous_object()->query_pronoun())+
         " is surrounded by an aura of bees.\n";
}
int do_turn(mixed *indirect_obs, string indir_match,
            string dir_match, mixed *args, string pattern) {
  int new_state;
  new_state = 0;
  if ("<direct:object> {on|off}" == pattern) {
    if (args[1] == "on")
      new_state = 1;
  } else {
    if (args[0] == "on")
      new_state = 1;
  }
  if (state == new_state) {
    this_player()->add_failed_mess(this_object(),
                   "$D is already turned "+(state?"on":"off")+".\n", ({ }));
    return 0;
  }
  set_state(new_state);
  this_player()->add_succeeded_mess(this_object(),
    "$N $V $D "+(state?"on":"off")+".\n", ({ }));
  return 1;
}
int do_flick() {
  set_state(!state);
  this_player()->add_succeeded_mess(this_object(),
    "$N $V the switch on $D to the "+(state?"on":"off")+" position.\n", ({ }));
  return 1;
}
int do_press() {
  return do_flick();
}
int do_push() {
  return do_flick();
}
int do_switch(mixed *indirect_obs, string indir_match,
              string dir_match, mixed *args, string pattern) {
  int new_state;
  if (args[1] == "on")
    new_state = 1;
  if (state == new_state) {
    this_player()->add_failed_mess(this_object(),
                   "$D is already turned "+(state?"on":"off")+".\n", ({ }));
    return 0;
  }
  set_state(new_state);
  this_player()->add_succeeded_mess(this_object(),
    "$N $V $D "+(state?"on":"off")+".\n", ({ }));
  return 1;
}
mapping query_dynamic_auto_load() {
   return ([ "state" : state,
             "::" : held::query_dynamic_auto_load()
          ]);
}
void init_dynamic_arg(mapping map) {
   set_state(map["state"]);
   if ( map[ "::" ] )
      held::init_dynamic_arg( map[ "::" ] );
}
varargs int move(mixed dest, string str1, string str2) {
  int ret;
  object old;
  old = environment();
  ret = ::move(dest, str1, str2);
  if (ret == MOVE_OK) {
    if (state) {
      if (old)
        old->remove_extra_look(this_object());
      if (living(environment())) {
        environment()->add_extra_look(this_object());
      }
    }
  }
  return ret;
}