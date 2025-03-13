# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/peopler.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.de_names = DE_NAMES
            self.abbrev = ABBREV
            self.var_names = []


    def review(self, ) -> int:
            mixed *bing
            bing = (mixed *)this_player()->query_property("people list")
            if (!bing)
            bing = P_DEFAULT
            write("People : "+review_thingy(bing)+"\n")
            bing = (mixed *)this_player()->query_property("qpeople list")
            if (!bing)
            bing = QP_DEFAULT
            write("Qpeople: "+review_thingy(bing)+"\n")
            bing = (mixed *)this_player()->query_property("netstat list")
            if (!bing)
            bing = N_DEFAULT
            write("Netstat: "+review_thingy(bing)+"\n")
            bing = (mixed *)this_player()->query_property("term list")
            if (!bing)
            bing = T_DEFAULT
            write("Terms  : "+review_thingy(bing)+"\n")
            bing = (mixed *)this_player()->query_property("dir list")
            if (!bing)
            bing = D_DEFAULT
            write("Dirs   : "+review_thingy(bing)+"\n")
            bing = (mixed *)this_player()->query_property("netdup list")
            if (!bing)
            bing = ND_DEFAULT
            write("Netdups: "+review_thingy(bing)+"\n")


    def set_var(self, str: str) -> int:
            string name, type
            mixed *bing
            if (str == "help") {
            write("The non helpful help.\nThis is the list of things that go after "+
            "the %'s in the value.\n")
            list_matches()
            return 1



class Peopler(MudObject):

    de_names = 'DE_NAMES'

    abbrev = 'ABBREV'

    var_names = '[]'
