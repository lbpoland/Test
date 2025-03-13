# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/living/r_ead.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, things: MudObject) -> Any:
            string gendstr
            string text
            string read
            string reader
            string *others
            string r_short
            object thing
            mapping hide_invis
            int dark
            dark = this_player()->check_dark(environment(this_player())->query_light())
            if (dark < 0) {
            add_failed_mess("It is too dark to read $I.\n", things)
            return 0



class R_ead(MudObject):
