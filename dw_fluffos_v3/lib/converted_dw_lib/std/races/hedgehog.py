# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/races/hedgehog.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "hedgehog" )
            set_long( "A snail and worm eating little bugger.\n" )
            set_height( 30 )
            set_weight( 150 )
            set_desc( "A small spiny hedgehog" )
            set_stats( [2, -2, -4, -2, -6] )


    def new_set_level(self, args: Any) -> None:
            int level
            object thing
            if( sizeof(args) < 2 || !args[1] )
            return
            level = args[ 0 ]
            thing = args[ 1 ]
            level = 1 + ( 2 * level + random( level ) ) / 10
            thing.add_ac( "blunt", "blunt", level )
            thing.add_ac( "sharp", "sharp", 2 + level )
            thing.add_ac( "pierce", "pierce", 2 * level )


    def set_unarmed_attacks(self, thing: MudObject) -> None:
            int number
            number = (int)thing.query_skill_bonus( "fighting.combat.melee.unarmed" )
            number = sqrt( number )
            thing.remove_attack( "hands" )
            thing.remove_attack( "feet" )
            thing.remove_attack( "bite" )
            thing.remove_attack( "claws" )
            thing.add_attack( "bite", 100, [number / 2, 2, number],
            "pierce", "unarmed", 0 )
            thing.add_attack( "claws", 150, [number / 2, 2, number],
            "sharp", "unarmed", 0 )
            thing.tactics( "response dodge" )



class Hedgehog(MudObject):
