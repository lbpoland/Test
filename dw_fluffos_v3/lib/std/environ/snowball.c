#include <tasks.h>
inherit "std/object";
int strength;
void set_strength( int number );
void setup() {
   set_name( "snowball" );
   add_alias( "ball" );
   add_adjective( "snow" );
   set_strength( 99 );
   set_heart_beat( 1 );
}
int query_strength() { return strength; }
void set_strength( int number ) { strength = number; }
string long( string word, int dark ) {
   return "This is a "+ ({
      "very small lump of slush",
      "small and rather soggy lump of snow",
      "small snowball",
      "smallish snowball",
      "vaguely small snowball",
      "decent sized snowball",
      "reasonably sized snowball",
      "snowball for throwing at someone",
      "good snowball for throwing at someone",
      "nice, big snowball, just right for throwing at someone"
   })[ strength / 10 ] +".\n";
}
void init() {
    add_command( "throw", "<direct:object> {at|to} <indirect:object>" );
}
void heart_beat() {
   strength--;
   if ( strength < 1 ) {
      set_heart_beat( 0 );
      move( "/room/rubbish" );
   }
}
private object find_person(object ob) {
   if (living(ob)) {
      return ob;
   } else {
      while (ob && !living(ob)) {
         ob = environment(ob);
      }
      if (ob) {
         return ob;
      }
   }
   return 0;
}
int do_throw( object *obs ) {
   object per;
   int chance;
   per = find_person(obs[0]);
   if (per) {
      if (per != obs[0]) {
         chance = 0;
      } else {
         chance = 30;
      }
      if (per == this_player()) {
         per->add_effect( "/std/effects/external/snowball", strength );
      } else {
         switch (TASKER->compare_skills(this_player(),
                                        "fighting.combat.range.thrown",
                                        per,
                                        "fighting.combat.dodging.range",
                                        chance,
                                        TM_FREE,
                                        TM_FREE)) {
         case OFFAWARD :
            tell_object(this_player(), "%^YELLOW%^You feel more able to throw "
                                       "snowballs at people.\n%^YELLOW%^");
         case OFFWIN :
            per->add_effect( "/std/effects/external/snowball", strength );
            add_succeeded_mess( ({ "$N throw$s $D at $I and hit$s!\n",
                "$N throw$s $D at $I and hits!\n" }),  ({ obs[0] }) );
            break;
         case DEFAWARD :
            tell_object(this_player(), "%^YELLOW%^You feel more able to dodge "
                                       "snowball thrown by people.\n%^YELLOW%^");
         case DEFWIN :
            add_succeeded_mess( "$N throw$s $D at $I and miss$es!\n",
                                   ({ obs[0] }) );
            break;
         }
      }
   } else {
      add_succeeded_mess( "$N throw$s $D at $I.\n", ({ obs[ 0 ] }) );
   }
   move( "/room/rubbish" );
   return 1;
}
mapping query_dynamic_auto_load() {
   return ([
      "::" : ::query_dynamic_auto_load(),
      "strength" : strength
   ]);
}
void init_dynamic_arg( mapping map, object ) {
   ::init_dynamic_arg( map[ "::" ] );
   strength = map[ "strength" ];
}