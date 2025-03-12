#include "path.h"
inherit "/obj/armour";
void setup()
{
  set_name("brooch");
  add_adjective( ({ "womble", "brass" }) );
  set_short("womble brooch");
  set_long("A brass brooch with a womble engraved "
    "upon it.\n");
  add_alias("jewellery");
  add_plural("jewellery");
  set_type("badge");
  setup_armour(1000);
  set_percentage(100);
  set_damage_chance(0);
  set_weight(2);
  add_property("wombles brooch", 1);
  add_property( "shop type", "jewellers" );
}