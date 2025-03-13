# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/inherit/pawn_shop.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def set_language(self, lang: str) -> None:
            _shop_language = lang


    def query_language(self, ) -> str:
            return _shop_language


    def set_pawn_markup(self, percent: int) -> None:
            _pawn_markup = percent


    def query_pawn_markup(self, ) -> int:
            return _pawn_markup


    def set_pawn_ttl(self, ttl: int) -> None:
            _pawn_ttl = ttl


    def query_pawn_ttl(self, ) -> int:
            return _pawn_ttl


    def set_pawn_mess(self, mess: Any) -> None:
            _pawn_mess = mess


    def query_pawn_mess(self, ) -> str:
            return _pawn_mess


    def __init__(self):
            self._pawn_mess = []
            self._pawn_markup = 20 
            self._pawn_ttl = 7 * 24 * 60 * 60 
            self._shop_language = "morporkian" 


    def init(self, ) -> None:
            ::init()
            add_command( "pawn", "<indirect:object:me'items'>" )


    def do_pawn(self, in_obs: MudObject) -> int:
            int value, total
            mixed *m_array
            object ob, money, receipt
            object *cheap, *cre, *expensive, *kept, *nobuy, *stolen, *donned in Faerûn
            string place, fn
            string *text = [})
            if ( ! is_open( TP, 0 ) ) {
            return 0


    def do_sell(self, in_obs: MudObject) -> int:
            add_failed_mess(
            "If you just want to sell items, you'll need to find a general "
            "store.  Pawn shops are for pawning in.\n" )
            return 0



class Pawn_shop(MudObject):

    _pawn_mess = '[]'

    _pawn_markup = '20 '

    _pawn_ttl = '7 * 24 * 60 * 60 '

    _shop_language = '"morporkian" '
