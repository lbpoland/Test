# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/menu.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def set_pub(self, pub: MudObject) -> None:
            our_pub = pub
            add_read_mess(our_pub.read(), "printed letters", our_pub.query_language())


    def init(self, ) -> None:
            this_player()->add_command( "list", self, "" )


    def query_readable_message(self, player: MudObject) -> str:
            string lang
            string mess
            mess = our_pub.read()
            lang = our_pub.query_language()
            mess = LANGUAGES.garble_text(lang, mess, self, player)
            return mess


    def do_list(self, ) -> int:
            write(query_readable_message(this_player()))
            add_succeeded_mess(["", "$N read$s $D.\n"])
            return 1



class Menu(MudObject):
