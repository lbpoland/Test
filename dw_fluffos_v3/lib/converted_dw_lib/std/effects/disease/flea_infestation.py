# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/disease/flea_infestation.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "Fleas" )
            set_classification( "disease.parasite.external.flea" )
            set_infection_chance( 2 )
            set_infection_check( (: living( $1 ) &&
            ( ( !userp( $1 ) && !$1.query_property( "unique" ) ) ||
            $1.query_mature() ) && !$1.query_property( "dead" ) :) )


    def disease_start(self, player: MudObject, arg: int, int) -> int:
            string race_ob
            race_ob = (string)player.query_race_ob()
            if ( ( (string)race_ob.query_name() == "troll" ) ||
            player.query_property( "no fleas" ) ) {
            player.submit_ee( 0, 0, EE_REMOVE )
            return 0


    def disease_action(self, player: MudObject, int, int) -> None:
            switch( random( 14 ) ) {
            case 0 .. 3 :
            player.remove_hide_invis( "hiding" )
            await  player.send("Something itches.  You scratch yourself.\n" )
            tell_room( environment( player ), (string)player.one_short() +
            " scratches "+ (string)player.query_objective() +"self.\n",
            player )
            break
            case 4 .. 7 :
            player.remove_hide_invis( "hiding" )
            await  player.send("Ouch!  Something bit you!\n" )
            tell_room( environment( player ), (string)player.one_short() +
            " starts as if bitten.\n", player )
            player.adjust_hp( -10 - random( 10 ) )
            break
            case 8 .. 11 :
            await  player.send("You notice a small red welt on your skin.\n" )
            break
            default:


    def test_remove(self, player: MudObject, arg: int, enum: int, bonus: int) -> int:
            log_file( "OLD_CURE", file_name( previous_object() ) +" "+
            file_name( self ) +"\n" )
            if ( arg + bonus < 30 ) {
            player.set_arg_of( enum, arg + bonus )
            return 0



class Flea_infestation(MudObject):
