# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/races/cabbage.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "cabbage" )
            set_long("A green, leafy vegetable.  Probably full of vitamins and "+
            "minerals, and plenty of roughage.\n" )
            set_height( 20 )
            set_weight( 40 )
            set_desc( "a cute little green-fronded cabbage.  Awww" )
            set_skin( "fronds" )
            bits = ({
            "frond", "frond", [0, 100, ({"/std/bit", 10})],
            "stalk", "stalk", [0, 500, 0]
            })
            inedible = [})
            unrottable = [})
            set_stats( [-4, -4, -6, -4, -6] )


    def player_heart_beat(self, word: str, brassica: MudObject) -> None:
            object *caterpillars
            if( !environment( brassica ) ) {
            return


    def set_unarmed_attacks(self, thing: MudObject) -> None:
            int number
            number = (int)thing.query_skill_bonus( "fighting.combat.melee.unarmed" )
            number = 4 + sqrt( number ) / 2
            thing.remove_attack( "hands" )
            thing.remove_attack( "feet" )
            thing.remove_attack( "fronds" )
            thing.add_attack( "fronds", 160, [4 * number, 5, 3 * number],
            "sharp", "unarmed", 0 )
            thing->add_attack_message( "fronds", "sharp", ({
            50, "$N scratch$es $P $z with a frond.\n",
            100, "$N jab$s a sharp frond into $P $z.\n",
            140, "$N chew$s on $P $z.\n",
            180, "$N slash$es $P $z with $p fronds.\n",
            230, "$N climb$s onto %I and cuts $P $z with a sharp frond.\n",
            0, "$N bite$s $P $z off!\n"] )
            thing.tactics( "response dodge" )
            thing.tactics( "attitude offensive" )



class Cabbage(MudObject):
