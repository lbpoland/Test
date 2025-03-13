# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/object/newbie_shoes.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def chat(self, player: MudObject, arg: Any, id: int) -> None:
            {
            string *mechats = ({
            "Something's crawling inside the shoes.\n",
            "The Cobblers of Sek must've made these things!\n",
            "Did that vice just screw down tighter?\n",
            "*OUCH* that stung!\n",
            "You not-so-idly wonder who came up with these shoes.\n"
            })
            string *youchats = ({
            " winces in pain.\n",
            " mutters something about shoes.\n",
            " stumbles.\n"
            })
            if (!interactive(player)) return
            await player.send(mechats[random(sizeof(mechats))])
            tell_room(environment(player),
            player.query_cap_name() + youchats[random(sizeof(youchats))],
            [player] )


    def notify(self, player: MudObject, arg: Any, id: int) -> None:
            {
            tell_object(player,
            "A fiery pain shoots up your legs from your feet.\n")


    def beginning(self, player: MudObject, amount: int, id: int) -> None:
            {
            player.add_extra_look( self )
            player.adjust_bonus_dex(-1)
            player.submit_ee("chat", [10, 30], EE_CONTINUOUS)
            player.submit_ee("notify", 1, EE_ONCE)


    def restart(self, player: MudObject, amount: int, id: int) -> None:
            {
            beginning(player, amount, id)


    def merge_effect(self, player: MudObject, oldarg: Any, newarg: Any, id: int) -> None:
            {
            return


    def end(self, player: MudObject, amount: int, id: int) -> None:
            {
            player.remove_extra_look( self )
            player.adjust_bonus_dex(1)
            await player.send("Ahhhh!  Free from those evil shoes!\n")


    def extra_look(self, player: MudObject) -> str:
            {
            int *enums
            enums = (int *)player.effects_matching( CLASS )
            if ( !sizeof( enums ) )
            return ""
            return(capitalize(player.query_pronoun()) +
            " looks embarrassed and uncomfortable.\n")



class Newbie_shoes(MudObject):
