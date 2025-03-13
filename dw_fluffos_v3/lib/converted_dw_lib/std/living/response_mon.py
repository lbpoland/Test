# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/living/response_mon.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._respond_to_with = []
            self._response_data = new(class response_data)
            self._response_data->only_respond_to = []


    def set_response_mon_understand_anything(self, flag: int) -> None:
            _response_data->understand_anything = flag


    def query_response_mon_debug_mode(self, ) -> int:
            return self.query_property("respon mon debug")


    def set_response_mon_debug_mode(self, flag: int) -> None:
            self.add_property("respon mon debug", flag)


    def query_stop_responding(self, ) -> int:
            int query_response_allowed(object ob,
            string *response) {
            if (!self.query_visible(ob)) {
            return 0


    def set_respond_to_with(self, map: Any) -> None:
            mixed *old_keys
            int i
            if ( mapp( map ) ) {
            #ifdef DEBUG
            log_file("BAD_RESPONSE", "set_respond_to_with() called by %O (%s)\n",
            previous_object(), previous_object()->query_name())
            #endif
            old_keys = keys(map)
            _respond_to_with = allocate(sizeof(old_keys) * 2)
            for (i = sizeof(old_keys); i--; ) {
            _respond_to_with[2*i] = old_keys[i]
            _respond_to_with[2*i+1] = map[old_keys[i]]


    def add_respond_to_with(self, trigger: Any, response: Any) -> None:
            _respond_to_with += [trigger, response]


    def add_only_respond_to(self, person: MudObject) -> None:
            _response_data->only_respond_to += [person]


    def remove_only_respond_to(self, person: MudObject) -> None:
            _response_data->only_respond_to -= [person]


    def query_only_respond_to(self, ) -> List[MudObject]:
            return _response_data->only_respond_to


    def check_loop(self, per: MudObject, mess: str) -> int:
            if(interactive(per)) {
            return 0


    def event_person_sayto(self, per: MudObject, mess: str, lang: str, targets: Any) -> None:
            string skill
            if(_response_data->stop_responding ||
            !sizeof(_respond_to_with) ||
            environment() == find_object( "/room/rubbish" ) ||
            environment() == find_object( "/room/void" ) ||
            !per || per == self) {
            return


    def event_person_say(self, per: MudObject, start: str, mess: str, lang: str) -> None:
            string skill
            if(_response_data->stop_responding ||
            !sizeof(_respond_to_with) ||
            environment() == find_object( "/room/rubbish" ) ||
            environment() == find_object( "/room/void" ) ||
            !per || per == self) {
            return



class Response_mon(MudObject):

    _respond_to_with = '[]'

    _response_data = 'new(class response_data)'

    _response_data->only_respond_to = '[]'
