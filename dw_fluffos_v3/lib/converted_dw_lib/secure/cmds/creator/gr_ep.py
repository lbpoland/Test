# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/cmds/creator/gr_ep.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, arg: str) -> Any:
            int fd, search = 0, nfiles = 0
            if(!arg)
            arg = ""
            else {
            string bit, *bits = explode(arg, " ")
            arg = ""
            bits -= ({""})
            foreach(bit in bits){
            string *files, file
            if (bit[0] == '-'){
            if( ( bit == "-r" || bit == "--recursive" || bit== "-d=recurse" ||
            bit == "--directories=recurse" || bit == "-recursive" ||
            bit == "-directories=recurse" ) && !this_player()->query_lord() )
            continue
            arg += (" " + bit)
            continue


    def read_call_back(self, fd: int, mess: Any) -> None:
            mess = replace(mess, "/usr/bin/", "")
            RET += mess


    def write_call_back(self, fd: int) -> None:
            await TP.send("grep: Whoops! fatal error.\n")


    def close_call_back(self, fd: int) -> None:
            if(RET != "")
            TP.more_string(RET)
            else
            await TP.send("grep finished.\n")
            map_delete(ret, fd)
            map_delete(globals, fd)



class Gr_ep(MudObject):
