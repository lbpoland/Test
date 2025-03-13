# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/races/light.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "light" )
            set_long( "A small sphere of magical blue light.\n" )
            set_weight( 1 )
            set_height( 1 )
            set_desc( "a small ball of blue light hovering in the air." )
            bits = [})
            inedible = [})
            unrottable = [})
            add_ac( "fire", "fire", 1000 )
            add_ac( "sound", "sound", 1000 )
            add_ac( "acid", "acid", 1000 )
            add_ac( "gas", "gas", 1000 )
            add_ac( "mental", "mental", 100 )
            set_stats( [0, 14, -6, -6, -6] )


    def start_player(self, thing: MudObject) -> None:
            ::start_player( thing )
            thing.tactics( "response dodge" )



class Light(MudObject):
