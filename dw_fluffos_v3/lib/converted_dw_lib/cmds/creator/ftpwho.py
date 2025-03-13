# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/ftpwho.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, string) -> Any:
            mixed *who_unix, *who
            int i
            if(!find_object(FTPD)) {
            write("MUD FTP is currently disabled.\n")
            } else {
            who = FTPD.query_connections()
            if ((i = sizeof(who))) {
            write("People currently using MUD FTP :\n")
            while (i--)
            write(" - "+who[i]+"\n")
            } else {
            write("No one is using MUD FTP at the moment.\n")



class Ftpwho(MudObject):
