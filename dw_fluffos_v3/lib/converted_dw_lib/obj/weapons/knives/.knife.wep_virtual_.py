# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/weapons/knives/.knife.wep_virtual_.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def create_virtual_ob(self, ) -> MudObject:
            object clone
            clone = (object)SERVER.create_virtual_object( "/obj/weapon.c", 1 )
            clone.add_property( VIRTUAL_NAME_PROP, "/obj/weapons/knives/knife.wep#1" )
             clone.set_name("knife"  )
             clone.set_short("knife"  )
             clone.add_adjective(["medium-sized", "medium"]  )
             clone.set_main_plural("knives"  )
             clone.set_long("This is a medium-sized knife, the sort of thing someone might keep in a boot to ward off a would-be attacker.  You just have to hope that it's not then used to prepare your dinner.\n"  )
             clone.set_weight(8  )
             clone.set_length(7  )
             clone.set_width(2  )
             clone.set_material("steel"  )
             clone.set_value(100  )
             clone.new_weapon(9000  )
             clone.add_attack("slash", 70, [10, 3, 20], "sharp", "sharp", 0  )
             clone.add_attack("stab", 40, [15, 3, 30], "pierce", "pierce", 0 )
            return clone



class .knife.wep_virtual_(MudObject):
