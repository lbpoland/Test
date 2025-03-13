# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/cmds/creator/locks.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, string) -> int:
            string *bits, rcspath, *files, path, tmp
            files = get_dir(this_player()->query_current_path()+"/")
            write("locked files in this directory:\n")
            foreach(path in files) {
            path = this_player()->query_current_path() + "/" + path
            bits = explode(path, "/")
            if(sizeof(bits) > 2) {
            rcspath = "/" + implode(bits[0..sizeof(bits)-2], "/") + "/RCS/"
            } else if(sizeof(bits) == 2) {
            rcspath = "/" + bits[0] + "/RCS/"
            } else
            rcspath = "/"
            rcspath += bits[sizeof(bits)-1] + ",v"
            if(file_size(rcspath) > 0) {
            tmp = read_file(rcspath, 4, 1)
            if(tmp == "locks\n") {
            string lockname
            tmp = read_file(rcspath, 5, 1)
            sscanf(tmp, "\t%s:", lockname)
            printf("%s locked by %s\n", path, lockname)


    def help(self, ) -> str:
            return "Displays the files that are locked in your current directory."



class Locks(MudObject):
