# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/master/dest_env.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def destruct_environment_of(self, ob: MudObject) -> None:
            object env
            env = environment(ob)
            if (env) {
            string *a
            a = (string *)env.query_dest_dir()
            if (catch(ob.move_player(a[0], a[1], "stumbles"))) {
            ob.move_player("void", "/room/void", "is sucked into the")



class Dest_env(MudObject):
