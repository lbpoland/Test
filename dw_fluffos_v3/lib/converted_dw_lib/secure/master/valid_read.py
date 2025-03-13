# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/master/valid_read.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def valid_read(self, path: str, euid: Any, func: str) -> int:
            mapping perms
            string prev
            if (euid == master())
            return 1
            if ((func == "file_size") || (func == "stat"))
            return 1
            if (path[0] != '/')
            path = "/" + path
            if (path[<1] == 'c' && base_name(euid)[0..2] == "/w/")
            return 0
            #ifdef FILE_STATS
            if(!read_stats)
            read_stats = ([ ])
            if(previous_object()) {
            prev = base_name(previous_object())
            if(!read_stats[prev])
            read_stats[prev] = ([ path : 1 ])
            else
            read_stats[prev][path] += 1



class Valid_read(MudObject):
