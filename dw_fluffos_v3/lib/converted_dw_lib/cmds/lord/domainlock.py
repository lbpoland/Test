# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/lord/domainlock.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def domain_check(self, ) -> int:
            mapping map = APPLICATIONS_HANDLER.query_domain_status()
            string ret = ""
            foreach (string s, int o in map) {
            ret += capitalize (s) + " is " + (o ? "open" : "closed") + " to "
            "applications and is managed by " +
            capitalize (APPLICATIONS_HANDLER->query_responsibility (s)) + ".\n"


    def cmd(self, domain: str, status: int) -> int:
            int i = APPLICATIONS_HANDLER.query_domain_status()[domain]
            if (i == -1) {
            this_player()->add_failed_mess (self, "You do not have "
            "permission to close the " + domain + " domain.\n")
            return 0



class Domainlock(MudObject):
