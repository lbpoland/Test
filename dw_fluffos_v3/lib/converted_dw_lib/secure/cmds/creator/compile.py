# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/cmds/creator/compile.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> Any:
            string bit, *bits, error_str
            if (str)
            bits = this_player()->get_files(str)
            if (!str || !sizeof(bits))
            return notify_fail("Syntax: compile <files>\n")
            #ifdef __RUNTIME_LOADING__
            foreach (bit in bits) {
            error_str = catch(generate_source(bit))
            if (!error_str)
            printf("Compiled %s Ok.\n", bit)
            else
            printf("Error compiling %s: %s\n", bit, error_str)



class Compile(MudObject):
