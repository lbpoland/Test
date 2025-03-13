# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/weapons/knives/.sharp_butter_knife.wep_virtual_.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def create_virtual_ob(self, ) -> MudObject:
            object clone
            clone = (object)SERVER.create_virtual_object( "/obj/weapon.c", 1 )
            clone.add_property( VIRTUAL_NAME_PROP, "/obj/weapons/knives/sharp_butter_knife.wep#1" )
             clone.set_name("knife"  )
             clone.set_short("sharp butter knife"  )
             clone.set_main_plural("sharp butter knives"  )
             clone.add_adjective(["sharp", "butter"]  )
             clone.add_alias(["utensil"]  )
             clone.add_plural("knives"  )
             clone.set_long("This is a butter knife that has been sharpened a bit.\n"  )
             clone.set_weight(3  )
             clone.set_length(6  )
             clone.set_width(1  )
             clone.set_material("steel"  )
             clone.set_value(75  )
             clone.new_weapon(500  )
             clone.add_attack("slash", 70, [15, 2, 20], "sharp", "sharp", 0  )
             clone.add_attack("stab", 40, [20, 2, 30], "pierce", "pierce", 0 )
            return clone



class .sharp_butter_knife.wep_virtual_(MudObject):
