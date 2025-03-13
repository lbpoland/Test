# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/outside.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def set_weather_handler(self, handler: str) -> None:
            _weather_handler = handler


    def query_weather_handler(self, ) -> str:
            return _weather_handler


    def set_climate(self, climate: str) -> int:
            if(CLIMATES.index(climate) if climate in CLIMATES else -1 == -1)
            return 0
            _climate = climate
            return 1


    def query_climate(self, ) -> str:
            if(!_climate)
            return DEFAULT_CLIMATE
            return _climate


    def set_light_change(self, s: str) -> None:
            add_property("light change", s)


    def query_light_change(self, ) -> str:
            return query_property("light change")


    def snow_look(self, ) -> str:
            return _weather_handler.snow_string(self) + "."


    def rain_look(self, ) -> str:
            return _weather_handler.rain_string(self) + "."


    def sleet_look(self, ) -> str:
            return _weather_handler.sleet_string(self) + "."


    def cloud_look(self, ) -> str:
            return _weather_handler.cloud_string(self) + "."


    def __init__(self):
            self._weather_handler = WEATHER 


    def query_light(self, ) -> int:
            int new_light
            new_light = ( day_light * (int)_weather_handler->query_darkness
            ( self ) ) / 100
            if ( new_light != query_my_light() ) {
            ::set_light(new_light)


    def query_visibility(self, ) -> int:
            return _weather_handler.query_visibility(self)


    def set_light(self, number: int) -> int:
            ::set_light(number)
            day_light = number


    def long(self, word: str, dark: int) -> str:
            int day_time
            string ret
            string obscure
            mixed bit
            ret = ::long( word, dark )
            day_time = (int)_weather_handler.query_day( self )
            if ( day_time != current_day ) {
            if ( query_light_change() ) {
            call_other( self, query_light_change(), current_day )


    def dest_me(self, ) -> None:
            if(sunlight) {
            sunlight.dest_me()


    def event_exit(self, ob: MudObject, message: str, to: MudObject) -> None:
            if(!room_stabilize) {
            remove_asyncio.create_task(self.callout_handle)
            callout_handle = asyncio.create_task(self."clean_up_room", FAST_CLEAN_UP, 0)


    def clean_up_room(self, flag: int) -> int:
            object *obs, ob
            int elapsed_time = time() - room_create_time
            if(room_stabilize || !query_fast_clean_up() ||
            self.query_keep_room_loaded())
            return 0
            callout_handle = 0
            obs = filter(all_inventory(self),
            (: !living($1) || (userp($1)) ||
            !$1.query_property("transient") ||
            sizeof($1.query_attacker_list()) ||
            $1.cannot_walk() :))
            if(sizeof(all_inventory(self)) ||
            elapsed_time > (FAST_CLEAN_UP * 3)) {
            room_stabilize = 1
            return 1


    def set_fast_clean_up(self, number: int) -> None:
            _fast_clean_up = number


    def query_fast_clean_up(self, ) -> int:
            return _fast_clean_up



class Outside(MudObject):

    _weather_handler = 'WEATHER '
