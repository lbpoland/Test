# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/bank_franchise.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._total_account = 0
            self._total_made = 0


    def query_float(self, ) -> int:
            return 2400000


    def adjust_float(self, amt: int) -> None:


    def query_franchise(self, ) -> str:
            return file_name(self)


    def is_open_for(self, type: str, person: str) -> int:
            return 1


    def set_save_file(self, word: str) -> None:
            _save_file = word
            if ( file_size( _save_file +".o" ) > 0 ) {
            unguarded((: restore_object, _save_file :))


    def event_save(self, ob: MudObject) -> None:
            if ( !_save_file ) {
            return


    def make_bank_robbers(self, ) -> int:
            int i, amount, loss, number, percent_loss, total
            string player_name
            object *bags, *money, *players, *robbers
            mixed *mon_array
            percent_loss = 2 + random( 4 )
            players = users()
            for ( i = 0; i < sizeof( players ); i++ ) {
            player_name = (string)players[ i ]->query_name()
            if ( ( amount = BANK_HANDLER.query_account( player_name, query_bank_name() ) ) ) {
            switch( amount ) {
            case 1 .. 10:
            loss = 0
            break
            case 11 .. 100:
            loss = ( amount * percent_loss ) / 100
            break
            case 101 .. 1000:
            loss = ( amount * percent_loss * 2 ) / 100
            break
            case 1001 .. 10000:
            loss = ( amount * percent_loss * 3 ) / 100
            break
            case 10001 .. 100000:
            loss = ( amount * percent_loss * 4 ) / 100
            break
            default:
            loss = ( amount * percent_loss * 5 ) / 100


    def init(self, ) -> None:
            basic_room::init()
            bank_franchise::init()



class Bank_franchise(MudObject):

    _total_account = 0

    _total_made = 0
