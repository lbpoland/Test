# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/hi_story.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, arg: str) -> int:
            return this_player()->print_history(arg)


    def query_patterns(self, ) -> Any:
            return ["", (: cmd("") :),
            "<string'number|number,number'>", (: cmd($4[0]) :)]



class Hi_story(MudObject):
