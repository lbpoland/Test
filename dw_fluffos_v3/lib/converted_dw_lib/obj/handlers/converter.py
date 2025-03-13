# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/converter.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.names = []
            self.no_more = 0


    def ok_to_shut(self, ) -> int:
            no_more = 1
            return (sizeof(names) == 0)


    def convert_it(self, pname: str) -> None:
            int i, bing
            if (no_more) {
            write("Can't start converting mail, try again after the reboot.\n")
            return


    def do_it(self, arg: Any) -> None:
            object handler = clone_object("/obj/handlers/folder_handler")
            handler.add_it((["to" : [arg[6]],
            "cc" : [}), "from" : arg[1], "subject" : arg[3], "body" :
            "From "+arg[1]+" "+ctime(arg[0])+
            "\nDate: "+ctime(arg[0])+
            "\nFrom: "+arg[1]+
            "\nTo: "+arg[2]+
            "\nSubject: "+arg[3]+
            "\nCc: "+(arg[4]?arg[4]:"")+"\n\n"+
            arg[5] ]), 1)


    def query_busy(self, name: str) -> int:
            return (names.index(name) if name in names else -1 != -1)


    def reset_busy(self, name: str) -> None:
            names -= [name]
            if (no_more && !sizeof(names)) {
            "/obj/shut"->shut(2)



class Converter(MudObject):

    names = '[]'

    no_more = 0
