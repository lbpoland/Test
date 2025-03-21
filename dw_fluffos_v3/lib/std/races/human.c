inherit "/std/races/humanoid";
void setup() {
   set_long("The human race.  The standard by which all the races are set, "+
           "this is race can be considered the norm.\n");
   set_name("human");
   set_weight(1600);
   set_height(175);
   add_ac( "blunt", "blunt", 3 );
   add_ac( "pierce", "pierce", 2 );
   add_ac( "sharp", "sharp", 2 );
   set_sight( ({ 5, 25, 200, 300 }) );
}
string query_desc( object thing ) {
  if ( (int)thing->query_gender() == 1 )
    return "He is a strapping young human lad.\n";
  if ( (int)thing->query_gender() == 2 )
    return "She is a strapping young human lass.\n";
  return "It is a strapping young human.\n";
}
void set_unarmed_attacks( object thing ) {
   int number;
   number = (int)thing->query_skill_bonus( "fighting.combat.melee.unarmed" );
   number = 4 + sqrt( number );
   thing->remove_attack( "hands" );
   thing->remove_attack( "feet" );
   thing->add_attack( "hands", 75, ({ 2 * number, 5, number }), "blunt",
         "unarmed", "unarmed_hands" );
   thing->add_attack( "feet", 25, ({ 3 * number, 7, number }), "blunt",
         "unarmed", 0 );
}
string temperature_effects(object thing, int temperature) {
  string temperature_str;
  switch(temperature/3) {
  case 101 .. 1000:
    thing->dest_hide_shadow();
    tell_object( thing, "The heat is just too much for you.\n" );
    tell_room( environment( thing ), "Sweating profusely and turning "
               "a nasty red-purple colour "+
               (string)thing->the_short() +" expires.\n", thing );
    thing->do_death();
    temperature_str = "";
    break;
  case 81 .. 100:
    temperature_str = "close to death from extreme heatstroke";
    thing->adjust_tmp_wis(-1);
    thing->adjust_tmp_int(-1);
    break;
  case 51 .. 80:
    temperature_str = "sick from heatstroke";
    if(!random(2))
      thing->adjust_tmp_wis(-1);
    if(!random(2))
      thing->adjust_tmp_int(-1);
    break;
  case 21 .. 50:
    temperature_str = "very hot";
    tell_object(thing, "You feel really hot.\n");
    break;
  case 11 .. 20:
    temperature_str = "rather warm";
    tell_object(thing, "You feel quite warm.\n");
    break;
  case -10 .. 10:
    temperature_str = "";
    break;
  case -20 .. -11 :
    temperature_str = "rather cold";
    tell_object(thing, "You feel quite cold.\n");
    break;
  case -50 .. -21 :
    temperature_str = "very cold";
    tell_object(thing, "You feel cold to your bones.\n");
    break;
  case -80 .. -51 :
    temperature_str = "sick from hypothermia";
    tell_object(thing, "You're so cold you feel your energy being drained.\n");
    if(!random(2))
      thing->adjust_tmp_str(-1);
    if(!random(2))
      thing->adjust_tmp_con(-1);
    break;
  case -100 .. -81 :
    temperature_str = "close to death from extreme hypothermia";
    tell_object(thing, "You're so cold you feel as though you're about to "
                "expire.\n");
    thing->adjust_tmp_str(-1);
    thing->adjust_tmp_con(-1);
    break;
  case -1000 .. -101:
    thing->dest_hide_shadow();
    tell_object( thing, "The cold is just too much for you.\n" );
    tell_room( environment( thing ), "Frost riming "+
               (string)thing->query_possessive() +" skin in a thick crust, "+
               (string)thing->the_short() +" expires.\n", thing );
    thing->do_death();
    temperature_str = "";
    break;
  }
  if(temperature /5 >  10) {
    thing->new_parser("sweat");
    thing->add_effect("/std/effects/other/wetness",
                      temperature);
  } else if(temperature/5 < -10) {
    thing->new_parser("shiver");
    if(temperature < -30 && !random(250))
      thing->add_effect( "/std/effects/disease/common_cold",
                         -(temperature*10));
  }
  return temperature_str;
}