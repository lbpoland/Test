# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/races/sheep.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "sheep" )
            set_long( "The sheep is a wooly mammal.  It is possibly the most stupid "
            "animal in the universe, with the possible exception of the duck.\n" )
            set_height( 50 )
            set_weight( 800 )
            set_skin( "fleece" )
            set_desc( "a wooly sheep" )
            add_ac( "blunt", "blunt", 50 )
            add_ac( "pierce", "pierce", 20 )
            add_ac( "sharp", "sharp", 20 )
            set_stats( [0, 0, -6, -2, -6] )


    def set_unarmed_attacks(self, thing: MudObject) -> None:
            thing.remove_attack( "hands" )
            thing.remove_attack( "feet" )
            thing.remove_attack( "standard" )
            thing.remove_attack( "chew" )
            thing.remove_attack( "hoof" )
            thing.add_attack( "chew", 50, [40, 8, 10],
            "sharp", "unarmed", 0 )
            thing.add_attack( "hoof", 50, [60, 10, 40],
            "blunt", "unarmed", 0 )
            thing.tactics( "response dodge" )



class Sheep(MudObject):
