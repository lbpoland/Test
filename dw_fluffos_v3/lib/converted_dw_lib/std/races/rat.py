# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/races/rat.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "rat" )
            set_long( "A rodent of the genus Rattus, distinguished from a mouse "
            "by its larger size and by structural details, as of the teeth.\n" )
            set_height( 15 )
            set_weight( 10 )
            set_desc( "a vicious-looking rat, scurrying about for food." )
            set_stats( [-4, 8, -2, -4, -4] )


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
            number = sqrt( number )
            thing.remove_attack( "hands" )
            thing.remove_attack( "feet" )
            thing.remove_attack( "bite" )
            thing.remove_attack( "claws" )
            thing.add_attack( "bite", 75, [3*number, 3, number],
            "pierce", "unarmed", 0 )
            thing.add_attack( "claws", 50, [3*number, 5, number / 2],
            "sharp", "unarmed", 0 )
            thing.tactics( "response dodge" )



class Rat(MudObject):
