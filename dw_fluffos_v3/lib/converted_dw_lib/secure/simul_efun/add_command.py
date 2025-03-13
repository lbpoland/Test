# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/simul_efun/add_command.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def add_succeeded_mess(self, mess: Any, indir: MudObject) -> None:
            if (!indir) {
            indir = [})


    def add_succeeded_ob(self, ob: MudObject) -> None:
            this_player()->add_succeeded(ob)


    def add_failed_mess(self, mess: Any, indir: MudObject) -> None:
            if (!indir) {
            indir = [})



class Add_command(MudObject):
