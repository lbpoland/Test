# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/guildl_ist.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, arg: str) -> int:
            object ob
            mapping classs
            string class, *fields
            classs = ([ ])
            foreach(ob in users()) {
            if(ob.query_creator())
            continue
            if(!ob.query_class_ob()) {
            classs["none"]++
            } else {
            fields = explode((string)ob.query_class_ob(), "/")
            classs[fields[2]]++



class Guildl_ist(MudObject):
