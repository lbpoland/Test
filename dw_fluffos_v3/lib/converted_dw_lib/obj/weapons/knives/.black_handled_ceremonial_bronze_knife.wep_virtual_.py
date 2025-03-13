# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/weapons/knives/.black_handled_ceremonial_bronze_knife.wep_virtual_.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def create_virtual_ob(self, ) -> MudObject:
            object clone
            clone = (object)SERVER.create_virtual_object( "/obj/weapon.c", 1 )
            clone.add_property( VIRTUAL_NAME_PROP, "/obj/weapons/knives/black_handled_ceremonial_bronze_knife.wep#1" )
             clone.set_name("knife"  )
             clone.set_short("black handled ceremonial bronze knife"  )
             clone.add_adjective(["black", "handled", "ceremonial", "bronze"]  )
             clone.set_main_plural("black handled ceremonial bronze knives"  )
             clone.add_plural("knives"  )
             clone.set_long("This is a ceremonial knife, for use in magic rituals.  Its ornate handle is made of ebony and its long bronze blade has been carved with mystic runes.\n"  )
             clone.set_weight(11  )
             clone.set_length(13  )
             clone.set_width(4  )
             clone.set_material("copper"  )
             clone.set_value(1000  )
             clone.new_weapon(2000  )
             clone.add_attack("slash", 70, [10, 2, 20], "sharp", "sharp", 0  )
             clone.add_attack("stab", 40, [20, 2, 60], "pierce", "pierce", 0 )
            return clone



class .black_handled_ceremonial_bronze_knife.wep_virtual_(MudObject):
