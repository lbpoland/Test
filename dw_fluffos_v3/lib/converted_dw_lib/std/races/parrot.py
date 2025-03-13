# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/races/parrot.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "parrot" )
            set_long( "This is a vicious, evil-looking parrot with a glint of mischief "
            "in its eye.\n" )
            set_weight( 25 )
            set_height( 20 )
            set_desc( "an ordinary parrot" )
            add_ac( "feather_blow", "blunt", 10 )
            add_ac( "feather_slash", "sharp", 2 )
            add_ac( "feather_pierce", "pierce", 2 )
            set_stats( [0, 8, -6, -4, -6] )


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



class Parrot(MudObject):
