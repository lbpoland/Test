# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/path_of.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> Any:
            object *ov, ob
            if(strsrch(str, "in everyone") != -1)
            return notify_fail("Please don't do that.  You've been asked not to "
            "and it causes lag.\n")
            notify_fail("Pathof what?\n")
            ov = WIZ_PRESENT.wiz_present(str, this_player())
            if (!sizeof(ov)) return 0
            foreach (ob in ov) {
            if (!objectp(ob)) continue
            write("Path of " + WIZ_PRESENT.desc_object(ob) + " in " +
            WIZ_PRESENT.desc_object(environment(ob)) + ":\n")
            write(file_name(ob)+ "\n")


    def dest_me(self, ) -> None:
            destruct(self)


    def clean_up(self, ) -> None:
            dest_me()


    def reset(self, ) -> None:
            dest_me()



class Path_of(MudObject):
