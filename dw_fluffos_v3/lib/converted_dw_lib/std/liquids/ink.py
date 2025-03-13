# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/liquids/ink.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def splash_func(self, ob: MudObject) -> int:
            ob.add_extra_look(self)
            ob.add_property("splashed with", previous_object()->query_liquid_name())
            return 1


    def extra_look(self, ) -> str:
            return capitalize((string)previous_object()->query_name())+
            " has been splashed with "+
            previous_object()->query_property("splashed with")



class Ink(MudObject):
