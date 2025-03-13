# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/locate.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, word: str) -> Any:
            int i
            int base_num
            string list
            object thing
            object *things
            object *extra_things
            debug_printf("%s", word)
            if (environment(TP)) {
            switch(TP.check_dark(environment(TP)->query_light())) {
            case -2:
            case -1:
            if (this_player()->query_creator()) {
            write("It is too dark to locate anything, but since you are a cre...\n")
            } else {
            return notify_fail("It's too dark to locate anything.\n")



class Locate(MudObject):
