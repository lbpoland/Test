# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/npc/drink_silly.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def normalise(self, arg: Any, player: MudObject) -> Any:
            if (stringp(arg)) {
            arg = [arg, player]
            } else if (functionp(arg)) {
            arg = [arg, player]
            } else if (!pointerp(arg)) {
            arg = [})


    def beginning(self, player: MudObject, arg: Any, id: int) -> None:
            player.submit_ee("buy_something", 5, EE_CONTINUOUS)
            player.do_command("stand at bar")
            return normalise(arg, player)


    def merge_effect(self, player: MudObject, time1: int, time2: int, id: int) -> int:
            return normalise(time1, player) + normalise(time2, player)


    def end(self, player: MudObject, arg: Any, id: int) -> None:
            int i
            for (i = 0; i < sizeof(arg); i += 2) {
            if (functionp(arg[i])) {
            evaluate(arg[i])
            } else {
            call_other(arg[i], arg[i+1])


    def buy_something(self, player: MudObject, arg: Any, id: int) -> None:
            mapping items
            mixed *stuff
            string *rabbit
            int i
            int value
            mixed ret
            string place
            string name
            class menu_item menu
            items = environment(player)->query_menu_items()
            rabbit = [})
            if (mapp(items)) {
            stuff = keys(items)
            place = environment(player)->query_property( "place" )
            if ( !place || ( place == "" ) ) {
            place = "default"



class Drink_silly(MudObject):
