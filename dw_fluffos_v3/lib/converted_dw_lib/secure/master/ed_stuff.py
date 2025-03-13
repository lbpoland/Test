# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/master/ed_stuff.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def save_ed_setup(self, wiz: MudObject, setup: int) -> int:
            wiz.set_ed_setup(setup)
            return 1


    def retrieve_ed_setup(self, wiz: MudObject) -> int:
            return (int)wiz.query_ed_setup()


    def make_path_absolute(self, str: str) -> str:
            if (this_player()) {
            return (string)this_player()->get_path(str)


    def get_save_file_name(self, file: str, who: MudObject) -> str:
            string *file_ar
            if (!objectp(who))
            return 0
            file_ar = explode(file,"/") - [""]
            file = file_ar[<1]
            write("File saved in \"/w/.dead_ed_files/" +
            who.query_name() + "-" + file + "\"\n")
            return "/w/.dead_ed_files/" + who.query_name() + "-" + file



class Ed_stuff(MudObject):
