#include <player.h>
#include <login.h>
#include <player_handler.h>
#define PLAYTESTING
int pk_check( mixed thing1, mixed thing2, int off_line ) {
   int pk1;
   int pk2;
   object ob;
   if(objectp(thing1) && objectp(thing2) &&
      interactive(thing1) && interactive(thing2) &&
      sizeof( filter( ({ thing1, thing2 }),
                      (: $1->query_creator() ||
                       $1->query_property("test character") :) )) == 1) {
     this_object()->debug_printf( "PK check between %s and %s failed!\n",
                                  thing1->query_name(),
                                  thing2->query_name() );
     return 1;
   }
   if (objectp(thing1) &&
       !interactive(thing1) &&
       thing1->query_owner_pk_check()) {
       thing1 = thing1->query_owner_pk_check();
   }
   if ( !objectp( thing1 ) ) {
      ob = this_object()->find_player(thing1);
      if (ob) {
         thing1 = ob;
      }
   }
   if (objectp(thing1) && userp(thing1)) {
      pk1 = thing1->query_player_killer() &&
            interactive(thing1);
   } else if (stringp(thing1)) {
      if (off_line && stringp(thing1)) {
         if (PLAYER_HANDLER->test_user(thing1)) {
           pk1 = PLAYER_HANDLER->test_player_killer(thing1);
         } else {
            return 0;
         }
      } else {
         return 0;
      }
   } else {
      return 0;
   }
   if (objectp(thing2) &&
       !interactive(thing2) &&
       thing2->query_owner_pk_check()) {
       thing2 = thing2->query_owner_pk_check();
   }
   if ( !objectp( thing2 ) ) {
      ob = this_object()->find_player(thing2);
      if (ob) {
         thing2 = ob;
      }
   }
   if (objectp(thing2) && userp(thing2)) {
      pk2 = thing2->query_player_killer() &&
            interactive(thing2);
   } else if (stringp(thing2)) {
      if (off_line && stringp(thing2)) {
         if (PLAYER_HANDLER->test_user(thing2)) {
            pk2 = PLAYER_HANDLER->test_player_killer(thing2);
         } else {
            return 0;
         }
      } else {
         return 0;
      }
   } else {
      return 0;
   }
   return !pk1 || !pk2;
}
int pk_assist(mixed assister, mixed assistee, int off_line ) {
  object ob;
  if(objectp(assistee) && !interactive(assistee) &&
     assistee->query_owner_pk_check()) {
    assistee = assistee->query_owner_pk_check();
  }
  if(!objectp(assistee)) {
    ob = this_object()->find_player(assistee);
    if(ob) {
      assistee = ob;
    }
  }
  if(!objectp(assistee) || !assistee->query_player_killer())
    return 0;
  if(objectp(assister) &&
     !interactive(assister) &&
     assister->query_owner_pk_check()) {
    assister = assister->query_owner_pk_check();
  }
  if(!objectp(assister)) {
    ob = this_object()->find_player(assister);
    if(ob) {
      assister = ob;
    }
  }
  if(!objectp(assister) || !userp(assister) || assister->query_player_killer())
    return 0;
  return sizeof(filter(assistee->query_attacker_list(),
                       (: $1->query_player_killer() :))) > 0;
}