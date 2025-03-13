# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/when.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, who: str) -> int:
            object player
            int last
            int caller
            string* bits
            string womble
            int bing
            bits = explode(who, ",")
            if (sizeof(bits) > 1) {
            bing = 0
            foreach (womble in bits) {
            if (cmd(womble)) {
            bing = 1



class When(MudObject):
