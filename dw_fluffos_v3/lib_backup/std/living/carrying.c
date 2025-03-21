#include <clothing.h>
#include <money.h>
object* query_wearing();
protected varargs string *query_types_worn( object *things ) {
   int i;
   string *types;
   mixed *stuff;
   types = ({ });
   if ( !things ) {
      things = (object *)this_object()->query_wearing();
   }
   stuff = (mixed *)things->query_type();
   for ( i = sizeof( stuff ) - 1; i > -1; i-- ) {
      if ( stringp( stuff[ i ] ) ) {
         stuff[ i ] = ({ stuff[ i ] });
      }
      if ( !pointerp( stuff[ i ] ) ) {
         printf( "%O (%s) has an invalid type.  Please bug report it.\n",
                 things[ i ], (string)things[ i ]->query_short() );
         stuff[ i ] = ({ "broken" });
      }
      types += stuff[ i ];
   }
   return ({ types, stuff });
}
object* query_wearing_hidden(object looker, object *things) {
   mixed* bing;
   string* types;
   mixed* obj_types;
   object* worn;
   object* ret;
   int i;
   int found_under;
   string fluff;
   string under_type;
   string* under;
   if (!things) {
      worn = query_wearing();
   } else {
      worn = things;
   }
   bing = query_types_worn( worn );
   types = bing[0];
   obj_types = bing[1];
   ret = ({ });
   for (i = 0; i < sizeof(worn); i++) {
      if (worn[i]->query_visible(looker)) {
         found_under = 0;
         foreach (fluff in obj_types[i]) {
            under = CLOTHING_HANDLER->query_clothing_hiding( fluff );
            if ( under && sizeof(under)) {
               foreach (under_type in under) {
                  if (member_array(under_type, types) != -1) {
                     ret += ({ worn[i] });
                     found_under = 1;
                     break;
                  }
               }
            }
            if (found_under) {
               break;
            }
         }
      } else {
         ret += ({ worn[i] });
      }
   }
   return ret;
}
protected string armour_list( object *things, int hidden_only, int self) {
   string word;
   object* hidden;
   hidden = query_wearing_hidden( this_player(), things);
   if (hidden_only) {
      things = filter(hidden, (: $1->query_visible( this_player() ) :));
   } else {
      things = things - hidden;
   }
   if ( !sizeof( things ) ) {
      return 0;
   }
   if (!self) {
      things = sort_array(things,
               (: CLOTHING_HANDLER->query_clothing_depth($2->query_type())  -
                  CLOTHING_HANDLER->query_clothing_depth($1->query_type()) :));
   }
   word = query_multiple_short( things );
   return word;
}
string query_living_contents( int self ) {
   string s;
   string fish;
   string *limbs;
   string *bits;
   string *strs;
   object *holding;
   object *arms;
   object *carry;
   object *conts;
   object money;
   object ob;
   int i;
   int coins;
   int pos;
   s = "";
   strs = ({ });
   conts = ({ });
   limbs = this_object()->query_limbs();
   if (!limbs) {
      limbs = ( this_object()->query_race_ob() )->query_limbs();
   }
   conts = filter(all_inventory(), (: $1->short(0) :) );
   if(!limbs || !sizeof(limbs))
     holding = ({ });
   else
     holding = (object *)this_object()->query_holding() + ({ });
   arms = (object *)this_object()->query_armours() - holding;
   money = present(MONEY_ALIAS, this_object());
   if(!arms) {
      arms = ({ });
   }
   carry = conts - arms - holding - ({ money });
   for (i = 0; i < sizeof(holding); i++) {
     if (holding[i] && environment(holding[i]) == this_object()) {
       bits = ({ limbs[i] });
       ob = holding[i];
       holding[i] = 0;
       while ((pos = member_array(ob, holding)) != -1) {
         bits += ({ limbs[pos] });
         holding[pos] = 0;
       }
       strs += ({  ob->a_short() + " (" +
                     query_multiple_short(bits, "a", 1)+")" });
     }
   }
   if (sizeof(strs)) {
      s += "$I$+10,+0=%^RED%^Holding%^RESET%^ : " +
         query_multiple_short( strs ) +
         ".\n$I$-10,-0=";
   }
   if ( sizeof( arms ) ) {
      if ( fish = armour_list( arms, 0, self) ) {
         s += "$I$+10,+0=%^YELLOW%^Wearing%^RESET%^ : " + fish +
            ".\n$I$-10,-0=";
      }
      if ( self && (fish = armour_list(arms, 1, self) ) ) {
         s += "$I$+10,+0=%^YELLOW%^(under)%^RESET%^ : " + fish +
            ".\n$I$-10,-0=";
      }
   }
   if ( sizeof( carry ) ) {
      fish = this_object()->query_contents(0, carry, 1);
      if ( fish ) {
         if (pointerp(fish)) {
            s += "$I$+10,+0=%^GREEN%^" + fish[1] + "%^RESET%^: " + fish[0] +
               "$I$-10,-0=";
         } else {
            s += "$I$+10,+0=%^GREEN%^Carrying%^RESET%^: " + fish +
               "$I$-10,-0=";
         }
      }
   }
   if ( self && environment() &&
        this_object()->check_dark(environment()->query_light()) > -1) {
      if ( money ) {
         fish = query_multiple_short( (string *)money->half_short( 1 ) );
      } else {
         fish = 0;
      }
      if ( s == "" ) {
         s = "You are empty handed.\n";
      }
      s += "Your purse contains " + (fish?fish:"only moths") + ".\n";
   } else if(money) {
      coins = (int)money->query_number_coins();
      if (self) {
         s += "Your purse is ";
      } else {
         s += capitalize( (string)this_object()->query_possessive() ) +
              " purse is ";
      }
      switch(coins) {
      case 0..10:
         s += "home to only moths!\n";
         break;
      case 11..100:
         s += "tinkling with coins.\n";
         break;
      case 101..300:
         s += "bulging with coins.\n";
         break;
      default:
         s += "fit to burst!\n";
         break;
      }
   }
   return s;
}