# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/mobs.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, arg: str) -> int:
            mapping m = ([])
            string *obs, ob, ret = ""
            if(!master()->query_senior(this_player()->query_name()))
            return 0
            switch(arg){
            case "all":
            objects((:$(m)[base_name($1)]++,reset_eval_cost():))
            break
            case "inside":
            objects((:environment($1) && $(m)[base_name($1)]++:))
            break
            default:
            objects((:environment($1) && living($1) &&
            $(m)[base_name($1)]++:))


    def help(self, ) -> str:
            return "Shows partys of NPCs of one kind that are in the same room."



class Mobs(MudObject):
