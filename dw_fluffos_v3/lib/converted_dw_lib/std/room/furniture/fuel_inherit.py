# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/furniture/fuel_inherit.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._amount = 100


    def __init__(self):
            self._amount = 100
            set_short( (: fuel_short :) )
            set_long( (: fuel_long :) )
            add_property("no recycling", 1)
            add_property("fuel", 1)


    def fuel_short(self, ) -> str:
            int i
            int x
            x = sizeof(_shorts)
            for(i = 1; i <= x; i++){
            if( (_amount + 1) > 100 - ( i * 100 / x ) ){
            return _shorts[(i-1)]


    def fuel_long(self, ) -> str:
            int i
            int x
            x = sizeof(_longs)
            for(i = 1; i <= x; i++){
            if( ( _amount + 1 ) > ( 100 - ( i * 100 / x )) ){
            return _longs[(i-1)]


    def query_dynamic_auto_load(self, ) -> Any:
            return ([ "::" : ::query_dynamic_auto_load(),
            "amount" : _amount
            ])


    def init_dynamic_arg(self, arg: Any) -> None:
            _amount = arg[ "amount" ]
            ::init_dynamic_arg(arg["::"])



class Fuel_inherit(MudObject):

    _amount = 100
