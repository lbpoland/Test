# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/leaflet.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.pages = ['({ })']


    def init(self, ) -> None:
            add_command( "turn", "[a] page of <direct:object>" )
            add_command( "open", "<direct:object> to [page] <number>",
            (: do_open($4[1]) :))


    def set_no_pages(self, number: int) -> None:
            int i
            if ( number < 1 ) {
            number = 1


    def add_read_mess(self, mess: Any, type: str, lang: str, size: int) -> Any:
            mixed ret
            ret = ::add_read_mess( mess, type, lang, size )
            pages[ page ] = query_read_mess()
            return ret


    def set_open_page(self, number: int) -> None:
            if ( ( number < 1 ) || ( number > sizeof( pages ) ) ) {
            number = 1


    def do_turn(self, ) -> int:
            set_open_page( page + 2 )
            return 1


    def do_open(self, page_no: int) -> int:
            if ( ( page_no < 1 ) || ( page_no > sizeof( pages ) ) ) {
            add_failed_mess("The page no " + page_no + " does not exist.\n")
            return 0


    def init_dynamic_arg(self, map: Any) -> None:
            if ( !mapp( map ) ) {
            return


    def query_read_short(self, player: MudObject, ignore_labels: int) -> str:
            string ret
            if (page == 0) {
            ret = ::query_read_short(player, 1)
            } else {
            ret = ::query_read_short(player, 0)



class Leaflet(MudObject):

    pages = "['({ })']"
