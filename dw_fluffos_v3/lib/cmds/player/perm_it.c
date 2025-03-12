inherit "/cmds/base";
int cmd( object player ) {
  object *corpses, corpse;
  int i;
  corpses = filter( children( "/obj/corpse" ),
                    (: $1 && $1->query_property("player" ) :) );
  corpses = filter( corpses,
                    (: $1 && $1->query_ownership() ==
                     $(this_player()->query_name()) :) );
  if( sizeof( corpses ) ) {
    foreach( corpse in corpses ){
      if(member_array(player->query_name(), corpse->query_permitted()) != -1) {
        i++;
      } else {
        corpse->give_permission( player->query_name() );
      }
    }
  } else {
    add_failed_mess("You don't seem to have a corpse!  Why not die and try "
                    "again?%^RESET%^\n");
    return 0;
  }
  if( i == sizeof( corpses ) ){
    write(capitalize(player->query_name()) + " is already permitted to "
          "remove items from your corpse.%^RESET%^\n" );
  } else {
    write(capitalize(player->query_name()) + " is now permitted to "
          "remove items from your corpse.%^RESET%^\n" );
    tell_object(player, "%^BOLD%^%^GREEN%^You now have permission to get "
                "items from " + this_player()->query_cap_name() +
                "'s corpse.%^RESET%^\n");
  }
  return 1;
}
mixed *query_patterns() {
  return ({ "<indirect:player>", (: cmd($1[0]) :) });
}