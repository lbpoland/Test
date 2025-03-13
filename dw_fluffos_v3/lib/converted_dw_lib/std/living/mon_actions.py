# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/living/mon_actions.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.mon_actions = []


    def do_shadow(self, ) -> None:
            int i
            object ob
            string fname
            self.shadow_death()
            fname = (string)MONSTER_HAND.query_shadow_name()
            rm(fname+".c")
            for (i=0;i<sizeof(mon_actions);i+=2)
            write_file(fname+".c",
            "inherit \"/std/trigger/"+mon_actions[i]+"\";\n")
            write_file(fname+".c", read_file("/std/living/mon-shadow.c"))
            ob = clone_object(fname)
            ob.setup_shadow(self)
            rm(fname+".c")


    def remove_trigger(self, name: str) -> int:
            int i
            if ((i=mon_actions.index(name) if name in mon_actions else -1) == -1)
            return 0
            mon_actions = delete(mon_actions, i, 2)
            if (!sizeof(mon_actions))
            self.shadow_death()
            else
            do_shadow()
            return 1


    def remove_triggered_action(self, trigger: str, name: str) -> int:
            int i, j
            if ((i=mon_actions.index(trigger) if trigger in mon_actions else -1) == -1)
            return 0
            if ((j=mon_actions[i+1].index(name) if name in mon_actions[i+1] else -1) == -1)
            return 0
            mon_actions[i+1] = delete(mon_actions[i+1], i, 2)
            if (!sizeof(mon_actions[i+1]))
            remove_trigger(trigger)
            return 1



class Mon_actions(MudObject):

    mon_actions = '[]'
