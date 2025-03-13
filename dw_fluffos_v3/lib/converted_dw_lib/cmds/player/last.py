# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/last.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> Any:
            string retval
            int i
            write("This command is no longer available.\n")
            return 1
            if (!str || str == "") {
            notify_fail("Usage: last <name>\n")
            return 0


    def process_file(self, fname: str, str: str) -> str:
            int size, bits, length, i
            string retval, file
            retval = ""
            seteuid("Root")
            size = file_size(fname)
            if(size > 50000) {
            length = file_length(fname)
            bits = size / 50000
            } else {
            bits = 1


    def get_details(self, str: str, file: str) -> str:
            string *sarr
            string retval
            string t2
            string type
            string time_str
            int i
            retval = ""
            sarr = explode(file, "\n")
            for (i = 0; i < sizeof(sarr); i++) {
            if (sscanf(sarr[i], "%s [%s] " + str + " ", time_str, type) == 2 ||
            sscanf(sarr[i], "%s [%s]  " + str + " ", time_str, type) == 2)  {
            switch(type)  {
            case "Enter":
            time = time_str
            logged_on = 1
            break
            case "Recon":
            time = time_str
            logged_on = 1
            break
            case "Su":
            t2 = time_str
            logged_on = 0
            retval += sprintf("%15-s %s - %s [Quit]\n", str, mtime(time),
            stime(t2))
            break
            case "NDead":
            t2 = time_str
            logged_on = 1
            retval += sprintf("%15-s %s - %s [NetDead]\n", str, mtime(time),
            stime(t2))
            time = ""
            break
            case "Exit":
            t2 = time_str
            logged_on = 0
            retval += sprintf("%15-s %s - %s [Quit]\n", str, mtime(time),
            stime(t2))
            break
            default:
            write("Someone has stuffed up... please file a bug report\n")
            break


    def mtime(self, t: str) -> str:
            if(t == "")
            return "??? ?? ??:??"
            return t[0..<4]


    def stime(self, t: str) -> str:
            if(t == "")
            return "??:??"
            return t[7..11]



class Last(MudObject):
