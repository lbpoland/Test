# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shadows/object/newbie_shoes.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def query_msgin(self, ) -> str:
            {
            return "$N stagger$s clumsily from $F."


    def query_msgout(self, ) -> str:
            {
            return "$N stagger$s $T clumsily."


    def move(self, dest: Any, inmsg: str, outmsg: str) -> int:
            {
            int ret
            ret = player.move(dest, inmsg, outmsg)
            if (ret == MOVE_OK) {
            tell_object( player, "You wince as spikes seem to drive themselves "
            "into the balls of your feet, but you get there eventually.\n" )


    def test_for_effect(self, thing: MudObject) -> int:
            return member_array( EFFECTS +"newbie_shoes",
            (string *)thing.query_wear_effects() ) != -1


    def taken_off(self, what: MudObject, eff: str) -> None:
            {
            if (eff != EFFECTS + "newbie_shoes")
            player.taken_off(what, eff)
            else {
            remove_this_effect()



class Newbie_shoes(MudObject):
