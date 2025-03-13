# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/races/camel.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "camel" )
            set_long( "The camel is an animal living in desert regions.  It has two "
            "humps, a mean temper and a good eye for numbers.  They are usually "
            "named things like \"You Bastard\", \"Evil-smelling Bugger\" and so "
            "on, something that might seem strange to anyone who hasn't "
            "actually met one of the beasts.\n" )
            set_height( 170 )
            set_weight( 12000 )
            set_desc( "a camel that looks less interested in you than in sand" )
            add_bit( "tail", "tail", [0, 18, 0] )
            add_bit( "fore hump", "hump", [0, 75, 0] )
            add_bit( "aft hump", "hump", [0, 50, 0] )
            inedible += ["tail"]
            add_ac( "blunt", "blunt", 50 )
            add_ac( "pierce", "pierce", 20 )
            add_ac( "sharp", "sharp", 20 )
            add_attack( "bite", 50, [40, 8, 10] )
            add_attack( "feet", 50, [60, 10, 40] )
            set_stats( [4, 2, 10, 6, 8] )


    def start_player(self, thing: MudObject) -> None:
            ::start_player( thing )
            thing.tactics( "response dodge" )



class Camel(MudObject):
