# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/other/wetness.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def beginning(self, player: MudObject, wetness: int, id: int) -> int:
            int dryness
            await  player.send("Squelch.\n" )
            player.submit_ee( "squelch", [20, 20], EE_CONTINUOUS )
            player.add_extra_look( self )
            if(dryness = (int)player.check_dryness())
            wetness -= dryness
            if ( wetness > (int)player.query_weight() )
            wetness = (int)player.query_weight()
            return wetness


    def restart(self, player: MudObject) -> None:
            player.add_extra_look( self )


    def merge_effect(self, player: MudObject, new_wetness: int, old_wetness: int, id: int) -> int:
            int wetness, dryness
            wetness = new_wetness + old_wetness
            if(dryness = (int)player.check_dryness())
            wetness -= dryness
            if ( wetness > (int)player.query_weight() )
            wetness = (int)player.query_weight()
            if ( wetness <= 0 )
            player.submit_ee(0, 0, EE_REMOVE )
            return wetness


    def end(self, player: MudObject, strength: int, id: int) -> None:
            await player.send("You feel dry now.\n")
            player.remove_extra_look( self )


    def squelch(self, player: MudObject, wetness: int, id: int) -> None:
            string loc
            object env
            int bingle
            env = environment(player)
            if(!env)
            return
            loc = (string)env.query_property("location")
            if(loc == "outside" && (int)WEATHER.query_temperature(env) > 0) {
            bingle = (int)WEATHER.query_temperature(env) / 2 +
            env.query_property("warmth")
            } else if(loc == "inside")
            bingle = (20 / 2) + env.query_property( "warmth" )
            if(player.query_personal_temp() / 3 > bingle)
            bingle -= (player.query_personal_temp() / 3)
            if(!env.query_water() && bingle > 0)
            wetness -= bingle
            if(player.query_property("dead"))
            wetness = 0
            if(wetness <= 0)
            player.submit_ee(0, 0, EE_REMOVE )
            if (wetness > 10 && !random(3) && !env.query_water() ) {
            await player.send("Squelch.\n" )


    def wet_string(self, player: MudObject, self: int) -> str:
            int wetness
            int *enums
            enums = (int *)player.effects_matching( "body.wetness" )
            if ( !sizeof( enums ) )
            return ""
            wetness = (int)player.arg_of(enums[0])
            if (!intp(wetness)) {
            wetness = 0
            player.submit_ee(0, 0, EE_REMOVE )


    def extra_look(self, player: MudObject) -> str:
            return capitalize(player.query_pronoun()) + " " + wet_string(player, 0) +
            ".\n"



class Wetness(MudObject):
