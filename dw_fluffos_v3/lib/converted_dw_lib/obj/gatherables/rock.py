# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/gatherables/rock.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("rock")
            set_short("hidden rock")
            set_long("There are rocks of all shapes and sizes here.  Use "
            "\"gather\" to collect specific types.\n")
            set_get_failure_mess("There are all sorts of rocks and minerals "
            "around here.  Use \"gather\" to get "
            "specific varieties.\n")



class Rock(MudObject):
