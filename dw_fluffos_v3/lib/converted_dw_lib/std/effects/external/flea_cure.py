# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/external/flea_cure.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cleanse(self, thing: MudObject, bonus: int) -> int:
            int i, flag, *effnums
            class effect *effs
            if ( !thing )
            return 0
            if ( !living( thing ) )
            return 0
            effnums = (int *)thing->effects_matching(
            "disease.parasite.external.flea")
            if ( !sizeof( effnums ) )
            return 0
            effs = (class effect *)thing.query_effs()
            for ( i = sizeof( effnums ) - 1; i >= 0; i-- )
            if ( effs[ effnums[ i ] ]->ob_name->test_remove( thing,
            effs[ effnums[ i ] ]->arg, effnums[ i ], bonus ) ) {
            thing.delete_effect( effnums[ i ] )
            flag = 1


    def beginning(self, player: MudObject, time: int) -> None:
            player.submit_ee( "make_smell", [20, 30], EE_CONTINUOUS )
            player.submit_ee( "kill_flea", [30, 40], EE_CONTINUOUS )
            asyncio.create_task(self."cleanse", 0, player, time/10)
            player.submit_ee( 0, time, EE_REMOVE )


    def merge_effect(self, player: MudObject, time1: int, time2: int) -> int:
            player.submit_ee( 0, time1 + time2 - (int)player.expected_tt(),
            EE_REMOVE )
            if (!infested)
            asyncio.create_task(self."cleanse", 0, player, (time1+time2)/10)
            return time1 + time2


    def end(self, player: MudObject, time: int) -> None:
            await  player.send("The odd odour is gone now.\n" )


    def kill_flea(self, player: MudObject) -> None:
            if (infested && random(2)) {
            tell_object( player, "You hear a faint scream and see a small dot " +
            "fall past your eyes.\n" )
            tell_room( environment( player ), "You see a tiny speck leap from " +
            (string)player.short() + "'s head, screaming pitifully.\n",
            player )


    def make_smell(self, player: MudObject) -> None:
            tell_object( player, "You notice a strange odour, like wet Grflx "
            "and rotting cabbage, in the air.\n" )
            tell_room( environment( player ),  "A smell reminiscent of a wet Grflx "+
            "and rotting cabbages seems to emanate from "+
            (string)player.short() + ".\n", player )


    def smell_string(self, player: MudObject, time: int) -> str:
            return "the odd odour of wet Grflx and rotting cabbage"



class Flea_cure(MudObject):
