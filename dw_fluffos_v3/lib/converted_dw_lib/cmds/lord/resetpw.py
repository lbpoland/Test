# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/lord/resetpw.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def do_reset(self, player: str, newpw: str) -> int:
            string password
            string *bits, t1, t2
            int i
            if(base_name(previous_object())[0..12] != "/secure/login" &&
            base_name(previous_object())[0..13] != "/secure/nlogin") {
            if (!sizeof(filter(previous_object(-1), (: interactive($1) :)))) {
            unguarded((: write_file, "/log/CHEAT", ctime( time() ) +
            ": illegal attempt to reset password.\nTrace: " + back_trace()
            :))
            return 0


    def cmd(self, player: str, newpw: str) -> Any:
            if(!newpw || newpw == "")
            return notify_fail("Syntax: resetpw <player> <new password>\n")
            if(do_reset(player, newpw)) {
            write(sprintf("Reset password for %s to %s\n", player, newpw))
            } else {
            write("Unable to find player "+player+".\n")



class Resetpw(MudObject):
