#include <effect.h>
string query_classification() { return "corpse.transformation.vampire"; }
void beginning( object corpse, mixed *args ) {
   corpse->add_extra_look( this_object() );
   corpse->submit_ee( "corpse_action", 10, EE_CONTINUOUS );
}
mixed *merge_effect( object corpse, mixed *old_args, mixed *new_args ) {
   return new_args;
}
void end( object corpse, mixed *args ) {
   object ob, vampire;
   tell_room( environment(corpse), "The corpse's eyes snap open, and a "
      "vicious grin spreads across its face.  It rises upwards without "
      "bothering to push away from the ground, standing upright, its eyes "
      "flashing.  You notice that the fangs of the corpse look considerably "
      "longer than they used to.\n" );
   vampire = clone_object( "/d/ram/chars/Uberwald/corpse_vampire" );
   vampire->setup_vampire( args[0], args[1] );
   vampire->move( environment( corpse ), vampire->the_short() + " glances "
      "down at " + vampire->query_objective() + "self and grimaces.  " +
      capitalize( vampire->query_pronoun() ) + " waves one arm and is "
      "instantly clothed in more fitting garments.\n"  );
   vampire->do_command( "grin viciously" );
   corpse->clear_armours();
   foreach( ob in all_inventory( corpse ) ) {
      ob->move( environment( corpse ) );
   }
   corpse->remove_extra_look( this_object() );
   corpse->move( "/room/rubbish" );
}
void corpse_action( object corpse, mixed *args ) {
   int rate;
   object *stuff;
   stuff = all_inventory (corpse);
   rate = (int) (corpse->query_decay());
  if( sizeof( stuff ) ) {
    tell_room( environment(corpse), corpse->one_short() + " twitches "
         "slightly.\n" );
    if (rate < 20) {
      tell_room( environment(corpse), corpse->one_short() + " seems to "
         "arch its back, and a faint gasp comes from its mouth.\n" );
      corpse->submit_ee( 0, 1, EE_REMOVE );
     }
    return;
   }
   switch( args[3] ) {
   case 0 :
      tell_room( environment(corpse), corpse->one_short() + " twitches "
         "slightly.\n" );
      break;
   case 1 :
      tell_room( environment(corpse), corpse->one_short() + " jerks "
         "violently, its limbs quivering.\n" );
      break;
   case 2 :
      tell_room( environment(corpse), corpse->one_short() + " seems to "
         "arch its back, and a faint gasp comes from its mouth.\n" );
      corpse->submit_ee( 0, 1, EE_REMOVE );
      break;
  }
   args[3]++;
}
string extra_look( object corpse, mixed *args ) {
   return "It seems to be twitching slightly, almost as if it's still "
      "alive.  You probably shouldn't get too close.\n";
}
int query_theft_command() { return -1; }