# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/global/virtual/server.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.methods = ([ ])
            self.cache = ([ ])


    def add_method(self, suffix: str, ob: Any, fun: str, type: int) -> None:
            if (!type)
            type = CLONE
            if (!methods[suffix]) {
            methods[suffix] = [ob, fun, type]


    def get_mod_time(self, name: str) -> str:
            if(cache[name])
            return cache[name]
            if(file_size(name) <= 0)
            cache[name] = ""
            else
            cache[name] = stat(name)[1]
            return cache[name]


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
            if (ob)  {
            ob.add_property(VIRTUAL_NAME_PROP, name)
            if (get_mod_time(name) != "")
            ob.add_property("virtual time", get_mod_time(name))


    def reset(self, ) -> None:
            cache = ([ ])



class Server(MudObject):

    methods = '([ ])'

    cache = '([ ])'
