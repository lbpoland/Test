# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/disease/common_cold.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "Common Cold" )
            set_cure_rate( 6 )
            set_classification( "disease.infection.respiratory.cold" )


    def disease_start(self, player: MudObject, arg: int, sid: int) -> int:
            await  player.send("You realise that your nose is running.\n" )
            player.submit_ee2( sid, "sap_strength", [600, 600], EE_CONTINUOUS )
            return arg


    def disease_end(self, player: MudObject, arg: int, sid: int) -> None:
            if ( !player.query_property( "dead" ) )
            await  player.send("You realise that your nose is clear again.\n" )


    def disease_action(self, player: MudObject, arg: int) -> None:
            switch ( random( 3 ) ) {
            case 0 :
            player.new_parser( "sniff" )
            break
            case 1 :
            player.new_parser( "cough" )
            break
            default :
            player.new_parser( "sneeze" )


    def sap_strength(self, player: MudObject) -> None:
            await  player.send("You feel your strength being sapped by the cold.\n" )
            player.adjust_tmp_str( -1 )



class Common_cold(MudObject):
