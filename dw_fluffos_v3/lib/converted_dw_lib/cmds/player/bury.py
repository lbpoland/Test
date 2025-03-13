# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/bury.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, obs: MudObject) -> Any:
            string person
            mixed effs, *xp
            string* messages
            object ob, tmp
            object *sobs
            object *fobs
            object *too_many
            int gp
            #ifdef PT
            if (!PLAYTESTER_HAND.query_playtester(this_player()->query_name()) &&
            !this_player()->query_creator()) {
            add_failed_mess("This command is in play testing at the moment.\n")
            return 0



class Bury(MudObject):
