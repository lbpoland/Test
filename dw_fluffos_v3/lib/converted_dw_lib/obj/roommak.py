# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/roommak.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("maker")
            add_adjective("room")
            set_short("Room maker")
            set_long("It is a small wooden rod about 30 centimeters long with deep "+
            "burn marks along the sides.  It has what looks like a small "+
            "lens stuck in the end and three buttons along its length.\n")


    def init(self, ) -> None:
            if (this_player()->query_creator()) {
            add_action("do_new", "new")
            add_action("do_set", "set")
            add_action("do_add", "add")
            add_action("do_setup", "setup")
            add_action("do_modify", "modify")
            add_action("do_map", "map")


    def do_new(self, str: str) -> int:
            if (!str) {
            notify_fail("Syntax: new <name>\n")
            return 0



class Roommak(MudObject):
