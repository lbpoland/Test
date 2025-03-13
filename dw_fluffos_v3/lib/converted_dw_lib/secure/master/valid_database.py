# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/master/valid_database.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def valid_database(self, ob: MudObject, action: str, info: Any) -> Any:
            string obname = base_name(ob)
            switch (obname){
            case "/obj/handlers/clusters":
            case "/obj/handlers/map":
            case "/cmds/creator/osql":
            case "/cmds/errors_base":
            return -1
            default:
            return 0



class Valid_database(MudObject):
