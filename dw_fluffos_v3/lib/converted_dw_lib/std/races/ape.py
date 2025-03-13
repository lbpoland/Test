# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/races/ape.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "ape" )
            set_long( "The apes are any members of the family Pongidae of large "
            "semi-erect primates, including the chimpanzee, gorilla, orangutan "
            "and gibbon.\n" )
            set_weight( 2500 )
            set_height( 175 )
            set_stats( [4, 4, 0, 4, 0] )


    def query_desc(self, thing: MudObject) -> str:
            if( (int)thing.query_gender() == 1 )
            return "He is your average hairy young male ape.\n"
            return "She is your average hairy young female ape.\n"


    def new_set_level(self, args: Any) -> None:
            int level
            object thing
            if( sizeof(args) < 2 || !args[1] )
            return
            level = args[ 0 ]
            thing = args[ 1 ]
            thing.add_ac( "blunt", "blunt", 15 + level / 10 )
            thing.add_ac( "sharp", "sharp", 10 + level / 15 )
            thing.add_ac( "pierce", "pierce", 12 + level / 12 )
            thing.reset_all()


    def query_dark(self, light: int) -> int:
            if( light < 10 ) return 1
            if( light > 200 ) return 2
            return 0


    def set_unarmed_attacks(self, thing: MudObject) -> None:
            int number
            number = (int)thing.query_skill_bonus( "fighting.combat.melee.unarmed" )
            number = 10 + ( 3 * sqrt( number ) ) / 2
            thing.remove_attack( "hands" )
            thing.remove_attack( "feet" )
            thing.add_attack( "hands", 75, [2 * number, 8, number],
            "blunt", "unarmed", "unarmed_hands" )
            thing.add_attack( "feet", 25, [3 * number, 10, number],
            "blunt", "unarmed", 0 )



class Ape(MudObject):
