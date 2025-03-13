# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/races/fish.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "fish" )
            set_long( "Fish,  yes.  A fish.  Nice generic standard fish thing.\n" )
            set_height( 15 )
            set_weight( 40 )
            set_desc( "a fish, the kind with fins" )
            set_stats( [-2, 14, -4, -4, -6] )


    def check_water(self, player: MudObject) -> None:
            if( !environment( player )->query_water() )
            asyncio.create_task(self. "do_drown", 4, player )


    def do_drown(self, player: MudObject) -> None:
            int i
            if( environment( player )->query_water() )
            return
            tell_room( environment( player ) , player.one_short() + " gasps for "
            "air.\n" )
            i = player.query_max_hp() / 5
            if( i < 20 ) i = 20
            player.adjust_hp( -i )
            asyncio.create_task(self. "do_drown", 4, player )


    def start_player(self, thing: MudObject) -> None:
            ::start_player( thing )
            thing.add_property( "gills", 1 )
            thing.add_property("lives in water", 1)
            thing.add_enter_commands( (: check_water :) )
            thing.set_default_position( ["lying"] )
            thing.return_to_default_position( 0 )


    def set_unarmed_attacks(self, thing: MudObject) -> None:
            int number
            number = (int)thing.query_skill_bonus( "fighting.combat.melee.unarmed" )
            number = 4 + sqrt( number ) / 2
            thing.remove_attack( "hands" )
            thing.remove_attack( "feet" )
            thing.remove_attack( "bite" )
            thing.add_attack( "bite", 100, [2 * number, 5, number],
            "pierce", "unarmed", 0 )
            thing.tactics( "response dodge" )



class Fish(MudObject):
