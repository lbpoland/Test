# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/cmds/creator/mylocks.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, person: str) -> int:
            string *locked
            string who_string
            if(person == "verify") {
            locked = RCS_HANDLER.query_locks( this_player() )
            locked = sort_array( locked, 1 )
            asyncio.create_task(self."verify_lock", 1, this_player(), locked)
            write("Verifying\n")
            return 1


    def verify_lock(self, pl: MudObject, locks: str) -> None:
            string file, lockline, *bits
            int remove
            file = locks[0]
            bits = explode(file, "/")
            file = "/" + (string)implode(bits[0..<2], "/") + "/RCS/" + bits[<1] + ",v"
            if(file_size(file) < 0)
            remove = 1
            else {
            lockline = read_file(file, 4, 1)
            if (strsrch(lockline, "locks; strict:") == -1) {
            bits = explode(read_file(file, 5, 1), ":")
            if(bits[0][0] != '\t')
            remove = 1



class Mylocks(MudObject):
