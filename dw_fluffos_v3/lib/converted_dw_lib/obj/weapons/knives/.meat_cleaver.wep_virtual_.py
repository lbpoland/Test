# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/weapons/knives/.meat_cleaver.wep_virtual_.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def create_virtual_ob(self, ) -> MudObject:
            object clone
            clone = (object)SERVER.create_virtual_object( "/obj/weapon.c", 1 )
            clone.add_property( VIRTUAL_NAME_PROP, "/obj/weapons/knives/meat_cleaver.wep#1" )
             clone.set_name("cleaver"  )
             clone.set_short("meat cleaver"  )
             clone.add_alias(["utensil", "knife"]  )
             clone.add_adjective("meat"  )
             clone.set_main_plural("meat cleavers"  )
             clone.add_plural(["utensils", "knives"]  )
             clone.set_long("This is a butcher's implement for cutting animal carcasses into joints or pieces.  It is a large, rectangular knife and is quite heavy.\n"  )
             clone.set_weight(16  )
             clone.set_length(11  )
             clone.set_width(5  )
             clone.set_material("steel"  )
             clone.set_value(400  )
             clone.new_weapon(750  )
             clone.set_damage_chance(5  )
             clone.add_attack("slash", 50, [10, 4, 10], "sharp", "sharp", 0  )
             clone.add_attack("hack", 90, [20, 3, 20], "sharp", "sharp", 0 )
            return clone



class .meat_cleaver.wep_virtual_(MudObject):
