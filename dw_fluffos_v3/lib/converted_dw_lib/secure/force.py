# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/force.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def force_commands(self, ) -> None:
            sscanf(file_name(self), "%s#", fname)
            if(!self.query_property("npc") &&
            self.query_property("force") || fname == "/global/lord")
            add_action("do_force", "force")
            if(fname == "/global/lord")
            add_action("no_force", "noforce")


    def do_force(self, str: str) -> int:
            string who, what
            object *obs, ob
            int i
            class obj_match omatch
            if(fname == "/global/player" && !this_player()->query_property("force")) {
            notify_fail("You do not have the ability to do that yet.\n")
            return 0


    def do_force_on_me(self, str: str) -> int:
            string temp1, temp2
            object forcer
            forcer = this_player(1)
            if(!forcer) {
            forcer = previous_object()



class Force(MudObject):
