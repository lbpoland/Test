# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/races/rabbit.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "rabbit" )
            set_long( "A small furry and fluffy rabbit.\n" )
            set_height( 30 )
            set_weight( 25 )
            set_desc( "a cute and fluffy little bunny" )
            set_stats( [-3, 8, -4, -5, -6] )


    def new_set_level(self, args: Any) -> None:
            int level
            object thing
            if( sizeof(args) < 2 || !args[1] )
            return
            level = args[ 0 ]
            thing = args[ 1 ]
            thing.add_ac( "blunt", "blunt", level )
            thing.add_ac( "sharp", "sharp", 2 + level )
            thing.add_ac( "pierce", "pierce", 2 * level )


    def set_unarmed_attacks(self, thing: MudObject) -> None:
            int number
            number = (int)thing.query_skill_bonus( "fighting.combat.melee.unarmed" )
            number = sqrt( number ) / 7
            thing.remove_attack( "hands" )
            thing.remove_attack( "feet" )
            thing.remove_attack( "bite" )
            thing.add_attack( "bite", 75, [1, 3, 4],
            "pierce", "unarmed", 0 )
            thing.tactics( "response dodge" )
            thing.tactics( "attitude defensive" )



class Rabbit(MudObject):
