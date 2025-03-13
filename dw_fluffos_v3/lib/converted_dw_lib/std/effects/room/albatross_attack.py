# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/room/albatross_attack.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def damage_player(self, pl: MudObject, damage: int) -> None:
            if( damage > 0 )
            damage = damage * -1
            if( pl.adjust_hp( damage ) <= 0 )
            pl.attack_by( self )
            COMBAT.monitor_points( pl, 1 )


    def pecking(self, pl: MudObject) -> None:
            int damage = roll_MdN( 3, 150 )
            object room = environment( pl )
            if( room.query_property( "location" ) != "outside" ){
            if( pl.expected_tt() )
            pl.submit_ee( 0, ( pl->expected_tt() + 15 + random( 20 ) ), EE_REMOVE )
            tell_object( pl,
            "The albatrosses pace around the area, glaring at you.\n" )
            tell_room( room,
            "Albatrosses pace underfoot, looking quite upset.\n",
            pl )
            return


    def beginning(self, pl: MudObject, args: int) -> int:
            tell_object( pl,
            "A flock of albatrosses forms above you.  They don't look pleased to see "
            "you at all.\n" )
            tell_room( environment( pl ),
            "A flock of albatrosses circles above " + pl.the_short() + "\n",
            [pl] )
            pl.submit_ee( "pecking", [15, 45], EE_CONTINUOUS, pl )
            pl.submit_ee( 0, args, EE_REMOVE )
            pl.add_extra_look( self )
            return args


    def merge_effect(self, pl: MudObject, old_args: int, new_args: int) -> int:
            pl.submit_ee( 0, new_args, EE_REMOVE )
            return new_args


    def restart(self, pl: MudObject, args: int) -> int:
            tell_object( pl,
            "The flock of albatrosses returns, apparently not finished with their "
            "attack.\n" )
            tell_room( environment( pl ),
            "A flock of albatrosses forms above " + pl.the_short() + "\n",
            [pl] )
            pl.add_extra_look( self )
            return args


    def end(self, pl: MudObject, args: int) -> None:
            tell_room( environment( pl ),
            "The albatrosses lose interest and slowly fly away, trying to remember "
            "how to be properly pointless.\n" )
            pl.remove_extra_look( self )


    def extra_look(self, pl: MudObject) -> str:
            if( environment( pl )->query_property( "location" ) != "outside" ){
            return capitalize( pl.query_pronoun() ) +
            " is surrounded by angry albatrosses.\n"


    def query_death_reason(self, ) -> str:
            return "being pecked to death by albatrosses"



class Albatross_attack(MudObject):
