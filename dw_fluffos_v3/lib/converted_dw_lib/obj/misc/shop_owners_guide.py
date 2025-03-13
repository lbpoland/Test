# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/shop_owners_guide.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("book")
            set_short("brilliant vermillion book")
            add_adjective(({"brilliant", "vermillion"}))
            add_alias("guide")
            set_long("This is a brilliant vermillion coloured book with lots of "
            "pictures of money on the front cover.\n")
            set_read_mess("                   DIY\n\n"
            "          A guide for shop owners.\n")
            set_main_plural("brilliant vermillion books")
            set_weight(10)
            set_value(10)
            set_book_language( "general")
            set_book_dir("/save/books/shop_owner/page")
            set_open_page(0)
            set_ignore_saved_pages(1)


    def do_tear(self, ) -> int:
            return 0


    def query_binding_force(self, ) -> int:
            return 100



class Shop_owners_guide(MudObject):
