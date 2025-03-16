#include <effect.h>
string query_classification() { return "misc.curse.ridcullian"; }
int merge_effect( object player, int old_arg, int new_arg, int id ) {
   player->submit_ee( 0, player->expected_tt() + new_arg, EE_REMOVE );
   tell_object(player, "You feel more concerned about your hair loss.\n");
}
int test_remove( object player, int a, int id, int bonus) {
   if (bonus > 150) return 1;
   tell_object(player, "You feel less concerned about your hair loss.\n");
   player->submit_ee(0, player->expected_tt() - bonus, EE_REMOVE);
   return 0;
}
int beginning( object player, int a, int id) {
   player->submit_ee("hair_worry", ({ 10, 20 }), EE_CONTINUOUS);
   player->submit_ee(0, a, EE_REMOVE);
   tell_object( player, "You reach up to smooth your hair, and a large "+
               "chunk of hair comes out.\n");
   tell_room( environment( player ), player->the_short() + " smooths " +
             player->query_possessive() + " hair and then stares in "+
             "horror at " + player->query_possessive() + " hands.\n",
             ({ player }) );
}
void end( object player, mixed a, int id ) {
   tell_object( player, "Ahhhh.  Your hair seems to have stopped "
               "falling out so prematurely.\n");
}
void hair_worry( object player, mixed a, int id ) {
   switch (random(5)) {
    case 0:
      player->do_say("I'm not going bald!  I mean it's "+
                     "ridiculous!  My family have never gone "+
                     "bald, except for one of my aunts!");
      break;
    case 1:
      player->do_say("I mean it wasn't there yesterday!");
      break;
    case 2:
      player->do_say("I have NOT got a bald spot!");
      break;
    case 3:
      player->do_say("Something's definitely happening, "+
                     "I can feel it in my water.");
      break;
    case 4:
      player->do_say("What about this, then?");
      break;
   }
}