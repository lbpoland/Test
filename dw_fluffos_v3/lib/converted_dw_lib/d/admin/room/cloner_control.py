# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/admin/room/cloner_control.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_light(100)
            set_short("Cloner Room")
            set_long("This room is used to look at or add filename mappings for the "+
            "cloner object.  It's a very, very, very, very boring room.\n\n"+
            "  add <from> <to> - adds a mapping.\n"+
            "  remove <from> - removes a mapping.\n"+
            "  list [str] - lists mappings which contain the optional string "+
            "str.\n")
            add_exit("southwest" , ROOM+"development" , "door")


    def init(self, ) -> None:
            ::init()
            if (!this_player()) return
            this_player()->add_command("add", self,
            "<string:small'from object'> <string:small'to object'>",
            (: do_add($4[0], $4[1]) :)
            )
            this_player()->add_command("remove", self,
            "<string:small'from object'>",
            (: do_remove($4[0]) :)
            )
            this_player()->add_command("list", self,
            "<string:small'matching'>",
            (: do_list($4[0]) :)
            )
            this_player()->add_command("list", self,
            "",
            (: do_list("") :)
            )


    def do_add(self, from: str, to: str) -> int:
            CLONER.add_mapping(from, to)
            return 1


    def do_remove(self, str: str) -> int:
            CLONER.remove_mapping(str)
            return 1


    def do_list(self, from: str) -> int:
            this_player()->more_string(CLONER.list_mappings(from))
            return 1



class Cloner_control(MudObject):
