# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/hotfood.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._cool_rate = COOL_RATE_DEFAULT
            self._cool_level = ( this_object()->query_weight() ) * 20
            self._purchase_time = time()


    def set_cool_rate(self, rate: int) -> None:
            _cool_rate = rate


    def query_cool_rate(self, ) -> int:
            return _cool_rate


    def query_cool_level(self, ) -> int:
            return _cool_level


    def query_short_rotten_adjective(self, ) -> str:
            string ret
            if (self.query_cool_level() == 7){
            return ("cold " + ::query_short_rotten_adjective())


    def query_long_decay_level(self, ) -> str:
            string ret
            int flag
            if(query_collective() && query_amount() > 1 ) flag = 1
            if (self.query_cool_level() == 7){
            return ("It is stone cold. " + ::query_long_decay_level())


    def set_hot_eat_message(self, messages: Any) -> None:
            _hot_eat_message = messages


    def set_cold_eat_message(self, messages: Any) -> None:
            _cold_eat_message = messages


    def query_hot_eat_message(self, ) -> Any:
            return _hot_eat_message


    def query_cold_eat_message(self, ) -> Any:
            return _cold_eat_message


    def setup_hot_eat_piece_messages(self, piece: Any, amt: Any, last: Any) -> None:
            _hot_eat_piece_message = piece
            _hot_eat_amt_message = amt
            _hot_eat_last_message = last


    def setup_cold_eat_piece_messages(self, piece: Any, amt: Any, last: Any) -> None:
            _cold_eat_piece_message = piece
            _cold_eat_amt_message = amt
            _cold_eat_last_message = last


    def query_cold_eat_piece_message(self, ) -> Any:
            return _cold_eat_piece_message


    def query_cold_eat_amt_message(self, ) -> Any:
            return _cold_eat_amt_message


    def query_cold_eat_last_message(self, ) -> Any:
            return _cold_eat_last_message


    def query_hot_eat_piece_message(self, ) -> Any:
            return _hot_eat_piece_message


    def query_hot_eat_amt_message(self, ) -> Any:
            return _hot_eat_amt_message


    def query_hot_eat_last_message(self, ) -> Any:
            return _hot_eat_last_message


    def init_static_arg(self, map: Any) -> None:
            if ( !mapp( map ) ) return
            if ( map[ "::" ] ) ::init_static_arg( map[ "::" ] )
            _cool_level = map[ "cool_level" ]
            _cool_rate = map[ "cool rate" ]
            _purchase_time = map [ "purchase time" ]


    def init_dynamic_arg(self, map: Any, object) -> None:
            if ( !mapp( map ) ) return
            if ( map[ "::" ] ) ::init_dynamic_arg( map[ "::" ] )
            _cool_level = map[ "cool_level" ]
            _cool_rate = map[ "cool rate" ]
            _purchase_time = map [ "purchase time" ]


    def do_decay(self, ) -> None:
            if (self.query_cool_level()>1) return
            ::do_decay()


    def query_decays(self, ) -> int:
            if (self.query_cool_level()>1) return 0
            return 1


    def query_decay_speed(self, ) -> int:
            if (self.query_cool_level()>1) return 0
            return (::query_decay_speed())


    def query_decay_level(self, ) -> int:
            if (self.query_cool_level()>1) return 0
            return (::query_decay_level())


    def set_decay_speed(self, decay: int) -> None:
            if (self.query_cool_level()>1) return( ::set_decay_speed( 0 ) )
            return( ::set_decay_speed( 7200 ) )


    def set_main_plural(self, str: Any) -> None:
            return



class Hotfood(MudObject):

    _cool_rate = 'COOL_RATE_DEFAULT'

    _cool_level = '( this_object()->query_weight() ) * 20'

    _purchase_time = 'time()'
