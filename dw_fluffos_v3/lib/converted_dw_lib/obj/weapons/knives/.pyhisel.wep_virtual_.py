# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/weapons/knives/.chisel.wep_virtual_.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def create_virtual_ob(self, ) -> MudObject:
            object clone
            clone = (object)SERVER.create_virtual_object( "/obj/weapon.c", 1 )
            clone.add_property( VIRTUAL_NAME_PROP, "/obj/weapons/knives/chisel.wep#1" )
             clone.set_name("chisel"  )
             clone.set_short("chisel"  )
             clone.set_long("This is a tool with a sharp edge which is used to shape and cut metal, wood, or stone.\n"  )
             clone.set_weight(11  )
             clone.set_length(6  )
             clone.set_width(3  )
             clone.set_material("steel"  )
             clone.set_value(300  )
             clone.new_weapon(19200  )
             clone.set_damage_chance(5  )
             clone.add_attack("slash", 30, [10, 3, 10], "sharp", "sharp", 0  )
             clone.add_attack("stab", 30, [10, 3, 10], "pierce", "pierce", 0 )
            return clone



class Hisel.wep_virtual_(MudObject):
