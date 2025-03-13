# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/living/withdraw.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def withdraw_offer(self, sell_to: MudObject) -> int:
            object *removed
            object ob
            removed = [})
            foreach (ob in sell_to) {
            if (ob.query_respond_command("sell", this_player())) {
            ob.remove_respond_command("sell", this_player())
            removed += [ob]



class Withdraw(MudObject):
