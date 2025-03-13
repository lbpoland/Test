# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/races/dog.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "dog" )
            set_long( "A street dog. I wouldn't stay too near, it could bite.\n" )
            set_desc( "a nasty dog" )
            set_height( 50 )
            set_weight( 700 )
            set_stats( [4, 10, -2, 6, -4] )


    def new_set_level(self, args: Any) -> None:
            int level
            object thing
            if( sizeof(args) < 2 || !args[1] )
            return
            level = args[ 0 ]
            thing = args[ 1 ]
            thing.add_ac( "blunt", "blunt", 40 )
            thing.add_ac( "sharp", "sharp", 20 )
            thing.add_ac( "pierce", "pierce", 10 )
            thing.add_skill_level( "other.perception", 200 )


    def set_unarmed_attacks(self, thing: MudObject) -> None:
            int number
            number = (int)thing.query_skill_bonus( "fighting.combat.melee.unarmed" )
            number = sqrt( number )
            thing.remove_attack( "hands" )
            thing.remove_attack( "feet" )
            thing.remove_attack( "claws" )
            thing.remove_attack( "bite" )
            thing.add_attack( "claws", 100, [( 3 * number ) / 2, 5, number } ),
            "sharp", "unarmed", 0 )
            thing.add_attack( "bite", 50, [3 * number, 2, number],
            "pierce", "unarmed", 0 )
            thing.tactics( "response dodge" )



class Dog(MudObject):
