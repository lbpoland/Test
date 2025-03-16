#include <tasks.h>
#define TOO_SOON "too soon to proceed from rooftop"
inherit "/std/room/outside";
#define DEBUG
#define ROCK "other.movement.climbing.rock"
#define ROPE "other.movement.climbing.rope"
void   set_death_reason( string );
void   set_fall_damage( string, int );
mixed  query_fall_damage( string );
int    calc_fall_damage( string );
void   set_weak_roof( int, string );
void   set_slope( int, string, string );
string process_string( string, mapping );
string process_mess( string, object, string );
mapping  damages;
string * damage_types;
int      roof_max_weight;
int      gradient;
string   weak_roof_dest;
string   slope_dest;
string   place;
string   death_reason;
string * weak_messages;
string * slope_messages;
string * step_messages;
string * jump_tm_messages;
string * jump_success_messages;
string * jump_failure_messages;
string * ghost_fall_messages;
string * item_slope_messages;
string * corpse_slope_messages;
mapping jump_info;
mapping translations;
void init() {
   ::init();
   add_command( "jump", "<word'direction'>",
     (: this_object()->do_roofjump( $4[0] ) :) );
}
void create() {
   do_setup++;
   ::create();
   do_setup--;
   weak_messages = ({
     "The roof collapses! This is going to be painful...\n",
     "$short$ crashes down through a weak spot in the roof.",
     "$short$ comes crashing to the ground, landing in a rain of debris.",
     "You hear an ominous creak.\n"
   });
   slope_messages = ({
     "The roof is too steep for you to stand on! It's time to make friends "
       "with the floor...\n",
     "$short$ gets in touch with gravity and slides over the edge of the "
       "roof.",
     "$short$ comes crashing to the ground, landing in a heap."
   });
   step_messages = ({
     "You step off the edge of the roof into midair.\n",
     "$short$ steps off the edge of the roof and plummets earthwards.",
     "$short$ comes crashing to the ground, landing in a heap."
   });
   jump_tm_messages = ({
     "You leap more gracefully through the air.",
     "You feel more able to leap tall buildings in a single bound.",
     "You jump like a mountain goat."
   });
   jump_success_messages = ({
     "You launch yourself off the edge of the roof and land gracefully on "
       "the other side.\n",
     "$short$ jumps gracefully across the gap to the $dir$.",
     "$short$ jumps in from across the gap to the $opp_dir$."
   });
   jump_failure_messages = ({
     "You launch yourself off the edge of the roof!\nUnfortunately you "
       "misjudge the distance and plummet earthwards. This is going to "
       "hurt...\n",
     "$short$ jumps off to the $dir$, but misjudges and plummets "
       "earthwards.",
     "$short$ plummets to the ground, landing in a heap."
   });
   ghost_fall_messages = ({
      "You find your consciousness drifting earthwards.\n",
      "$the_short$ drifts earthwards.",
      "$the_short$ drifts in from above, looking somewhat dazed."
   });
   item_slope_messages = ({
     "$the_short$ tumbles over the edge and plummets to the ground.\n",
     "Hearing a noise, you look up just as $a_short$ falls off the edge "
       "of the roof and hits the ground.\n"
   });
   corpse_slope_messages = ({
     "$the_short$ tumbles over the edge and plummets to the ground with "
       "a sickening thud.\n",
     "Hearing a noise, you look up just as $the_short$ tumbles over the "
       "edge of the roof and hits the ground with a sickening thud.\n"
   });
   damages = ([ ]);
   damage_types = ({ "weak", "slope", "step", "jump" });
   translations = ([ ]);
   jump_info = ([ ]);
   this_object()->setup();
}
void set_weak_messages( string player, string from, string to, string warn ) {
   weak_messages = ({ player, from, to, warn });
}
void set_slope_messages( string player, string from, string to ) {
   slope_messages = ({ player, from, to });
}
void set_step_messages( string player, string from, string to ) {
   step_messages = ({ player, from, to });
}
void set_jump_tm_messages( string * messages ) {
   jump_success_messages = messages;
}
void set_jump_success_messages( string player, string from, string to ) {
   jump_success_messages = ({ player, from, to });
}
void set_jump_failure_messages( string player, string from, string to ) {
   jump_failure_messages = ({ player, from, to });
}
void set_ghost_fall_messages( string player, string from, string to ) {
   ghost_fall_messages = ({ player, from, to });
}
void set_corpse_slope_messages( string from, string to ) {
  corpse_slope_messages = ({ from, to });
}
void set_item_slope_messages( string from, string to ) {
   item_slope_messages = ({ from, to });
}
void set_fall_damage( string type, int damage ) {
   if( damage < 0 )
      damage = -damage;
   if( type == "all" ) {
      foreach( type in damage_types )
         damages[type] = damage;
   } else if( member_array( type, damage_types ) >= 0 ) {
      damages[type] = damage;
   } else
      return;
}
mixed query_fall_damage( string type ) {
   if( type == "all" )
      return damages;
   else
      return damages[type];
}
int calc_fall_damage( string type ) {
   if( type == "all" )
      return 0;
   return query_fall_damage( type ) + random( query_fall_damage( type ) );
}
void set_weak_roof( int maxweight, string dest ) {
   roof_max_weight = maxweight;
   weak_roof_dest = dest;
}
void set_slope( int angle, string loc, string dest ) {
   gradient = ( angle * 100 ) / 90;
   place = loc;
   slope_dest = dest;
}
int set_jump( mixed dir, string dest, string fall_dest, int distance ) {
   string * dirs;
   mixed foo;
   string bar;
   if( stringp( dir ) ) {
      dirs = ({ dir });
   } else if( arrayp(dir) ) {
      foreach( foo in dir )
         if( !stringp( foo ) )
            return 0;
      dirs = sort_array( dir, 1 );
   }
   foreach( bar in dir )
      if( !undefinedp( translations[bar] ) )
         return -1;
   jump_info[ dir[0] ] = ({ dest, fall_dest, distance });
   foreach( bar in dir )
      translations[bar] = dir[0];
   if( !query_exit( dir[0] ) )
      add_exit( dir[0], dest, "roof" );
   modify_exit( dir[0], ({
     "closed", 1,
     "function", (: this_object()->silly_move( $1, $2, $3,
       jump_info[ translations[$1] ][1], "step", step_messages ) :),
     "look", "You'll have to jump across to see what's on the other side."
   }) );
   return 1;
}
int silly_move( string verb, object ob, string special, mixed dest,
  string dam_type, string * messages ) {
   this_object()->do_fall( ob, dest, dam_type, messages, 0 );
   return notify_fail( "" );
}
void do_fall( object obj, mixed dest, string dam_type, string * messages,
  string dir ) {
   int damage, i;
   object destob;
   obj->remove_property( TOO_SOON );
   for( i = 0; i < sizeof( messages ); i++ )
      messages[i] = process_mess( messages[i], obj, dir );
   if( stringp( dest ) ) {
      if( !(destob = load_object( dest ) ) ) {
         tell_object( obj, "Cannot find " + dest + ".\n"
           "Moving you to the void - Please contact a creator.\n" );
         obj->move_with_look( "/room/void", "Poof. $N appears.\n",
           "$N plummets earthwards.\n" );
         return;
      }
   } else if( objectp( dest ) ) {
      destob = dest;
   } else {
      return;
   }
   tell_object( obj, messages[0] );
   obj->move_with_look( destob, messages[2], messages[1] );
   if( obj->query_property( "dead" ) )
      return;
   damage = calc_fall_damage( dam_type );
   if( damage >= obj->query_hp() ) {
      set_death_reason( "plummeting from the rooftops" );
      obj->attack_by( this_object() );
      obj->do_death();
   } else
      obj->adjust_hp( -damage );
}
void event_enter( object obj, object from ) {
   int totalweight, objectweight, i;
   float encum, diff;
   int fall;
   object * contents;
   object destination;
   if( !obj ) return;
   if( obj->query_property( "demon" )
     || obj->query_property( "floating" ) ) {
      return;
   }
   obj->add_property( TOO_SOON, 1, 5 );
   if( roof_max_weight ) {
      contents = all_inventory( this_object() );
      for( i = 0; i < sizeof(contents); i++ ) {
         objectweight = contents[i]->query_weight();
         objectweight += contents[i]->query_loc_weight();
         totalweight += objectweight;
#ifdef DEBUG
         debug_printf( "event_enter: Total weight of %s is %d units.\n",
           obj->query_name(), objectweight );
#endif
      }
#ifdef DEBUG
      debug_printf( "event_enter: The current weight on this roof is %d "
        "units. Max weight is set to %d.\n", totalweight, roof_max_weight );
#endif
      if( totalweight > roof_max_weight ) {
         fall = 1;
         tell_room( environment( obj ), weak_messages[3] );
         if( !(destination = load_object( weak_roof_dest ) ) ) {
            tell_room( this_object(), "Error loading room "
              + weak_roof_dest + ", moving you to the void.\n"
              "Please contact a creator.\n" );
            for( i = 0; i < sizeof(contents); i++ )
               contents[i]->move_with_look( "/room/void" );
            return;
         }
         for( i = 0; i < sizeof(contents); i++ ) {
            call_out( "do_fall", 1, contents[i], destination, "weak",
              weak_messages, 0 );
         }
         return;
      }
   }
   if( gradient && !fall ) {
      if( living( obj ) ) {
         if( ( obj->query_property( "dead" ) )
           || !( obj->query_max_weight() ) ) {
            call_out( "do_fall", 1, obj, slope_dest, "step",
              ghost_fall_messages );
            return;
         }
         encum = ( 100 * to_float( obj->query_loc_weight() ) )
           / to_float( obj->query_max_weight() );
         diff = to_int( sin( ( 3.1415926536 / 180.0 ) * gradient )
           * ( encum * 10 ) );
         call_out( "gradient_check", 1, obj, slope_dest,
           to_int( diff + ( gradient * 2 ) ) );
      } else {
         if( member_array( obj->query_name(),
           ({ "death", "binky" }) ) >= 0 )
            return;
         if( gradient > 3 ) {
            if( obj->query_corpse() ) {
               obj->move( slope_dest,
                 process_mess( corpse_slope_messages[1], obj, 0 ),
                 process_mess( corpse_slope_messages[0], obj, 0 ) );
            } else {
               obj->move( slope_dest,
                 process_mess( item_slope_messages[1], obj, 0 ),
                 process_mess( item_slope_messages[0], obj, 0 ) );
            }
         }
      }
      return;
   }
   obj->remove_property( TOO_SOON );
}
void gradient_check( object obj, string destination, int diff ) {
   object destob;
#ifdef DEBUG
   debug_printf( "gradient_check( %s, \"%s\", %d )",
     obj->query_name(), destination, diff );
#endif
   obj->remove_property( TOO_SOON );
   switch( TASKER->perform_task( obj, ROCK, diff + 1, TM_FIXED ) ) {
   case AWARD:
      tell_object( obj, "%^YELLOW%^" + ({
        "You balance more confidently on the " + place + ".",
        "Climbing becomes easier."
      })[ random(2) ] + "%^RESET%^\n" );
   case SUCCEED:
      tell_object( obj, "The " + place + " is steep, but you manage "
        "not to fall.\n" );
      break;
   case FAIL:
      if( !( destob = load_object( destination ) ) ) {
         tell_object( obj, "Error loading room " + destination +
           ", moving you to the void.\nPlease contact a creator.\n" );
         obj->move_with_look( "/room/void" );
      } else
         do_fall( obj, destob, "slope", slope_messages, 0 );
      break;
   default:
      write( "Gnaaaaaaaaaaaah! You should not be getting this message.  "
        "Please contact a creator.\n" );
      break;
   }
}
int do_roofjump( string dir ){
   mixed * info;
   int distance;
   float weight, max_weight;
   object destination, fall_destination;
   string key;
   if( !( key = translations[dir] ) || !( info = jump_info[key] ) ) {
      add_failed_mess( "You can't jump there!\n" );
      return 0;
   }
   if( !(destination = load_object( info[0] ) ) ) {
      add_failed_mess( "Error! The file " + info[0] + " does not exist "
        "or does not load. Please contact a creator.\n" );
      return 0;
   }
   if( !(fall_destination = load_object( info[1] ) ) ) {
      add_failed_mess( "Error! The file " + info[1] + " does not exist "
        "or does not load. Please contact a creator.\n" );
      return 0;
   }
   distance = info[2];
   if( distance ) {
      weight = to_float( this_player()->query_loc_weight() );
      max_weight = to_float( this_player()->query_max_weight() );
      distance *= to_float( ( to_float(weight) * 7) /
           to_float(max_weight) ) + 15;
      switch( TASKER->perform_task( this_player(), ROCK, distance, TM_FIXED ) ) {
         case AWARD:
            write( "%^YELLOW%^"
              + jump_tm_messages[ random( sizeof( jump_tm_messages ) ) ]
              + "%^RESET%^\n" );
         case SUCCEED:
            write( process_mess( jump_success_messages[0], this_player(), dir ) );
            this_player()->move_with_look( destination,
              process_mess( jump_success_messages[2], this_player(), dir ),
              process_mess( jump_success_messages[1], this_player(), dir ), );
            break;
         case FAIL:
            write( process_mess( jump_failure_messages[0], this_player(), dir ) );
            do_fall( this_player(), fall_destination, "jump",
              jump_failure_messages, dir );
            break;
         default:
            write( "Oh dear. Something is broken. Please inform a "
              "creator.\n" );
      }
      return 1;
   }
}
string query_death_reason() {
   call_out( (: death_reason = 0 :), 2 );
   if( death_reason )
      return "/global/player"->convert_message( death_reason );
   return "a rooftop (" + file_name( this_object() )
     + ") with an incorrectly set death message";
}
void set_death_reason( string str ) {
   death_reason = str;
}
string process_string( string str, mapping transforms ) {
   string foo, bar;
   foreach( foo, bar in transforms )
      if( bar ) str = replace_string( str, foo, bar );
   return "/global/player"->convert_message( str );
}
string process_mess( string str, object ob, string direction ) {
   string opp_dir;
   string * directions = ({ "north", "northeast", "east", "southeast",
     "south", "southwest", "west", "northwest" });
   if( !str || ( str == "" ) )
      return "";
   if( stringp( direction ) ) {
      if( member_array( direction, directions ) < 0 ) {
         opp_dir = 0;
      } else {
         opp_dir =
           directions[ ( member_array( direction, directions ) + 4 ) % 8 ];
      }
   }
   str = process_string( str, ([
     "$dir$"       : direction,
     "$opp_dir$"   : opp_dir,
     "$short$"     : ob->query_short(),
     "$poss$"      : ob->query_possessive(),
     "$pronoun$"   : ob->query_pronoun(),
     "$obj$"       : ob->query_objective(),
     "$a_short$"   : ob->a_short(),
     "$the_short$" : ob->the_short(),
     "$one_short$" : ob->one_short()
   ]) );
   return implode( explode( str, ". " ),
     (: "$C$" + $1 + ". " + "$C$" + $2 :) );
}
int test_remove( object ob, int flag, mixed dest ) {
   if( !living(ob) ) {
      return ::test_remove( ob, flag, dest );
   }
   if( objectp(dest) )
      dest = file_name(dest);
   if( !stringp(dest) || dest == "/room/rubbish" )
      return 1;
   if( ob->query_property( TOO_SOON ) ) {
      tell_object( ob, "You haven't quite caught your balance yet.\n" );
      notify_fail( "" );
      return 0;
   }
   return ::test_remove( ob, flag, dest );
}