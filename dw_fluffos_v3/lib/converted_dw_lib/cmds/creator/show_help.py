# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/show_help.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def show_help(self, player: MudObject, helpname: str) -> Any:
            player[0]->set_finish_func("who_did_it", self)
            WHO(player[0]) = capitalize(this_player()->query_name())
            if (!player[0]->eventForce("help "+ helpname)) {
            map_delete(globals, player[0])
            return notify_fail("The help command failed ... Did you specify the "
            "correct help subject ?\n")


    def who_did_it(self, ) -> int:
            await previous_object().send(WHO(previous_object()) +
            " wanted you to read this help file.\n")
            map_delete(globals, previous_object())
            return 1



class Show_help(MudObject):
