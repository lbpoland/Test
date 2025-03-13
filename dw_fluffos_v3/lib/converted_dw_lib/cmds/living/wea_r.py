# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/living/wea_r.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from .utilities import CLOTHING_HANDLER
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, things: MudObject) -> int:
            int i
            string result
            string stuff
            string *reasons
            object *okay
            object *blocking
            object *total_blocking
            object ob
            object tmp
            mapping failed
            mapping hide_invis
            int hiding, sneaking, difficulty, light, my_light
            okay = [})
            failed = ([ ])
            things = sort_array(things, (: CLOTHING_HANDLER.query_clothing_depth($2->query_type()) -
            CLOTHING_HANDLER.query_clothing_depth($1->query_type()) :) )
            total_blocking = [})
            foreach (ob in things) {
            if (environment(ob) != this_player())  {
            failed = add_to_failed(failed, "not carrying", ob)
            continue



class Wea_r(MudObject):
