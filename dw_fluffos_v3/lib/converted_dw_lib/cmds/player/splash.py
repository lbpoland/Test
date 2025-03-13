# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/splash.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, obs: MudObject) -> Any:
            object env, ob
            string str
            env = environment(TP)
            if ( !env.query_baths()  &&  (!env.query_water()  ||  !env.query_surface()) ) {
            if ((string)env.query_property("location") == "inside")
            return notify_fail("You must be outside to do that.\n")
            if (!WEATHER.query_raining(env))
            return notify_fail("It must be raining to splash someone.\n")



class Splash(MudObject):
