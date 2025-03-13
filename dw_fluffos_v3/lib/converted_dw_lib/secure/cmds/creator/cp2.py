# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/cmds/creator/cp2.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> Any:
            string *filenames, dest, *fnames
            int loop, fs
            int show_ok
            string src
            if(!str)
            return notify_fail("Usage : cp file [file|dir...]\n")
            show_ok = 0
            fnames = explode(str, " ")
            filenames = this_player()->get_files(implode(fnames[0..sizeof(fnames) -2],
            "/"))
            filenames = filter(filenames, (:$1[<1] != '.':))
            if(!sizeof(filenames)) {
            notify_fail("Usage : cp file [file|dir...]\n")
            return 0



class Cp2(MudObject):
