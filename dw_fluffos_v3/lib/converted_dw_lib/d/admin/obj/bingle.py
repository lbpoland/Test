# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/admin/obj/bingle.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("domainer")
            set_long(
            "This object shows you all of the creators who are in each domain and those "+
            "that don't have directorys, are not cretors and ones who are not in a "+
            "domain at all.\nThe command to view all this is \"info\".\n")


    def init(self, ) -> None:
            add_action("do_info", "info")


    def do_info(self, str: str) -> int:
            string *creators,
            *domains,
            *mem,
            *cre_not,
            bit
            mapping no_dir, not_creator
            int i, j, cols
            cols = (int)this_player()->query_cols()
            creators = get_dir("/w/")
            domains = get_dir("/d/")
            no_dir = ([ ])
            not_creator = ([ ])
            cre_not = [})
            for (i=0;i<sizeof(creators);i++)
            if (file_size("/w/"+creators[i]) != -2) {
            creators = delete(creators, i, 1)
            i--
            } else if (!"/secure/login"->test_creator(creators[i])) {
            cre_not += [creators[i]]
            creators = delete(creators, i, 1)
            i--



class Bingle(MudObject):
