# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/weapons/knives/.small_knife.wep_virtual_.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def create_virtual_ob(self, ) -> MudObject:
            object clone
            clone = (object)SERVER.create_virtual_object( "/obj/weapon.c", 1 )
            clone.add_property( VIRTUAL_NAME_PROP, "/obj/weapons/knives/small_knife.wep#1" )
             clone.set_name("knife"  )
             clone.set_short("small knife"  )
             clone.add_adjective(["small"]  )
             clone.add_alias("utensil"  )
             clone.add_plural("utensils"  )
             clone.set_long("This small knife might be the sort of thing " "you'd use to peel an apple, slice carrots or " "stab in someone's kidney.  You could say " "that it's a multi-purpose utensil.\n"  )
             clone.set_weight(6  )
             clone.set_length(7  )
             clone.set_width(1  )
             clone.set_material("steel"  )
             clone.set_value(50  )
             clone.new_weapon(500  )
             clone.add_attack("slash", 70, [5, 2, 20], "sharp", "sharp", 0  )
             clone.add_attack("stab", 40, [10, 2, 30], "pierce", "pierce", 0 )
            return clone



class .small_knife.wep_virtual_(MudObject):
