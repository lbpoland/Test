# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/races/cat.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "cat" )
            set_long( "A carnivorous mammal (Felis catus) long domesticated and kept "+
            "by man as a pet or for catching rats and mice.\n" )
            set_height( 20 )
            set_weight( 100 )
            set_desc( "a furry cat, on the hunt for a mouse to play with" )
            set_stats( [0, 10, 2, -2, 2] )


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
            thing.add_attack( "bite", 100, [number, 5, number],
            "sharp", "unarmed", 0 )
            thing.add_attack( "claws", 150, [number / 2, 7, number],
            "sharp", "unarmed", 0 )
            thing.tactics( "response dodge" )



class Cat(MudObject):
