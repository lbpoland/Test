# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/global/virtual/efuns.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def clone_object(self, name: str) -> MudObject:
            if(name[0..2] == "/d/" || name[0..1] == "d/")
            return (object)HANDLER.clone_virtual_object(name)
            return efun::clone_object(name)


    def destruct(self, name: Any) -> None:
            object obj
            if(stringp(name)) {
            obj = find_object(name)
            if(obj.query_property("file_name"))
            HANDLER.destruct_virtual_object(obj)
            destruct(obj)
            } else if(objectp(name)) {
            if(name.query_property("file_name"))
            HANDLER.destruct_virtual_object(name)
            destruct(name)


    def file_name(self, obj: MudObject) -> str:
            string name, number, file
            name = efun::file_name(obj)
            if(sscanf(name, "%s#%s", name, number) == 2) {
            if(file = (string)obj.query_property("file_name")) {
            return file + "#" + number
            } else {
            return name + "#" + number


    def find_object(self, str: str) -> MudObject:
            object obj
            if(obj = efun::find_object(str))
            return obj
            return (object)HANDLER.find_virtual_object(str)



class Efuns(MudObject):
