#include <move_failures.h>
inherit "/cmds/base";
#define TP this_player()
int cmd( string str ) {
  object *items, *moved = ({ }), *left = ({ });
  int i;
  if( !stringp(str) || (str == "" )) {
    add_failed_mess("Syntax: gather <plant>\n");
    return 0;
  }
  items = "/obj/handlers/gathering"->gather_item(str, TP);
  if (!sizeof(items)) {
    if (str[<1] != 's') {
       str = pluralize(str);
    }
    add_failed_mess( "You couldn't find any " + str + ".\n");
    return 0;
  }
  for (i = 0; i < sizeof(items); i++) {
    if (items[i]->move(TP) == MOVE_OK) {
    moved += ({ items[i] });
  }  else
    if(items[i]->move(environment(TP)) == MOVE_OK) {
      left += ({ items[i] });
    } else {
      items[i]->move("/room/rubbish");
    }
  }
  if (sizeof(moved)) {
#ifdef NO_DECAY
    moved->set_decay_speed(0);
#endif
    add_succeeded_mess( "$N gather$s $I.\n", moved );
    event( environment( this_player() ), "gather", this_player(), str,
        moved );
  }
  left -= ({ this_player() });
  if (sizeof(left))
    write("You found but couldn't get " + query_multiple_short(left) + ".\n");
  return 1;
}
mixed query_patterns() {
  return ({ "<string>", (: cmd( $4[0] ) :) });
}