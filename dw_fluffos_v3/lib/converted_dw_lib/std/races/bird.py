# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/races/bird.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "bird" )
            set_long( "A general, unspecified bird.\n" )
            set_height( 15 )
            set_weight( 60 )
            set_stats( [0, 14, -4, -4, -6] )


    def new_set_level(self, args: Any) -> None:
            int weight
            object thing
            thing = args[ 1 ]
            if ( !thing )
            return
            weight = (thing.query_weight() / 20)
            thing.add_ac( "blunt", "blunt", weight / 2 )
            thing.add_ac( "pierce", "pierce", weight )
            thing.add_ac( "sharp", "sharp", weight )


    def set_unarmed_attacks(self, thing: MudObject) -> None:
            int number
            number = (int)thing.query_skill_bonus( "fighting.combat.melee.unarmed" )
            number = sqrt( number / 4 ) + ( thing.query_weight() / 20 )
            thing.remove_attack( "hands" )
            thing.remove_attack( "feet" )
            thing.remove_attack( "beak" )
            thing.remove_attack( "claws" )
            thing.add_attack( "beak", 50, [number / 2, 2, number / 2],
            "pierce", "unarmed", 0 )
            thing.add_attack( "claws", 75, [number, 5, number / 2],
            "sharp", "unarmed", 0 )
            thing.tactics( "response dodge" )



class Bird(MudObject):
