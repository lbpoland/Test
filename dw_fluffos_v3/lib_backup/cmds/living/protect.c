inherit "/cmds/base";
#define TP this_player()
mixed cmd(object *things) {
  int i;
  object *protectees;
  things -= ({ TP });
  if ( !sizeof( things ) ) {
     add_failed_mess("You cannot protect yourself!\n");
     return 0;
  }
  if ( TP->query_property( "dead" ) ) {
    add_failed_mess("You cannot provide much protection as a ghost.\n" );
    return 0;
  }
  protectees = ({ });
  for ( i = 0; i < sizeof( things ); i++ ) {
    if ( things[ i ]->add_protector( TP ) ) {
      protectees += ({ things[ i ] });
      things = delete( things, i, 1 );
      i--;
    }
  }
  if ( !sizeof( protectees ) ) {
    add_failed_mess("You cannot protect $I.\n", things);
    return 0;
  }
  if ( sizeof( things ) ) {
    write( "You cannot protect "+ query_multiple_short( things ) +".\n" );
  }
  add_succeeded_mess(({ "You will protect $I.\n",
                        "$N moves to protect $I.\n" }),
	                protectees);
  return 1;
}
int show_protectors() {
   object *protect;
   object womble;
   protect = this_player()->query_protectors();
   if (sizeof(protect)) {
      write("You are being protected by " + query_multiple_short(protect) +
            ".\n");
   } else {
      write("You are not being protected by anyone.\n");
   }
   protect = ({ });
   foreach (womble in all_inventory(environment(this_player()))) {
      if (living(womble) && womble != this_player()) {
         if (member_array(this_player(), womble->query_protectors()) != -1) {
            protect += ({ womble });
         }
      }
   }
   if (sizeof(protect)) {
      write("Of the people in this room, you are protecting " +
            query_multiple_short(protect) + ".\n");
   } else {
      write("You are not protecting anyone in this room.\n");
   }
   return 1;
}
mixed *query_patterns() {
   return ({ "<indirect:living>",
             (: cmd($1) :),
             "",
             (: show_protectors() :) });
}