# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/book_shop.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def init(self, ) -> None:
            string storeroom
            ::init()
            storeroom = file_name(query_controller()->query_sell_list())
            add_command("browse", "page of <indirect:object:" + storeroom + ">",
            (: browse_pages($1) :) )
            set_extra_sell_check((: choose_which_page :))


    def browse_pages(self, obs: MudObject) -> int:
            object *real_obs
            object ob
            int number
            string mess
            string read
            object *no_pages
            object *ok
            int i
            if (!check_open(this_player(), "browse")) {
            return 0



class Book_shop(MudObject):
