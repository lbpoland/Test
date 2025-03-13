# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/sea_rch.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> int:
            if (this_player()->query_specific_gp("other") < GP_COST) {
            add_failed_mess("You are too weary to complete a "
            "proper search of your surroundings.\n")
            return 0


    def search_callout(self, who: MudObject, str: str) -> None:
            mapping hide_invis
            int i
            string *types
            string* ground
            mixed see
            object *found, ob
            if (who.query_fighting()) {
            write("Oops!  You appear to have entered combat and cannot "
            "finish searching.\n")
            return


    def interrupt_search(self, who: MudObject) -> None:
            if(callouts[who.query_name()]) {
            remove_asyncio.create_task(self.callouts[who.query_name()])
            await who.send("You stop searching.\n")
            map_delete(callouts, who.query_name())



class Sea_rch(MudObject):
