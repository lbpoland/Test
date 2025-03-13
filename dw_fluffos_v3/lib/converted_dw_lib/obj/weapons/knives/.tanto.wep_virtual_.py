# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/weapons/knives/.tanto.wep_virtual_.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def create_virtual_ob(self, ) -> MudObject:
            object clone
            clone = (object)SERVER.create_virtual_object( "/obj/weapon.c", 1 )
            clone.add_property( VIRTUAL_NAME_PROP, "/obj/weapons/knives/tanto.wep#1" )
             clone.set_name("tanto"  )
             clone.set_short("tanto"  )
             clone.add_alias("dagger"  )
             clone.add_plural(({"daggers","tantos"})  )
             clone.set_main_plural("tantos"  )
             clone.set_long("This large auriental dagger is an excellent weapon for close-in fighting.  It is short, well crafted and looks pretty durable.\n"  )
             clone.set_weight(9  )
             clone.set_length(10  )
             clone.set_width(3  )
             clone.set_material("steel"  )
             clone.set_value(4000  )
             clone.new_weapon(50000  )
             clone.set_damage_chance(2  )
             clone.add_attack("slash", 75, [0, 2, 40], "sharp", "sharp", 0  )
             clone.add_attack("stab", 50, [9, 4, 30], "pierce", "pierce", 0 )
            return clone



class .tanto.wep_virtual_(MudObject):
