# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/weapons/knives/.small_copper_knife.wep_virtual_.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def create_virtual_ob(self, ) -> MudObject:
            object clone
            clone = (object)SERVER.create_virtual_object( "/obj/weapon.c", 1 )
            clone.add_property( VIRTUAL_NAME_PROP, "/obj/weapons/knives/small_copper_knife.wep#1" )
             clone.set_name("knife"  )
             clone.set_short("small copper knife"  )
             clone.set_main_plural("small copper knives"  )
             clone.add_adjective(["small", "copper"]  )
             clone.set_long("This is a small, Djelian, copper knife.  Its straight blade and hilt are undecorated, clean and functional.\n"  )
             clone.set_weight(5  )
             clone.set_length(8  )
             clone.set_width(3  )
             clone.set_material("copper"  )
             clone.set_value(100  )
             clone.new_weapon(16000  )
             clone.add_attack("slash", 100, [10, 5, 10], "sharp", "sharp"  )
             clone.add_attack("stab", 50, [10, 2, 15], "pierce", "pierce" )
            return clone



class .small_copper_knife.wep_virtual_(MudObject):
