# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/races/spider.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "spider" )
            set_long( "A small, poisonous, hairy spider.\n" )
            set_desc( "a hairy arachnid" )
            set_height( 5 )
            set_weight( 2 )
            add_bit( "silk gland", "gland", ["abdomen", 10,
            ({"/std/bit", 1, 400})] )
            add_bit( "poison gland", "gland", ["cephalothorax", 5,
            ({"/std/bit", 1, 400})] )
            inedible += ["poison gland"]
            set_stats( [-6, 4, -6, -6, -6] )


    def new_set_level(self, args: Any) -> None:
            int level
            object thing
            if( sizeof(args) < 2 || !args[1] )
            return
            level = args[ 0 ]
            thing = args[ 1 ]
            thing.add_skill_level( "other.health", level * 2 )
            thing.add_ac( "blunt", "blunt", level / 2 )
            thing.add_ac( "pierce", "pierce", level / 4 )
            thing.add_ac( "sharp", "sharp", level / 3 )


    def set_unarmed_attacks(self, thing: MudObject) -> None:
            thing.remove_attack( "hands" )
            thing.remove_attack( "feet" )
            thing.remove_attack( "standard" )
            thing.remove_attack( "bite" )
            thing.remove_attack( "chew" )
            thing.add_attack( "bite", 80, [10, 2, 5],
            "pierce", "unarmed", ["poison", self] )
            thing.add_attack( "chew", 100, [2, 2, 10],
            "sharp", "unarmed", 0 )
            thing.tactics( "response dodge" )



class Spider(MudObject):
