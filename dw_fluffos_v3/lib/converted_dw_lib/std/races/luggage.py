# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/races/luggage.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "luggage" )
            set_long( "A sapient pearwood luggage.\n" )
            set_desc( "a nice set of luggage" )
            set_height( 75 )
            set_weight( 5000 )
            bits = ({
            "trunk", "trunk", [0, 400, 0],
            "lid", "lid", [0, 1000, 0],
            "leg", "leg", [0, 5, ({"/std/bit", 50})]
            })
            inedible = ["trunk", "lid"]
            unrottable = ["trunk", "lid"]
            set_skin( "casing" )
            add_ac( "blunt", "blunt", 25 )
            add_ac( "pierce", "pierce", 25 )
            add_ac( "sound", "sound", 1000 )
            add_ac( "gas", "gas", 1000 )
            set_stats( [10, 6, -2, 10, -2] )


    def set_unarmed_attacks(self, thing: MudObject) -> None:
            int number
            number = (int)thing.query_skill_bonus( "fighting.combat.melee.unarmed" )
            number = 4 + sqrt( number ) / 2
            thing.remove_attack( "hands" )
            thing.add_attack( "feet", 75, [5 * number, 10, number], "blunt",
            "unarmed", 0 )
            thing.tactics( "response dodge" )



class Luggage(MudObject):
