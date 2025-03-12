#include <tasks.h>
#define TP this_player()
#define SKILL "other.movement.climbing.rock"
inherit "/cmds/base";
void fall_off( object place, int number ) {
   if ( place->query_at_bottom() ) {
      write( "You try to climb, but you can't seem to get anywhere.\n" );
      say( (string)TP->one_short() + " tries to climb, but fails.\n" );
      return;
   }
   if ( random( (int)TP->query_dex() ) < number / 20 ) {
      write( "You begin to climb, but your fatigue makes you "+
            "clumsily lose your grip.\n" );
      say( (string)TP->one_short() +
            " begins to climb but clumsily loses "+
            (string)TP->query_possessive() +" grip.\n" );
      place->fall_down( TP );
      return;
   }
   write( "You begin to climb but wobble precariously and decide to "+
         "stay put for the moment.\n" );
   say( (string)TP->one_short() +
            " begins to climb, but wobbles precariously and stops.\n" );
}
mixed cmd( string words ) {
   int difficulty;
   object place;
   mixed ghost_action;
   mixed *move;
   string *move_descs = ({ "", "", "" });
   string skill;
   place = environment( TP );
   if ( !place ) {
      add_failed_mess( "You cannot climb anything: you're in limbo!\n" );
      return 0;
   }
   move = (mixed *)place->query_move( words );
   if ( !move ) {
      if( sizeof( place->query_moves() ) )
         add_failed_mess( "You cannot climb \""+ words +"\" from here.\n" );
      else
         add_failed_mess( "There is nothing to climb here.\n" );
      return 0;
   }
   if( stringp( move[2] ) ) {
      move_descs[0] =
         "You climb "+ words +".\n";
      move_descs[1] =
         "$N slowly climb$s "+ words +" and disappears from view.";
      move_descs[2] =
         copy( move[2] );
   } else if( sizeof( move[2] ) == 3 ) {
      move_descs = copy( move[2] );
      move_descs[0] += "\n";
   } else {
      return 0;
   }
   if ( TP->query_property( "dead" ) ) {
      ghost_action = place->query_ghost_action( place );
      if ( ! ghost_action ) {
          TP->move_with_look( move[ 1 ], move_descs[ 2 ], move_descs[ 1 ] );
          add_succeeded_mess("");
          return 1;
      }
      else if ( intp( ghost_action ) && ghost_action == 1 ) {
          add_failed_mess( "How can you climb anything?  You're dead!\n");
          return 0;
      }
      else if ( stringp( ghost_action ) ) {
          write( "As you move to climb the wall, your inherent wispiness gets "
              "the better of you, and you fall through to the other side.\n" );
          TP->move_with_look( ghost_action,
              "$N wisps through the wall with some undue haste.",
              "$N tries to climb the wall, but falls through it." );
          add_succeeded_mess( "" );
          return 1;
      }
      else if ( arrayp( ghost_action ) ) {
          write( ghost_action[ 1 ][ 0 ] + "\n" );
          TP->move_with_look( ghost_action[ 0 ],
              ghost_action[ 1 ][ 1 ], ghost_action[ 1 ][ 2 ] );
          add_succeeded_mess( "" );
          return 1;
      }
      else {
          TP->move_with_look( move[ 1 ], move_descs[ 2 ], move_descs[ 1 ] );
          add_succeeded_mess("");
          return 1;
      }
   }
   if( intp( move[0] ) ) {
      difficulty = move[0] + (int)TP->query_loc_weight() / 10;
      skill = SKILL;
   } else if( arrayp( move[0] ) && sizeof( move[0] ) > 1 ) {
      difficulty = move[0][0] + (int)TP->query_loc_weight() / 10;
      skill = move[0][1];
      debug_printf( "Base difficulty: %d, total difficulty: %d, skill: %s\n",
                    move[0][0], difficulty, move[0][1] );
   }
   if ( (int)TP->query_specific_gp( "other" ) < difficulty ) {
      fall_off( place, difficulty );
      add_succeeded_mess("");
      return 1;
   }
   TP->adjust_gp( -difficulty / 2 );
   switch ( (int)TASKER->perform_task(TP, skill, difficulty,
                                      TM_COMMAND)) {
      case AWARD :
         call_out( "advance_notice", random( 60 ), TP );
      case SUCCEED :
         write( move_descs[ 0 ] );
         TP->move_with_look( move[ 1 ], move_descs[ 2 ],
               move_descs[ 1 ] );
         return 1;
      default :
         break;
   }
   difficulty = random( difficulty );
   if ( (int)TP->query_specific_gp( "other" ) < difficulty ) {
      fall_off( place, difficulty );
      add_succeeded_mess("");
      return 1;
   }
   TP->adjust_gp( -difficulty );
   switch ( (int)TASKER->perform_task(TP, skill,  difficulty / 2,
                                      TM_COMMAND)) {
      case AWARD :
         write( "%^YELLOW%^You manage not to fall off!%^RESET%^\n" );
      case SUCCEED :
         write( "You begin to climb but wobble precariously and decide to "+
               "stay put for the moment.\n" );
         say( (string)TP->one_short() +
               " begins to climb, but wobbles precariously and stops.\n" );
         break;
      default :
         fall_off( place, difficulty );
         break;
   }
   add_succeeded_mess("");
   return 1;
}
void advance_notice( object thing ) {
   if ( !thing )
      return;
   tell_object( thing, "%^YELLOW%^"+ ({
      "In a flash of inspiration, you realise how to balance better "+
            "when climbing.",
      "Thinking about your climb, you realise something important.",
      "You realise that you've been using better grips to climb.",
      "You realise you've discovered how to find better places to "+
            "support your feet.",
      "You find you've worked out a more sensible way to distribute "+
            "your weight as you climb.",
      "With all your climbing, you discover you've found a better way "+
            "to locate handholds."
   })[ random( 6 ) ] +"%^RESET%^\n" );
}
mixed *query_patterns() {
   return ({ "<string'direction'>", (: cmd($4[0]) :) });
}