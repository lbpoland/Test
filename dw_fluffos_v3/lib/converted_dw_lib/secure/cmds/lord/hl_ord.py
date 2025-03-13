# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/cmds/lord/hl_ord.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, ) -> Any:
            int i
            mixed *hist
            if (!master()->query_lord((string)geteuid(this_player())))
            return 0
            seteuid(geteuid(this_player()))
            hist = HIST.query_lord_history()
            if (!pointerp(hist) || !sizeof(hist))
            return notify_fail("Nobody said anything on the lord channel.\n")
            write("The lord channel history is:\n")
            for (i=0;i<sizeof(hist);i++) {
            if (sizeof(hist[i]) > 2) {
            efun::tell_object(this_player(),
            this_player()->fix_string(sprintf("*%s* %s%-=*s\n",
            ctime(hist[i][2])[11..18], hist[i][0],
            (int)this_player()->query_cols()-strlen(hist[i][0])-11,
            hist[i][1])))


    def dest_me(self, ) -> None:
            destruct(self)


    def clean_up(self, ) -> None:
            dest_me()


    def reset(self, ) -> None:
            dest_me()



class Hl_ord(MudObject):
