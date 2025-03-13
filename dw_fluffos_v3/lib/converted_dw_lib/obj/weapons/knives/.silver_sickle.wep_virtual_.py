# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/weapons/knives/.silver_sickle.wep_virtual_.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def create_virtual_ob(self, ) -> MudObject:
            object clone
            clone = (object)SERVER.create_virtual_object( "/obj/weapon.c", 1 )
            clone.add_property( VIRTUAL_NAME_PROP, "/obj/weapons/knives/silver_sickle.wep#1" )
             clone.set_name("sickle"  )
             clone.set_short("silver sickle"  )
             clone.add_adjective("silver"  )
             clone.set_long("This is a dagger with a crescent shaped blade cast from silver.\n"  )
             clone.set_weight(9  )
             clone.set_length(12  )
             clone.set_width(8  )
             clone.set_material("silver"  )
             clone.set_value(2000  )
             clone.new_weapon(12800  )
             clone.set_damage_chance(5  )
             clone.add_attack("slash", 75, [10, 5, 15], "sharp", "sharp"  )
             clone.add_attack("stab", 50, [10, 2, 25], "pierce", "pierce" )
            return clone



class .silver_sickle.wep_virtual_(MudObject):
