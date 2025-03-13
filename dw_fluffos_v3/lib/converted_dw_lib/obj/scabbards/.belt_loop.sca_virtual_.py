# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/scabbards/.belt_loop.sca_virtual_.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def create_virtual_ob(self, ) -> MudObject:
            object clone
            clone = (object)SERVER.create_virtual_object( "/obj/scabbard.c", 1 )
            clone.add_property( VIRTUAL_NAME_PROP, "/obj/scabbards/belt_loop.sca#1" )
             clone.set_name("loop"  )
             clone.add_adjective(["belt", "belt loop"]  )
             clone.add_alias("belt loop"  )
             clone.set_short("belt loop"  )
             clone.set_long("This loop is made from the finest leather, designed to "         "hold axes or hammers safely.\n"  )
             clone.set_weight(8  )
             clone.set_value(800  )
             clone.set_type("belt scabbard"  )
             clone.add_property("no recycling", 1  )
             clone.setup_scabbard(10000  )
             clone.set_damage_chance(15  )
             clone.set_types(["axe","hammer"] )
            return clone



class .belt_loop.sca_virtual_(MudObject):
