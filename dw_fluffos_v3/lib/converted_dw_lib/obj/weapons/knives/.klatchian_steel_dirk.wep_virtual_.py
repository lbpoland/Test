# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/weapons/knives/.klatchian_steel_dirk.wep_virtual_.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def create_virtual_ob(self, ) -> MudObject:
            object clone
            clone = (object)SERVER.create_virtual_object( "/obj/weapon.c", 1 )
            clone.add_property( VIRTUAL_NAME_PROP, "/obj/weapons/knives/klatchian_steel_dirk.wep#1" )
             clone.set_name("dirk"  )
             clone.set_short("Klatchian steel dirk"  )
             clone.add_adjective(["klatchian", "steel"]  )
             clone.add_alias("dagger"  )
             clone.add_plural("daggers"  )
             clone.set_long("This is a very long, curving knife with a wickedly sharp point.  It is made of Klatchian steel.\n"  )
             clone.set_weight(12  )
             clone.set_length(18  )
             clone.set_width(3  )
             clone.set_material("steel"  )
             clone.set_value(400  )
             clone.new_weapon(32000  )
             clone.set_damage_chance(5  )
             clone.add_attack("slash", 75, [10, 5, 20], "sharp", "sharp"  )
             clone.add_attack("stab", 50, [10, 2, 27], "pierce", "pierce" )
            return clone



class .klatchian_steel_dirk.wep_virtual_(MudObject):
