# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/furniture/document_handler.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def query_save_dir(self, ) -> str:
            return commercial::query_save_dir() + "/" + query_commercial_id()


    def load_me(self, ) -> None:
            if (!query_commercial_id()) {
            setup_new_commercial_id()


    def save_me(self, ) -> None:
            environment()->event_save(self)


    def init(self, ) -> None:
            add_command("list", "documents [from] <direct:object>", (: do_list() :))
            add_command("view", "document <string'id'> [from] <direct:object>",
            (: do_display($4[0]) :))
            add_command("add", "documents {html|plain} called <string:quoted'title'> to <direct:object>",
            (: do_add_document($4[1], ($4[0] == "html"?DOCUMENT_HTML:DOCUMENT_PLAIN)) :))
            add_command("delete", "document <string'id'> [from] <direct:object>",
            (: do_delete_document($4[0]) :))


    def init_dynamic_arg(self, map: Any) -> None:
            document_handler::init_dynamic_arg(map)
            commercial::init_dynamic_arg(map)



class Document_handler(MudObject):
