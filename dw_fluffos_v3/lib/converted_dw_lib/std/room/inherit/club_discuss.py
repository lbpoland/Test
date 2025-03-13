# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/inherit/club_discuss.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def init(self, ) -> None:
            add_command("discuss",
            "[open] {description|add position|"
            "change position name|memo|secret|"
            "remove member|no confidence|remove position|"
            "create account|remove account} in <string'club name'>",
            (: do_discuss(1, $4[0], $4[1]) :))
            add_command("discuss",
            "committee {description|add position|"
            "change position name|memo|secret|remove member|"
            "no confidence|remove position|"
            "create account|remove account} in <string'club name'>",
            (: do_discuss(0, $4[0], $4[1]) :))


    def do_discuss(self, open: int, type: str, club_name: str) -> int:
            if (open) {
            open = CLUB_DISCUSS_OPEN



class Club_discuss(MudObject):
