# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/scroll.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.num_pages = 1
            self.open_page = 1
            self.pages = ['({ 0', '0', '0 })']


    def init(self, ) -> None:
            add_command("scroll", "<word'forward|backward'>", (:self.do_scroll($4[0]):))


    def set_read_mess(self, mess: str, lang: str, size: int) -> None:
            pages[ open_page ] = [mess, lang, size]
            ::set_read_mess( mess, lang, size )


    def add_read_mess(self, mess: str, type: str, lang: str, size: str) -> None:
            pages[ open_page ] = [mess, lang, size]
            ::set_read_mess( mess, lang, size )


    def set_open_page(self, number: int) -> None:
            int size
            string mess, lang
            mixed *text
            if ( ( number < 0 ) || ( number > num_pages ) )
            open_page = 1
            else
            open_page = number
            text = pages[ open_page ]
            if ( !text || ( sizeof( text ) < 3 ) )
            text = [0, 0, 0]
            mess = text[ 0 ]
            lang = text[ 1 ]
            size = text[ 2 ]
            ::set_read_mess( mess, lang, size )


    def do_scroll(self, word: str) -> int:
            if ( ( word != "forward" ) && ( word != "backward" ) ) {
            notify_fail( "Syntax: scroll forward|backward\n" )
            return 0


    def query_static_auto_load(self, ) -> Any:
            if ( ( file_name( self ) )[ 0 .. 10 ] != "/std/scroll" )
            return 0
            return int_query_static_auto_load()


    def init_dynamic_arg(self, args: Any) -> None:
            ::init_dynamic_arg( args[ "::" ] )
            open_page = args[ "open_page" ]


    def init_static_arg(self, args: Any) -> None:
            if ( args[ "::" ] ) ::init_static_arg( args[ "::" ] )
            if ( args[ "num_pages" ] ) num_pages = args[ "num_pages" ]
            if ( args[ "pages" ] ) pages = args[ "pages" ]



class Scroll(MudObject):

    num_pages = 1

    open_page = 1

    pages = "['({ 0', '0', '0 })']"
