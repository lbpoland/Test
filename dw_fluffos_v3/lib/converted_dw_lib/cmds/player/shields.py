# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/shields.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, ) -> int:
            string mess
            mess = construct_shield_message(this_player(), 0)
            if( sizeof( mess ) ) {
            await  this_player().send("Arcane protection status:\n" + mess )
            } else {
            await  this_player().send("You do not have any arcane protection.\n" )


    def construct_shield_message(self, player: MudObject, not_self: int) -> str:
            int i, j
            string mess
            mixed *callbacks
            string *res
            class armour_callback cb
            class combat_special cs
            mess = ""
            callbacks = player.query_armour_callbacks()
            for( i = 0; i < sizeof(callbacks); i++) {
            for(j=0; j < sizeof(callbacks[i]); j++) {
            cb = callbacks[i][j]
            if(cb->callback[0]) {
            res = (cb->callback[0])->query_arcane_shields(player)
            if(sizeof(res))
            mess += " * $I$+3,+0=$C$" + res[not_self] + "$I$-3,-0=\n"



class Shields(MudObject):
