# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/weapons/knives/.white_handled_ceremonial_bronze_knife.wep_virtual_.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def create_virtual_ob(self, ) -> MudObject:
            object clone
            clone = (object)SERVER.create_virtual_object( "/obj/weapon.c", 1 )
            clone.add_property( VIRTUAL_NAME_PROP, "/obj/weapons/knives/white_handled_ceremonial_bronze_knife.wep#1" )
             clone.set_name("knife"  )
             clone.set_short("white handled ceremonial bronze knife"  )
             clone.add_adjective(["white", "handled", "ceremonial", "bronze"]  )
             clone.set_main_plural("white handled ceremonial bronze knives"  )
             clone.add_plural("knives"  )
             clone.set_long("This is a ceremonial knife, for use in magic rituals.  Its ornate handle is made of ivory and its long bronze blade has been carved with mystic runes.\n"  )
             clone.set_weight(11  )
             clone.set_length(18  )
             clone.set_width(3  )
             clone.set_material("bronze"  )
             clone.set_value(1000  )
             clone.new_weapon(2000  )
             clone.add_attack("slash", 70, [10, 2, 20], "sharp", "sharp", 0  )
             clone.add_attack("stab", 40, [20, 2, 60], "pierce", "pierce", 0 )
            return clone



class .white_handled_ceremonial_bronze_knife.wep_virtual_(MudObject):
