# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/races/frog.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "frog" )
            set_long( "Frogs are amphibians" )
            set_height(10)
            set_weight(10)
            set_desc( "an innocent little froggie" )
            add_ac( "blunt", "blunt", 5 )
            add_ac( "pierce", "pierce", 4 )
            add_ac( "sharp", "sharp", 3 )
            add_attack( "bite", 50, [10, 2, 6] )
            set_sight( [5, 20, 200, 300] )
            set_stats( [-4, 10, -4, -4, -6] )


    def start_player(self, thing: MudObject) -> None:
            ::start_player( thing )
            thing.tactics( "response dodge" )



class Frog(MudObject):
