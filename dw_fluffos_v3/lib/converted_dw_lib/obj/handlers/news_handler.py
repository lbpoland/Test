# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/news_handler.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def has_unread_announcements(self, player: str) -> int:
            mapping news_rc
            mixed subjects
            news_rc = BOARD_HAND.query_newsrc( player )
            if ( !news_rc ) {
            news_rc = ([ ])


    def show_message(self, person: Any) -> None:
            object player
            if ( stringp( person ) ) {
            player = find_player( person )


    def login_event(self, person: Any, type: str) -> None:
            if ( type == LOGIN || type == RECONNECT ) {
            if ( objectp( person ) ) {
            person = person.query_name()


    def broadcast_announcement(self, ) -> None:
            foreach( object user in users() ) {
            if ( interactive( user ) ) {
            show_message( user )



class News_handler(MudObject):
