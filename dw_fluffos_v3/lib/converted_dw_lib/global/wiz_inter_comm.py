# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/global/wiz_inter_comm.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def wiz_commands(self, ) -> None:
            add_command("block", "", (:do_block(0):))
            add_command("block", "<word'name'>", (:do_block($4[0]):))
            add_command("unblock", "<word'name'>", (:do_unblock($4[0]):))


    def do_block(self, str: str) -> int:
            if (!str) {
            if (!sizeof(imud_ignored)) {
            write("Not blocking anyone.\n")
            return 1


    def do_unblock(self, str: str) -> int:
            int idx
            if (!str)
            return notify_fail("Syntax: unblock <name>|all\n")
            if (!pointerp(imud_ignored) || !sizeof(imud_ignored))
            return notify_fail("You are not blocking anyone.\n")
            if (str == "all") {
            imud_ignored = 0
            write("Okay, unblocked everyone.\n")
            return 1


    def check_not_ignored(self, who: str) -> int:
            if (!pointerp(imud_ignored))
            return 1
            return imud_ignored.index(lower_case(who)) if lower_case(who) in imud_ignored else -1 == -1



class Wiz_inter_comm(MudObject):
