# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/global/start_position.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.starts = []


    def __init__(self):
            self.starts = []
            int *query_saved_co_ords() { return saved_co_ords; }
            protected void set_last_pos(string pos) {
            if(pos[0..4] != "/room")
            last_pos = pos


    def query_last_pos(self, ) -> str:
            return last_pos


    def query_start_pos(self, ) -> str:
            string start_pos
            if ( !sizeof( starts ) ) {
            start_pos = query_nationality_start_location()
            } else {
            start_pos = starts[ 0 ]


    def add_start(self, start_file: str, start_desc: str) -> None:
            if ( !starts ) {
            starts = [})


    def remove_start(self, start_file: str) -> None:
            int i
            if ( !starts ) {
            return


    def set_start_location(self, start_file: str) -> None:
            int i
            if ( !starts) {
            return


    def inform_reconnect_game(self, ) -> None:
            user_event( "inform",
            query_extra_login_stuff(query_cap_name() +
            " reconnects"), "link-death", self )


    def check_last_pos(self, ) -> None:
            last_pos = find_start_pos(self, environment())
            saved_co_ords = find_start_coord(self, environment())



class Start_position(MudObject):

    starts = '[]'
