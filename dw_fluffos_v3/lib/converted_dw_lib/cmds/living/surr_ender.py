# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/living/surr_ender.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, mode: int, val: int) -> Any:
            if (!mode) {
            int surr = this_player()->query_surrender()
            if (surr)
            write(sprintf("You will surrender at %d%% of your max hps.\n", surr))
            else
            write("You will not surrender.\n")
            return 1
            } else {
            if (val < 0 || val > 100)
            return notify_fail("Your surrender must be between 0 and 100.\n")
            this_player()->set_surrender(val)
            write(sprintf("Surrender set to %d%%\n", this_player()->query_surrender()))
            return 1



class Surr_ender(MudObject):
