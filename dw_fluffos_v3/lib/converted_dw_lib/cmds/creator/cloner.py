# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/cloner.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def do_list(self, file: str) -> int:
            string *files, change
            mapping changes
            string ret
            if(file && file != "") {
            files = this_player()->get_files(file)


    def do_move(self, source: str, dest: str) -> int:
            string *sources, *tmp, destp, rcs
            seteuid(geteuid(this_player()))
            sources = this_player()->get_files(source)
            if(!sizeof(sources))
            return notify_fail("No source files found.\n")
            destp = this_player()->get_path(dest)
            if(file_size(destp) != -2 && !mkdir(dest))
            return notify_fail("Destination must be a directory.\n")
            foreach(source in sources) {
            if(file_size(source) == -2 || file_size(source) == -1) {
            if(source[<4..] == "/RCS") {
            if(rename(source, source+".tmp"))
            return notify_fail("Error moving RCS directory to temp location.\n")
            else
            rcs = source+".tmp"
            } else
            write("Not moving directory: " + source + "\n")
            } else {
            tmp = explode(source, "/")
            dest = destp + "/" + tmp[sizeof(tmp)-1]
            if(rename(source, dest))
            return notify_fail("Error renaming [" + source + "] to [" + dest +
            "]\n")
            CLONER.add_mapping(source, dest)


    def do_add(self, source: str, dest: str) -> int:
            CLONER.add_mapping(source, dest)
            return 1


    def do_remove(self, source: str) -> int:
            CLONER.remove_mapping(source)
            return 1



class Cloner(MudObject):
