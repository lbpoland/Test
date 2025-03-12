inherit "/std/basic/condition";
#include <clothing.h>
#include <move_failures.h>
private string *immune_to;
private string *wear_effects;
private mixed type;
private mixed *wear_remove_func;
nosave object worn_by;
void create() {
   condition::create();
   set_damage_chance( 25 );
   immune_to = ({ "cold", "sound", "gas", "mental" });
   wear_effects = ({ });
   wear_remove_func = ({ });
}
int query_wearable() { return 1; }
string long( string word, int dark ) {
   switch ( dark ) {
      case 0 :
         return cond_string();
      default :
         return "";
   }
}
mixed *query_wear_remove_func() {
   return wear_remove_func;
}
void set_wear_remove_func( mixed file, string func ) {
   wear_remove_func = ({ file, func });
}
string *query_wear_effects() {
  if(!wear_effects)
    wear_effects = ({ });
  return copy(wear_effects);
}
void set_wear_effects( string *effects ) {
   wear_effects = effects;
}
void add_wear_effect( string effect ) {
   if ( member_array( effect, wear_effects ) == -1 ) {
      wear_effects += ({ effect });
   }
}
void do_damage( string type, int amount ) {
   if ( member_array( type, immune_to ) == -1 ) {
      condition::do_damage( type, amount );
   }
}
object query_worn_by() {
   return worn_by;
}
int set_worn_by( object thing ) {
   int i;
   if ( thing == worn_by ) {
      return 1;
   }
   if (thing && environment() != thing) {
      return 0;
   }
   this_object()->remove_hide_invis( "concealed" );
   if ( sizeof( wear_remove_func ) ) {
    if ( !objectp( wear_remove_func[ 0 ] ) && !objectp( load_object( wear_remove_func[ 0 ] ) ) ) {
        debug_printf( "Wear/Remove func is %O. Not called.\n", wear_remove_func );
      return 0;
    }
    if ( worn_by ) {
         call_other( wear_remove_func[ 0 ], wear_remove_func[ 1 ], 0, worn_by );
      }
      if ( thing ) {
         call_other( wear_remove_func[ 0 ], wear_remove_func[ 1 ], thing, thing );
      }
   }
   if ( sizeof( wear_effects ) ) {
      for ( i = 0; i < sizeof( wear_effects ); i++ ) {
         if ( worn_by ) {
            worn_by->taken_off( this_object(), wear_effects[ i ] );
         }
         if ( thing ) {
            thing->add_effect( wear_effects[ i ], this_object() );
         } else {
            wear_effects[i]->person_removing_item(this_object(), worn_by);
         }
      }
   }
   if ( worn_by ) {
      worn_by->now_removed( this_object() );
      this_object()->add_adjective("worn");
      this_object()->remove_adjective("unworn");
   } else {
      this_object()->remove_adjective("worn");
      this_object()->add_adjective("unworn");
   }
   if ( thing ) {
      thing->now_worn( this_object() );
   }
   worn_by = thing;
   return 1;
}
string *query_immune_to() {
   return immune_to;
}
void add_immune_to( mixed args ) {
   int i;
   if ( pointerp( args ) ) {
      for ( i = 0; i < sizeof( args ); i++ ) {
         add_immune_to( args[ i ] );
      }
   } else {
      if ( member_array( args, immune_to ) == -1 ) {
         immune_to += ({ args });
      }
   }
}
void remove_immune_to( mixed args ) {
   int i;
   if ( pointerp( args ) ) {
      for ( i = 0; i < sizeof( args ); i++ ) {
         remove_immune_to( args[ i ] );
      }
   } else {
      i = member_array( args, immune_to );
      if ( i != -1 ) {
         immune_to = delete( immune_to, i, 1 );
      }
   }
}
string query_type() {
   return type;
}
private void log_bad_type( mixed type ) {
  string word, str;
  if ( !clonep( this_object() ) ) {
      return;
  }
  word = (string)this_object()->query_property( "virtual name" );
  if ( word ) {
     str = sprintf( "BAD_TYPE %s (%s) = %O\n", word,
           (string)this_object()->query_short(), type );
  } else {
     str = sprintf( "BAD_TYPE %s (%s) = %O\n", file_name(),
           (string)this_object()->query_short(), type );
  }
  if ( this_player()) {
    write(str);
  }
  call_out("move", 2, "/room/broken");
}
void set_type( mixed word ) {
  int i;
   if(!stringp(word) && !pointerp(word))
      return log_bad_type(word);
   type = word;
   if(stringp(word)) {
     if(CLOTHING_HANDLER->query_equivilant_type(word))
       type = CLOTHING_HANDLER->query_equivilant_type(word);
     if(!CLOTHING_HANDLER->query_valid_type(word))
       log_bad_type( word );
     return;
   }
   for(i=0; i<sizeof(word); i++) {
     if(CLOTHING_HANDLER->query_equivilant_type(word[i]))
       type[i] = CLOTHING_HANDLER->query_equivilant_type(word[i]);
     if (!CLOTHING_HANDLER->query_valid_type(word[i]))
       log_bad_type( word );
     return;
   }
}
int modify_value( int amount ) {
   return ( amount * ( 10 + ( 90 * query_cond() ) / query_max_cond() ) ) / 100;
}
void player_wear() {
   if ( !environment() ) {
      return;
   }
   environment()->wear_armour( this_object() );
}
void break_me() {
   if ( !worn_by ) {
      return condition::break_me();
   }
   tell_object( worn_by, "%^RED%^$C$"+ (string)this_object()->the_short() +
         " breaks!%^RESET%^\n" );
   tell_room( environment( worn_by ), (string)worn_by->the_short() +"'s "+
         this_object()->short( 0 ) +" breaks!\n", worn_by );
   worn_by->remove_armour( this_object() );
   if((int)this_object()->move("/room/rubbish") != MOVE_OK)
     move_object("/room/rubbish");
}
mixed *stats() {
   int i;
   string *stuff;
   stuff = condition::stats() +
      ({
         ({ "type", type }),
      });
   if ( sizeof( wear_effects ) ) {
      for ( i = 0; i < sizeof( wear_effects ); i++ ) {
         stuff += ({ ({ "wear effect", wear_effects[ i ] }) });
      }
   }
   for ( i = 0; i < sizeof( immune_to ); i++ ) {
      stuff += ({ ({ "immune to", immune_to[ i ] }) });
   }
   if (worn_by) {
      stuff += ({ ({ "worn by", worn_by->short() }) });
   }
   return stuff;
}
mapping query_static_auto_load() {
   return ([
      "condition" : condition::query_static_auto_load(),
      "type" : type,
      "wear remove func" : wear_remove_func
   ]);
}
mapping query_dynamic_auto_load() {
   return ([
      "condition" : condition::query_dynamic_auto_load(),
      "wear effects" : wear_effects,
      "immune" : immune_to,
      "worn" : ( worn_by != 0 )
   ]);
}
void init_static_arg( mapping map ) {
   if ( map[ "type" ] )
      type = map[ "type" ];
   if ( map[ "wear remove func" ] )
      wear_remove_func = map[ "wear remove func" ];
   if ( !undefinedp( map[ "condition" ] ) ) {
      condition::init_static_arg( map[ "condition" ] );
   }
#ifdef AFTER_1999_I_BELIEVE
   else {
      if ( !undefinedp( map[ "max cond" ] ) )
         max_cond = map[ "max cond" ];
      if ( !undefinedp( map[ "damage chance" ] ) )
         damage_chance = map[ "damage chance" ];
   }
#endif
}
void init_dynamic_arg( mapping map, object ) {
   if ( map[ "effect" ] )
      wear_effects = ({ map[ "effect" ] });
   if ( pointerp( map[ "wear effects" ] ) )
      wear_effects = map[ "wear effects" ];
   if ( map[ "immune" ] )
      immune_to = map[ "immune" ];
   if ( map[ "worn" ] )
      call_out( "player_wear", 0 );
   if ( !undefinedp( map[ "condition" ] ) ) {
      condition::init_dynamic_arg( map[ "condition" ] );
   }
#ifdef AFTER_1999_I_BELIEVE
   } else {
      cond = map[ "cond" ];
      lowest_cond = map[ "lowest cond" ];
   }
#endif
}
void remove_wear_remove_func() {
    wear_remove_func = ({ });
}