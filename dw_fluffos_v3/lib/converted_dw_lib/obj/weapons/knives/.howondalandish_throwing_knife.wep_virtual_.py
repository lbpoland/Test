# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/weapons/knives/.howondalandish_throwing_knife.wep_virtual_.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def create_virtual_ob(self, ) -> MudObject:
            object clone
            clone = (object)SERVER.create_virtual_object( "/obj/weapon.c", 1 )
            clone.add_property( VIRTUAL_NAME_PROP, "/obj/weapons/knives/howondalandish_throwing_knife.wep#1" )
             clone.set_name("knife"  )
             clone.add_adjective(["howondalandish", "throwing"]  )
             clone.set_short("howondalandish throwing knife"  )
             clone.set_main_plural("howondalandish throwing knives"  )
             clone.set_long("From one of the more remote Howondalandish tribes, this knife "   "doesn't look throwable, much less a knife.  From a short handle, "   "spiky steel blades jut out at all angles, sure to deliver a nasty "   "shock to whoever gets hit with it.\n"  )
             clone.set_weight(9  )
             clone.set_length(9  )
             clone.set_width(3  )
             clone.set_material("steel"  )
             clone.new_weapon(200  )
             clone.set_damage_chance(10  )
             clone.add_attack("stab", 60, [40, 3, 30], "pierce", "pierce", 0  )
             clone.add_attack("slash", 60, [25, 5, 30], "sharp", "sharp", 0  )
             clone.set_value(7000 )
            return clone



class .howondalandish_throwing_knife.wep_virtual_(MudObject):
