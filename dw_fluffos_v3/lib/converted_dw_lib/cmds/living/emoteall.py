# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/living/emoteall.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> Any:
            if(!TP.query_creator() && !TP.query_property("emoteall")) {
            return notify_fail(NOT_ALLOWED)


    def my_mess(self, fish: str, erk: str) -> None:
            if(!interactive(TP)) return
            printf("%s%-=*s\n", fish, (int)TP.query_cols()-strlen(fish),
            TP.fix_string(erk))



class Emoteall(MudObject):
