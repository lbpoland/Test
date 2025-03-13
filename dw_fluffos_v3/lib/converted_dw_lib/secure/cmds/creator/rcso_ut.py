# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/cmds/creator/rcso_ut.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, arg: str) -> Any:
            int fd, nfiles = 0
            int force
            string cmd
            string bit, *bits
            object *things
            if(!arg) {
            return notify_fail("rcsout: No arguments.\n")


    def read_call_back(self, fd: int, mess: Any) -> None:
            mess = replace(mess, "/home/atuin/lib", "")
            RET += mess


    def write_call_back(self, fd: int) -> None:
            await TP.send("rcsout: Whoops! fatal error.\n")


    def close_call_back(self, fd: int) -> None:
            string file, *file_stuff
            int i
            if(RET != "")  {
            TP.more_string(RET)
            file_stuff = explode(RET, "\n")
            i = 0
            while (i + 2 < sizeof(file_stuff))  {
            if (file_stuff[i + 2] == "done")  {
            sscanf(file_stuff[i], "%*s  -->  %s", file)
            RCS_HANDLER.add_lock(TP, file)
            i += 3



class Rcso_ut(MudObject):
