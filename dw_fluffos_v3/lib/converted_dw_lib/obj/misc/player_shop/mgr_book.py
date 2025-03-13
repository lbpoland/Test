# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/player_shop/mgr_book.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "book" )
            add_alias( "handbook" )
            set_short( "manager handbook")
            set_main_plural( "manager handbooks" )
            add_adjective( "manager" )
            set_weight( 5 )
            set_value( 5 )
            set_no_pages( 11 )
            add_property( "no recycling", 1 )


    def set_office(self, office: str) -> None:
            _office = office
            if ( !query_property( "office" ) ) {
            add_property( "office", office )


    def init(self, ) -> None:
            set_open_page( 0 )
            if ( !_office || _office == "" ) {
            if ( !query_property( "office" ) ) {
            return



class Mgr_book(MudObject):
