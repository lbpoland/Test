# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/races/scorpion.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "scorpion" )
            set_long( "A nasty little poisonous creature, of the arachnid family.\n" )
            set_height( 5 )
            set_weight( 2 )
            set_desc( "a nasty little poisonous creature, of the arachnid family" )
            bits = ({
            "head", "head", [0, 200, 0,
            "left eye", "right eye", "mandible", "brain"],
            "left eye", "eye", ["head", 10, 0],
            "right eye", "eye", ["head", 10, 0],
            "mandible", "mouth", ["head", 50, 0],
            "brain", "brain", ["head", 25, 0],
            "thorax", "thorax", [0, 500, 0, "heart", "poison sac"],
            "heart", "heart", ["thorax", 50, 0],
            "poison sac", "sac", ["thorax", 50, 0],
            "tail", "tail", [0, 300, 0, "sting"],
            "sting", "sting", ["tail", 25, 0],
            "left claw", "claw", [0, 100, 0],
            "right claw", "claw", [0, 100, 0],
            "left front leg", "leg", [0, 50, 0],
            "left middle leg", "leg", [0, 50, 0],
            "left back leg", "leg", [0, 50, 0],
            "right front leg", "leg", [0, 50, 0],
            "right middle leg", "leg", [0, 50, 0],
            "right back leg", "leg", [0, 50, 0]
            })
            inedible = ["mandible", "left claw", "right claw"]
            unrottable = ["mandible", "left claw", "right claw"]
            set_stats( [-6, 4, -6, -6, -6] )


    def new_set_level(self, args: Any) -> None:
            int level
            object thing
            if( sizeof(args) < 2 || !args[1] )
            return
            level = args[ 0 ]
            thing = args[ 1 ]
            thing.add_skill_level( "other.health", level * 3 )
            thing.add_ac( "blunt", "blunt", level / 2 )
            thing.add_ac( "pierce", "pierce", level / 4 )
            thing.add_ac( "sharp", "sharp", level / 3 )
            thing.add_ac( "fire", "fire", level )


    def set_unarmed_attacks(self, thing: MudObject) -> None:
            int number
            number = (int)thing.query_skill_bonus( "fighting.combat.melee.unarmed" )
            number = 4 + sqrt( number )
            thing.remove_attack( "hands" )
            thing.remove_attack( "feet" )
            thing.remove_attack( "poison" )
            thing.remove_attack( "bite" )
            thing.add_attack( "sting", 70, [5 * number, 10, number],
            "pierce", "unarmed", ["poison", self] )
            thing.add_attack( "bite",  20, [3 * number, 10, number],
            "pierce", "unarmed", 0 )
            thing->add_attack_message( "sting", "pierce", ({
            0, "$N sting$s $P $z.\n"] )
            thing.tactics( "response dodge" )



class Scorpion(MudObject):
