# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/crea_tor.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> Any:
            object *ov, ob
            notify_fail("Creator of what?\n")
            ov = WIZ_PRESENT.wiz_present(str,this_player())
            if (!sizeof(ov)) return 0
            foreach (ob in ov) {
            write("Creator of " + WIZ_PRESENT.desc_object(ob) + ": " +
            master()->creator_file (file_name(ob)) + ", uid: " +
            getuid(ob) + ", euid: "+geteuid(ob)+"\n")


    def dest_me(self, ) -> None:
            destruct(self)


    def clean_up(self, ) -> None:
            dest_me()


    def reset(self, ) -> None:
            dest_me()



class Crea_tor(MudObject):
