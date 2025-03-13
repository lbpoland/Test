# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/races/stoat.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "stoat" )
            set_long( "A small black and white animal.\n" )
            set_height( 15 )
            set_weight( 30 )
            set_desc( "small brown meateater" )
            set_stats( [-2, 8, -2, -4, -4] )


    def new_set_level(self, args: Any) -> None:
            int level
            object thing
            if( sizeof(args) < 2 || !args[1] )
            return
            level = args[ 0 ]
            thing = args[ 1 ]
            level = 1 + ( 2 * level + random( level ) ) / 8
            thing.add_ac( "blunt", "blunt", 20 + level / 3 )
            thing.add_ac( "sharp", "sharp", 50 + level )
            thing.add_ac( "pierce", "pierce", 60 + 2 * level )


    def set_unarmed_attacks(self, thing: MudObject) -> None:
            int number
            number = (int)thing.query_skill_bonus( "fighting.combat.melee.unarmed" )
            number = 4 + sqrt( number ) / 2
            thing.remove_attack( "hands" )
            thing.remove_attack( "feet" )
            thing.remove_attack( "claws" )
            thing.remove_attack( "bite" )
            thing.add_attack( "claws", 50, [( 4 * number ) / 2, 8, 2 * number],
            "sharp", "unarmed", 0 )
            thing.add_attack( "bite", 100, [2 * number, 10, ( 3 * number ) /2],
            "pierce", "unarmed", 0 )
            thing.tactics( "response dodge" )



class Stoat(MudObject):
