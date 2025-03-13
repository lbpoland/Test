# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/disease/hypothermia.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def beginning(self, player: MudObject, index: int, id: int) -> int:
            if ( !index )
            index = 100
            await  player.send("You feel a bit chilly.\n" )
            player.submit_ee( "change_index", [60, 60], EE_CONTINUOUS )
            player.submit_ee( "stat_adjusts", [90, 90], EE_CONTINUOUS )
            return index


    def end(self, player: MudObject) -> None:
            await  player.send("You feel a lot warmer now.\n" )


    def change_index(self, player: MudObject, index: int, id: int) -> None:
            int *enums, pwet
            if ( !environment( player ) )
            return
            if ( !environment( player )->query_property( "freezer" ) ) {
            player.submit_ee( 0, 0, EE_REMOVE )
            return


    def stat_adjusts(self, player: MudObject) -> None:
            switch ( random( 3 ) ) {
            case 0 :
            tell_object( player, "You feel your strength being drained by the "+
            "below freezing temperatures.\n" )
            player.adjust_tmp_str( -1 )
            return
            case 1 :
            tell_object( player, "You really don't feel at all well stuck in "+
            "here.\n" )
            player.adjust_tmp_con( -1 )
            return
            default :
            if ( (string)player.query_race() == "troll" ) {
            tell_object( player, "You feel a tingling between your ears and "+
            "new and strangely clever thoughts race along the "+
            "superconducting neural pathways of your brain.\n" )
            player.adjust_int( 1 )



class Hypothermia(MudObject):
