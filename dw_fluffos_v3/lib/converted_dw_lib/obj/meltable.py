# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/meltable.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._melt_rate = MELT_RATE_DEFAULT
            self._melt_counter = 0


    def set_melt_result(self, result: str) -> None:
            _melt_result = result


    def query_melt_result(self, ) -> str:
            return _melt_result


    def set_melt_rate(self, rate: int) -> None:
            _melt_rate = rate


    def query_melt_rate(self, ) -> int:
            return _melt_rate


    def query_melt_level(self, ) -> int:
            return _melt_level


    def query_short_rotten_adjective(self, ) -> str:
            string ret
            int bing
            bing = 100 - ( ( 100 * _melt_level ) / _original_melt_level )
            ret = ""
            switch ( bing ) {
            case 0..1:
            break
            case 2..20:
            ret = "slightly melted " + ret
            break
            case 21..45:
            ret = "partially melted " + ret
            break
            case 46..55:
            ret = "half melted " + ret
            break
            case 56..80:
            ret = "mostly melted " + ret
            break
            case 81..100:
            ret = "almost completely melted " + ret
            break


    def query_long_decay_level(self, ) -> str:
            string ret
            int bing
            bing = 100 - ( ( 100 * _melt_level ) / _original_melt_level )
            ret = ""
            switch ( bing ) {
            case 0..1:
            if( query_collective() && query_amount() > 1 )
            ret += "They have not yet begun to melt.\n"
            else
            ret += "It has not yet begun to melt.\n"
            break
            case 2..20:
            if( query_collective() && query_amount() > 1 )
            ret += "They have melted slightly.\n"
            else
            ret += "It has melted slightly.\n"
            break
            case 21..45:
            if( query_collective() && query_amount() > 1 )
            ret += "They have partially melted away.\n"
            else
            ret += "It has partially melted away.\n"
            break
            case 46..55:
            if( query_collective() && query_amount() > 1 )
            ret += "They are half melted away.\n"
            else
            ret += "It is half melted away.\n"
            break
            case 56..80:
            if( query_collective() && query_amount() > 1 )
            ret += "They have mostly melted away.\n"
            else
            ret += "It has mostly melted away.\n"
            break
            case 81..100:
            if( query_collective() && query_amount() > 1 )
            ret += "They have almost complete melted away.\n"
            else
            ret += "It has almost completely melted away.\n"
            break


    def do_apply(self, : MudObject) -> int:
            int i
            if( i = ::do_apply( things ) ) {
            things[ 0 ]->add_property( "warmth", CHILL, CHILL_TIME )


    def do_rub(self, : MudObject) -> int:
            int i
            if( i = ::do_rub( things ) ) {
            things[ 0 ]->add_property( "warmth", CHILL, CHILL_TIME )


    def init_static_arg(self, map: Any) -> None:
            {
            if ( !mapp( map ) ) {
            return


    def init_dynamic_arg(self, map: Any, object) -> None:
            {
            if ( !mapp( map ) ) {
            return


    def query_liquid(self, ) -> int:
            return 0


    def set_liquid(self, ) -> None:


    def do_decay(self, ) -> None:
            return


    def query_decays(self, ) -> int:
            return 0


    def query_decay_speed(self, ) -> int:
            return 0


    def query_decay_level(self, ) -> int:
            return 0


    def set_decay_speed(self, decay: int) -> None:
            return( ::set_decay_speed( 1 ) )


    def do_cure(self, ) -> int:
            return 0


    def query_cured(self, ) -> int:
            return 0


    def do_dry(self, ) -> int:
            return 0


    def query_dried(self, ) -> int:
            return 0


    def query_rotten(self, ) -> int:
            return 0


    def set_splashable(self, ) -> None:
            return



class Meltable(MudObject):

    _melt_rate = 'MELT_RATE_DEFAULT'

    _melt_counter = 0
