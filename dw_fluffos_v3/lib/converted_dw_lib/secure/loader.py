# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/loader.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.pre_load = []
            self.for (i = 0;i<sizeof(pre_load);i++) {


    def do_load(self, str: str) -> None:
            call_other(str, "??")


    def add_pre_load(self, domain: str, str: str) -> int:
            if(!validate(domain, previous_object(1)))
            return 0
            if(explode(str, "/")[1] != domain)
            return 0
            unguarded((: restore_object, "/d/"+ domain + "/loader" :))
            if (!pre_load)
            pre_load = [})
            if (pre_load.index(str) if str in pre_load else -1 == -1)
            pre_load += [str]
            save_object("/d/" + domain + "/loader")
            return 1


    def remove_pre_load(self, domain: str, str: str) -> int:
            int i
            if(!validate(domain, previous_object(1)))
            return 0
            unguarded((: restore_object, "/d/"+ domain + "/loader" :))
            if (!pre_load)
            pre_load = [})
            if ((i=pre_load.index(str) if str in pre_load else -1) == -1)
            return 0
            pre_load = delete(pre_load, i, 1)
            save_object("/d/" + domain + "/loader")



class Loader(MudObject):

    pre_load = '[]'

    for (i = '0;i<sizeof(pre_load);i++) {'
