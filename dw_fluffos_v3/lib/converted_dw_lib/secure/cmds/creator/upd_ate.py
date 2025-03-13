# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/cmds/creator/upd_ate.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> Any:
            string tring
            string* filenames
            string err
            object ob
            object* val
            object* obs
            int loop
            notify_fail("No such object.\n")
            tring = str
            if (!str || str == "here") {
            str = file_name(environment(this_player()))
            if (str == "/room/void") {
            notify_fail("The Surgeon General warns you that it is hazardous to "
            "update the void while standing in it.\n")
            return 0



class Upd_ate(MudObject):
