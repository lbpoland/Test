#include <library.h>
#include <player.h>
inherit "/cmds/base";
mixed cmd( string words ) {
  string pad = " ";
  if(!environment(this_player())) {
    return notify_fail("You are in limbo, you cannot emote.\n");
  }
  if ( userp( this_player() ) && !this_player()->query_creator() ) {
    if ( this_player()->query_property( "emote" ) ) {
      LIBRARY->set_quest( (string)this_player()->query_name(), "emote" );
      this_player()->remove_property( "emote" );
    }
    if ( !LIBRARY->query_quest_done( (string)this_player()->query_name(),
                                     "emote" ) ) {
      return notify_fail( NOT_ALLOWED );
    }
    if(this_player()->query_property("no emote")) {
      return notify_fail(NOT_ALLOWED);
    }
    if ( (int)this_player()->adjust_sp( -EMOTE_COST ) < 0 ) {
      return notify_fail( NO_POWER );
    }
  }
  if ( !words || ( words == "" ) ) {
    return notify_fail( "Syntax: emote <text>\n" );
  }
  words = strip_colours(words);
  words = replace(words, ({"        ", " ",
                           "       ", " ",
                           "      ", " ",
                           "     ", " ",
                           "    ", " ",
                           "   ", " ",
                            }) );
  this_player()->adjust_time_left( -5 );
  if (words[0..0] == "'") pad = "";
  environment( this_player() )->event_emote( this_player(),
                                             "$C$" + this_player()->one_short() + pad +
                                             words +"\n" );
  all_inventory( environment( this_player() ) )->
    event_emote( this_player(), "$C$" + this_player()->one_short() +
                                pad + words + "%^RESET%^\n" );
  write( "You emote: $C$"+
         (string)this_player()->pretty_short( this_player() ) + pad + words +
         "%^RESET%^\n" );
  return 1;
}