# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/shutdown.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, tim: int, reason: str, force: int) -> Any:
            string str
            seteuid(geteuid(this_player()))
            str = (string)this_player()->query_name()+" at "+ctime(time())
            #ifdef GAME_LOG
            log_file("GAME_LOG", "Game shutdown by ")
            log_file("GAME_LOG", str)
            log_file("GAME_LOG", " for\n")
            log_file("GAME_LOG", num + " " + reason)
            log_file("GAME_LOG", "\n\n")
            #endif
            write("Ok... shutting down game... \n")
            if (tim < 10 && (!master()->query_lord(geteuid(self)) && !force)) {
            tim = 10



class Shutdown(MudObject):
