# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/scabbards/.dagger_scabbard.sca_virtual_.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def create_virtual_ob(self, ) -> MudObject:
            object clone
            clone = (object)SERVER.create_virtual_object( "/obj/scabbard.c", 1 )
            clone.add_property( VIRTUAL_NAME_PROP, "/obj/scabbards/dagger_scabbard.sca#1" )
             clone.set_name("scabbard"  )
             clone.add_adjective("dagger"  )
             clone.set_short("dagger scabbard"  )
             clone.set_long("Similar in design to the scabbard made for longer bladed weapons."         "  In fact you could say they were the same, except for the size.\n"  )
             clone.set_weight(3  )
             clone.set_value(30  )
             clone.set_type("small scabbard"  )
             clone.setup_scabbard(10000  )
             clone.set_damage_chance(15  )
             clone.set_types(["dagger", "knife"] )
            return clone



class .dagger_scabbard.sca_virtual_(MudObject):
