# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/attached/living_light.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def beginning(self, player: MudObject) -> int:
            tell_object( player, "A soft glow spreads out from your middle to "+
            "envelop you.\n" )
            tell_room( environment( player ), "A soft glow spreads out from "+
            (string)player.the_short() +"'s middle to envelop "+
            (string)player.query_objective() +".\n", player )
            player.adjust_light( INTENSITY )
            player.add_extra_look( self )
            player.submit_ee( "decrease_points", 1, EE_ONCE )
            player.submit_ee( "decrease_points", [30, 60], EE_CONTINUOUS )
            return INTENSITY


    def restart(self, player: MudObject, light: int) -> None:
            player.adjust_light( light )
            player.add_extra_look( self )


    def merge_effect(self, player: MudObject, light: int) -> int:
            int times
            times = sizeof( filter_array( (object *)player.query_armours(),
            "test_for_effect", self ) )
            if ( light >= ( INTENSITY * times ) )
            return light
            await  player.send("The light surrounding you intensifies.\n" )
            tell_room( environment( player ), "The light around "+
            (string)player.short() +" grows brighter.\n", player )
            player.adjust_light( INTENSITY )
            return light + INTENSITY


    def end(self, player: MudObject, light: int) -> None:
            tell_object( player, "The light surrounding you flickers and winks "+
            "out.\n" )
            tell_room( environment( player ), "The light around "+
            (string)player.short() +" flickers and winks out.\n", player )
            player.adjust_light( -light )
            player.remove_extra_look( self )


    def test_for_effect(self, thing: MudObject) -> int:
            if( !thing || !thing.query_wear_effects() )
            return 0
            return member_array( file_name( self ),
            (string *)thing.query_wear_effects() ) != -1


    def decrease_points(self, player: MudObject, light: int, id: int) -> None:
            int times
            if ( player.query_auto_loading() )
            return
            times = sizeof( filter_array( (object *)player.query_armours(),
            "test_for_effect", self ) )
            if ( !times ) {
            player.submit_ee( 0, 0, EE_REMOVE )
            return


    def extra_look(self, player: MudObject) -> str:
            return capitalize( (string)player.query_pronoun() ) +" is surrounded by "+
            "a soft yellow glow.\n"



class Living_light(MudObject):
