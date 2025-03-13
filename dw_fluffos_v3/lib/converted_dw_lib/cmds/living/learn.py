# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/living/learn.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str, obs: MudObject) -> Any:
            object *diff_lvl
            object *no_xp
            object *not_offer
            object *ok
            object *moved
            object ob
            int time
            string skill
            string cmd
            string cmd_ob
            string *bits
            string levelstr
            class teaching_skill womble
            if (TP.query_property("dead")) {
            notify_fail("Your dead.  Your mind slips off the task and goes for "
            "a wander down memory lane.\n")
            return 0



class Learn(MudObject):
