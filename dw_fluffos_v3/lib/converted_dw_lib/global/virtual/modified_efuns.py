# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/global/virtual/modified_efuns.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def tell_object(self, ob: MudObject, str: str) -> None:
            if (objectp(ob))
            ob.event_write(previous_object(), str)


    def find_living(self, str: str) -> MudObject:
            string nick
            object ob
            if (this_player() && (nick = (string)this_player()->expand_nickname(str)))
            str = nick
            if ((ob = efun::find_living(str)))
            if ((int)ob.query_invis() == 2) {
            if (member_array(this_player()->query_name(),
            (object *)ob.query_allowed()) == -1)
            return 0


    def find_player(self, str: str) -> MudObject:
            object ob
            if ((ob = efun::find_player(str)))
            if ((int)ob.query_invis() == 2)
            if (member_array(this_player()->query_name(),
            (object *)ob.query_allowed()) == -1)
            return 0
            return ob


    def log_file(self, name: str, mess: str) -> None:
            if (file_size("/log/"+name) > MAX_SIZE) {
            seteuid("Root")
            rm("/log/"+name+".old")
            rename("/log/"+name, "/log/"+name+".old")


    def mud_name(self, ) -> str:
            return capitalize(MUD_NAME)


    def cat(self, file: str, start_line: int, number: int) -> None:
            string bing
            seteuid(geteuid(previous_object()))
            bing = read_file(file, start_line, number)
            seteuid(0)
            if (bing)
            printf("%s", bing[0..5000])


    def clone_object(self, name: str) -> MudObject:
            seteuid(geteuid(previous_object()))
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



class Modified_efuns(MudObject):
