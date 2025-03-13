# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/family.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def family_reverse(self, from: str, to: str) -> Any:
            string family_from
            string family_to
            string *relations_to
            string *relations_from
            string opp
            string relation
            family_from = PLAYER_HANDLER.test_family(from)
            family_to = PLAYER_HANDLER.test_family(to)
            if (!family_from) {
            add_failed_mess("Sorry, " + from + " is not in a family.\n")


    def family_remove(self, from: str, to: str) -> int:
            string family_from
            string family_to
            string *relations_to
            string *relations_from
            string relation
            family_from = PLAYER_HANDLER.test_family(from)
            family_to = PLAYER_HANDLER.test_family(to)
            if (!family_from) {
            add_failed_mess("Sorry, " + from + " is not in a family.\n")



class Family(MudObject):
