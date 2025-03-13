# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/disease/headache.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def beginning(self, player: MudObject, arg: Any) -> int:
            await player.send("Your head hurts.\n")
            player.submit_ee(0, arg, EE_REMOVE)
            player.submit_ee("pains", ({30, 60}), EE_CONTINUOUS)
            player.adjust_bonus_con(-1)
            player.adjust_bonus_dex(-1)
            player.adjust_bonus_int(-1)
            player.adjust_bonus_wis(-1)
            return arg


    def restart(self, player: MudObject, arg: Any) -> int:
            player.submit_ee("pains", ({30, 60}), EE_CONTINUOUS)
            player.adjust_bonus_con(-1)
            player.adjust_bonus_dex(-1)
            player.adjust_bonus_int(-1)
            player.adjust_bonus_wis(-1)
            return arg


    def merge_effect(self, player: MudObject, time1: int, time2: int) -> int:
            int duration
            duration = time2 + player.expected_tt()
            player.submit_ee( "end", duration, EE_REMOVE )
            player.submit_ee("pains", ({30, 60}), EE_CONTINUOUS)
            return duration


    def pains(self, player: MudObject) -> None:
            switch (random(5)) {
            case 0:
            await  player.send("Your head hurts.\n")
            tell_room( environment( player ), player.the_short()
            + " looks pained.\n",  [player] )
            break
            case 1:
            await  player.send("You clutch your aching head.\n")
            tell_room( environment( player ), player.the_short()
            + " clutches " + player.query_possessive() + " head.\n",
            [player] )
            break
            case 2:
            await  player.send("Owwwwwwwwwwww!\n")
            tell_room( environment( player ), player.the_short()
            + " moans.\n",  [player] )
            break
            case 3:
            await  player.send("Your head pounds!\n")
            tell_room( environment( player ), player.the_short()
            + " clutches " + player.query_possessive()
            + " head and moans.\n",  [player] )
            break
            case 4:
            await  player.send("Arrrrgh!  Migraine!\n")
            tell_room( environment( player ), player.the_short()
            + " whimpers.\n",  [player] )
            break


    def end(self, player: MudObject) -> None:
            await player.send("Your head feels better.\n")
            player.adjust_bonus_con(1)
            player.adjust_bonus_dex(1)
            player.adjust_bonus_wis(1)
            player.adjust_bonus_int(1)



class Headache(MudObject):
