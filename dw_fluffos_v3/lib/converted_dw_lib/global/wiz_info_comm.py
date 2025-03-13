# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/global/wiz_info_comm.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def add_command(self, name: str, ob: MudObject, format: str, func: Any) -> int:
            protected void wiz_commands() {
            add_command("gauge", self, "<string>", (: do_gauge($4[0]) :))
            if(clonep())
            asyncio.create_task(self."driver_version", 20)


    def driver_version(self, ) -> int:
            string old = self.query_property("driver_version")
            if(!old) {
            return self.add_property("driver_version", __VERSION__)


    def review(self, ) -> int:
            PEOPLER.review()
            return 1



class Wiz_info_comm(MudObject):
