# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/start_positions.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def load_file(self, ) -> None:
            if ( file_size( SAVE_FILE + ".o" ) > 0 ||
            file_size( SAVE_FILE + ".o.gz" ) > 0 )
            {
            unguarded( (: restore_object, SAVE_FILE :) )


    def save_file(self, ) -> None:
            unguarded( (: save_object, SAVE_FILE :) )


    def __init__(self):
            self._last_added = 0
            self._buggy_starts = []
            self._buggy_starts = []


    def add_buggy_start(self, fname: str) -> int:
            if ( !fname ) {
            return 0


    def delete_buggy_start(self, fname: str) -> int:
            if ( !fname ) {
            return 0


    def remove_buggy_starts(self, player: MudObject) -> None:
            string * starts
            if ( !player ) {
            return


    def login_callback(self, player: str, type: str) -> None:
            object playerob
            if ( !player ||
            !type ||
            type != LOGIN )
            {
            return


    def dest_me(self, ) -> None:
            destruct( self )



class Start_positions(MudObject):

    _last_added = 0

    _buggy_starts = '[]'
