# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/weapons/knives/.carving_knife.wep_virtual_.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def create_virtual_ob(self, ) -> MudObject:
            object clone
            clone = (object)SERVER.create_virtual_object( "/obj/weapon.c", 1 )
            clone.add_property( VIRTUAL_NAME_PROP, "/obj/weapons/knives/carving_knife.wep#1" )
             clone.set_name("knife"  )
             clone.set_short("carving knife"  )
             clone.add_adjective(["carving"]  )
             clone.add_alias("utensil"  )
             clone.add_plural("utensils"  )
             clone.set_long("This is a knife such as you might use to carve up your Octeday roast, and then use to substantiate your arguments with your spouse as to who should do the washing up.\n"  )
             clone.set_weight(9  )
             clone.set_length(12  )
             clone.set_width(2  )
             clone.set_material("steel"  )
             clone.set_value(500  )
             clone.new_weapon(2000  )
             clone.add_attack("slash", 70, [10, 2, 20], "sharp", "sharp", 0  )
             clone.add_attack("stab", 40, [20, 2, 60], "pierce", "pierce", 0 )
            return clone



class Arving_knife.wep_virtual_(MudObject):
