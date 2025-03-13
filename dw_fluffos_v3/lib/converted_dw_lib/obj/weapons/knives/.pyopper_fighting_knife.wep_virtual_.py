# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/weapons/knives/.copper_fighting_knife.wep_virtual_.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def create_virtual_ob(self, ) -> MudObject:
            object clone
            clone = (object)SERVER.create_virtual_object( "/obj/weapon.c", 1 )
            clone.add_property( VIRTUAL_NAME_PROP, "/obj/weapons/knives/copper_fighting_knife.wep#1" )
             clone.set_name("knife"  )
             clone.set_short("copper fighting knife"  )
             clone.set_main_plural("copper fighting knives"  )
             clone.add_adjective(["copper", "fighting"]  )
             clone.set_long("This Djelian copper knife is designed for fighting.  Its straight blade and hilt are undecorated, clean and functional.\n"  )
             clone.set_weight(9  )
             clone.set_length(10  )
             clone.set_width(2  )
             clone.set_material("copper"  )
             clone.set_value(180  )
             clone.new_weapon(32000  )
             clone.add_attack("slash", 100, [10, 5, 15], "sharp", "sharp"  )
             clone.add_attack("stab", 50, [10, 2, 20], "pierce", "pierce" )
            return clone



class Opper_fighting_knife.wep_virtual_(MudObject):
