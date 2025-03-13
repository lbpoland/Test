# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/races/tree.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "tree" )
            set_long( "A tree.\n" )
            set_height( 800 )
            set_weight( 40000 )
            set_desc( "a large tree" )
            add_ac( "blunt", "blunt", 500 )
            add_ac( "sharp", "sharp", 50 )
            add_ac( "pierce", "pierce", 250 )
            add_ac( "fire", "fire", 100 )
            add_ac( "sound", "sound", 1000 )
            add_ac( "gas", "gas", 1000 )
            set_stats( [10, -6, -2, 10, 4] )


    def set_unarmed_attacks(self, thing: MudObject) -> None:
            int number
            number = (int)thing.query_skill_bonus( "fighting.combat.melee.unarmed" )
            number = 2 + sqrt( number )
            thing.remove_attack( "hands" )
            thing.remove_attack( "feet" )
            thing.remove_attack( "branches" )
            thing.add_attack( "branches", 100, [number / 2, 10, number],
            "blunt", "blunt", 0 )
            thing->add_attack_message( "branches", "blunt", ({
            0, "$N swing$s at $I with $p branches",
            20, "$N tap$s $I in the $z with $p branches",
            60, "$N hit$s $I in the $z with $p branches",
            100, "$N bruise$s $P $z with $p branches",
            140, "$N hit$s $I hard in the $z with $p branches",
            180, "$N smash$es $I in the $z with $p branches",
            220, "$N crush$es $P $z with $p branches",
            5000, "$N mash$es $P $z with $p branches"])
            thing.set_unarmed_parry(1)



class Tree(MudObject):
