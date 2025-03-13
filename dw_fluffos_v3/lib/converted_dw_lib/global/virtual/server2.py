# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/global/virtual/server2.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.methods = ([ ])


    def add_method(self, suffix: str, ob: MudObject, fun: str, type: int) -> None:
            if (!type)
            type = CLONE
            if (!methods[suffix]) {
            methods[suffix] = [ob, fun, type]


    def create_virtual_object(self, name: str, clone: int) -> MudObject:
            string *split
            mixed  *method
            object ob
            split = explode(name, ".")
            method = methods[split[sizeof(split) - 1]]
            if (method) {
            if (clone ||
            (method[TYPE]&LOAD)) {
            ob =  (object) call_other(method[OB], method[FUN], name, clone)
            ob.add_property("virtual name", name)
            return ob



class Server2(MudObject):

    methods = '([ ])'
