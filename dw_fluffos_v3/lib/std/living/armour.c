#include <clothing.h>
#include <function.h>
#include <race.h>
#include <armour.h>
inherit "/std/armour_logic";
#undef INFORM 1
nosave string skin;
nosave object *wearing;
nosave mixed stopped;
nosave mixed *_armour_callbacks;
nosave int *_cids;
void create() {
   skin = "morphological field";
   wearing = ({ });
   if(!_armour_callbacks)
     _armour_callbacks = ({ ({ }), ({ }), ({ }) });
   if(!_cids)
     _cids = ({ 0, 0, 0 });
   ::create();
}
int register_armour_callback(int level, mixed callback, mixed data) {
  _armour_callbacks[level] += ({ new(class armour_callback,
                                     id : ++(_cids[level]),
                                     callback: callback,
                                     data : data) });
  return _cids[level];
}
int remove_armour_callback(int level, int id) {
  int i;
  for(i=0; i<sizeof(_armour_callbacks[level]); i++) {
    if((_armour_callbacks[level][i])->id == id) {
      _armour_callbacks[level] -= ({ _armour_callbacks[level][i] });
      return 1;
    }
  }
  return 0;
}
int update_armour_callback(int level, int id, mixed data) {
  int i;
  for(i=0; i<sizeof(_armour_callbacks[level]); i++) {
    if((_armour_callbacks[level][i])->id == id) {
      _armour_callbacks[level][i]->data = data;
      return 1;
    }
  }
  return 0;
}
mixed *query_armour_callbacks() { return copy(_armour_callbacks); }
string query_skin() { return skin; }
void set_skin( string word ) { skin = word; }
object *query_wearing() {
   wearing = filter(wearing, (: $1 && environment($1) == this_object() :));
   return copy( wearing );
}
object *query_armours() {
   return query_wearing();
}
void clear_armours() {
   wearing->set_worn_by( 0 );
   wearing = ({ });
}
mixed query_stopped() {
   return stopped;
}
void set_stopped( mixed arg ) { stopped = arg; }
protected int equivalent_armour_types( mixed comp, string type ) {
   string word;
   if ( stringp( comp ) ) {
      if ( CLOTHING_HANDLER->query_equivilant_type( comp ) ) {
         return CLOTHING_HANDLER->query_equivilant_type( comp ) == type;
      }
      return comp == type;
   }
   foreach ( word in comp ) {
      if ( equivalent_armour_types( word, type ) )
         return 1;
   }
   return 0;
}
string wear_armour( object armour, int doing_hold ) {
   int no_limbs;
   string type, word, fail_mess;
   mixed types;
   object thing;
   mapping things;
   if (environment(armour) != this_object()) {
      return "must be in your inventory";
   }
   wearing -= ({ 0 });
   if (member_array(armour, wearing) > -1)
     return "since you already have " + armour->query_objective() + " on";
   types = armour->query_type();
   word = this_object()->not_allowed_to_wear( types );
   if ( word ) {
      return word;
   }
   things = ([ ]);
   if ( stringp( types ) ) {
      types = ({ types });
   }
   if ( !pointerp( types ) ) {
      return "oh dear";
   }
   foreach ( type in types ) {
      if ( CLOTHING_HANDLER->query_equivilant_type( type ) ) {
         type = CLOTHING_HANDLER->query_equivilant_type( type );
      }
      things[ type ] = ({ });
      foreach ( thing in wearing ) {
         if ( equivalent_armour_types( (mixed)thing->query_type(), type ) )  {
            things[ type ] += ({ thing });
         }
      }
   }
   word = (string)this_object()->query_race_ob();
   if ( !word )
     return "no race object";
   foreach ( type in keys( things ) ) {
      if ( (int)word->query_number_worn( type ) <= sizeof( things[ type ] ) ) {
         return "since you are already wearing "+
               query_multiple_short( things[ type ] );
      }
   }
   no_limbs = (int)armour->query_no_limbs();
   if ( no_limbs && !doing_hold ) {
      if ( member_array( armour,
            (object *)this_object()->query_holding() ) != -1 ) {
         return "already wearing";
      }
      if( sizeof( (int *)armour->hold_item( this_object(), -1 ) ) ) {
         return 0;
      } else {
         return "already holding";
      }
   }
   if ( !armour->set_worn_by( this_object() ) ) {
      if( fail_mess = armour->query_wear_failure_mess() )
         return fail_mess;
      else
         return "oh dear";
   }
   wearing += ({ armour });
   this_object()->do_burden_call();
   return 0;
}
int remove_armour( object thing ) {
   int i;
   wearing -= ({ 0 });
   i = member_array( thing, wearing );
   if ( i == -1 ) {
      return 1;
   }
   if ( !thing->set_worn_by( 0 ) ) {
      return 1;
   }
   if ( member_array( thing, (object *)this_object()->query_holding() ) != -1 ) {
      if ( !sizeof( (int *)this_object()->set_unhold( thing ) ) ) {
         return 1;
      }
   }
   wearing = delete( wearing, i, 1 );
   this_object()->do_burden_call();
   return 0;
}
varargs int query_ac( string type, int amount, string zone ) {
  int part, total, i, max;
  string word, *types;
  mixed most;
  object thing;
  object *defenses;
  stopped = 0;
#ifdef INFORM
  event( environment(), "inform", "zone "+ zone, "combat" );
#endif
  if ( !zone ) {
    switch(random(21)) {
    case 0..1: zone = "head"; break;
    case 2: zone = "neck"; break;
    case 3..6: zone="chest"; break;
    case 7..9: zone="abdomen"; break;
    case 10..12: zone = "arms"; break;
    case 13..14:
      zone = "hands"; break;
    case 15..18: zone = "legs"; break;
    case 19: zone = "feet"; break;
    case 20: zone = "back"; break;
    }
#ifdef INFORM
    event( environment(), "inform", "picked zone "+ zone,
           "combat" );
#endif
  }
  if(sizeof(_armour_callbacks[ARM_OUTER]) && amount) {
    for(i=0; i<sizeof(_armour_callbacks[ARM_OUTER]); i++) {
      if(!_armour_callbacks[ARM_OUTER][i]->callback[0])
        remove_armour_callback(ARM_OUTER,
                               _armour_callbacks[ARM_OUTER][i]->id);
      else {
        part = call_other(_armour_callbacks[ARM_OUTER][i]->callback[0],
                          _armour_callbacks[ARM_OUTER][i]->callback[1],
                          this_object(),
                          type, amount, zone,
                          _armour_callbacks[ARM_OUTER][i]->data);
        if(part > max) {
          max = part;
          most = stopped;
        }
        total += part;
        amount -= part;
        if(amount < 1)
          break;
      }
    }
  }
  if(zone != "self" && amount > 0) {
    types = CLOTHING_HANDLER->query_clothing_zone( zone );
    if(!types) {
      log_file("ARMOUR_DEBUG", "No types for zone: %s", zone);
      return 0;
    }
    foreach ( word in  types) {
      wearing -= ({ 0 });
      defenses = wearing + filter_array(this_object()->query_holding(),
                                        (: $1 && $1->query_armour() :));
      foreach ( thing in defenses )
        if ( equivalent_armour_types( (mixed)thing->query_type(), word ) ) {
#ifdef INFORM
          event( environment(), "inform", "testing object "+
                 thing->short(), "combat" );
#endif
          part = (int)thing->query_ac( type, amount, zone );
          if (!stopped && part)
            stopped = thing;
          if(part > max) {
            max = part;
            most = stopped;
          }
          total += part;
          amount -= part;
        }
      if (amount < 1)
        break;
    }
  }
  if(sizeof(_armour_callbacks[ARM_INNER]) && amount > 0) {
    for(i=0; i<sizeof(_armour_callbacks[ARM_INNER]); i++) {
      if(!_armour_callbacks[ARM_INNER][i]->callback[0])
        remove_armour_callback(ARM_INNER,
                               _armour_callbacks[ARM_INNER][i]->id);
      else {
        part = call_other(_armour_callbacks[ARM_INNER][i]->callback[0],
                          _armour_callbacks[ARM_INNER][i]->callback[1],
                          this_object(),
                          type, amount, zone,
                          _armour_callbacks[ARM_INNER][i]->data);
        if(part > max) {
          max = part;
          most = stopped;
        }
        total += part;
        amount -= part;
        if(amount < 1)
          break;
      }
    }
  }
  if(amount > 0 && this_object()->query_race_ob() &&
     function_exists("query_ac", load_object(this_object()->query_race_ob()))){
    part = (this_object()->query_race_ob())->query_ac(type, amount, zone);
    if(part > max) {
      max = part;
      most = stopped;
    }
    total += part;
    amount -= part;
  }
  if(amount > 0) {
    if(!stopped && type != "skin")
      stopped = skin;
    if(type == "fire") {
      if(this_object()->effects_matching("body.wetness") &&
         sizeof((int *)this_object()->effects_matching("body.wetness"))) {
        this_object()->add_effect("/std/effects/other/wetness", -amount );
      }
    }
    part = ::query_ac(type, amount, zone);
    if(part > max) {
      max = part;
      most = stopped;
    }
    total += part;
    amount -= part;
  }
  if(amount > 0 && most) {
    stopped = most;
  }
  return total;
}
mixed *stats() {
   return ::stats() + ({
      ({ "skin", skin }),
   });
}