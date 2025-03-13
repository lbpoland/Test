# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/jumps.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def find_location(self, str: str) -> MudObject:
            if (find_object(str)) {
            return find_object(str)


    def do_add_jump(self, from: str, to: str) -> int:
            object from_ob
            object to_ob
            from_ob = find_location(from)
            to_ob = find_location(to)
            if (!from_ob) {
            add_failed_mess("The from location does not exist.\n")
            return 0


    def do_path_list(self, ) -> int:
            string str
            string from
            string* dest
            str = ""
            foreach (from, dest in PLAYTESTER_HAND.query_jump_points()) {
            str += from + ": " + query_multiple_short(dest) + ".\n"


    def do_remove_jump(self, from: str, to: str) -> int:
            string* dests
            dests = PLAYTESTER_HAND.query_jump_destination(from)
            if (!sizeof(dests)) {
            add_failed_mess("There are no destiations from " + from + ".\n")
            return 0



class Jumps(MudObject):
