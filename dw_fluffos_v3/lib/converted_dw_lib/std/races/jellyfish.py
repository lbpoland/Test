# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/races/jellyfish.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "jellyfish" )
            set_long( "A jelly-like blob with tendrils.\n" )
            set_height( 15 )
            set_weight( 20 )
            set_desc( "a jelly-like blob with tendrils." )
            bits = ({
            "tendril", "tendril", [0, 1, ["/std/bit", 10]],
            "bell", "bell", [0, 10, 0]
            })
            inedible = ["bell", "tendril"]
            unrottable = [})
            set_skin( "exocuticule" )
            add_ac( "acid", "acid", 100 )
            add_ac( "poison", "poison", 100 )
            add_ac( "blunt", "blunt", 75 )
            add_ac( "sharp", "sharp", 25 )
            add_ac( "pierce", "pierce", 25 )
            set_stats( [-5, -5, -5, -5, -5] )


    def set_unarmed_attacks(self, thing: MudObject) -> None:
            int number
            number = (int)thing.query_skill_bonus( "fighting.combat.melee.unarmed" )
            number = 2 + (sqrt( number ) / 10)
            thing.remove_attack( "hands" )
            thing.remove_attack( "feet" )
            thing.remove_attack( "tendrils" )
            thing.add_attack( "tendrils", 100, [number, 10, number],
            "blunt", "blunt", ["sting", self] )
            thing->add_attack_message( "tendrils", "blunt", ({
            20, "$N brush$es $P $z with $p tendrils",
            60, "$N slap$s $P $z with $p tendrils",
            100, "$N knock$s $I with $p tendrils",
            140, "$N thwack$s $I with $p tendrils",
            180, "$N smack$s $p tendrils into $P $z",
            220, "$N wallop$s $I with $p tendrils",
            0, "$N hammer$s $I with $p tendrils"] )


    def start_player(self, thing: MudObject) -> None:
            ::start_player( thing )
            thing.add_property( "gills", 1 )
            thing.add_property("lives in water", 1)


    def sting(self, damage: int, him: MudObject, me: MudObject, atype: str, aname: str) -> None:
            him.add_effect(STINGEFFECT, damage)



class Jellyfish(MudObject):
