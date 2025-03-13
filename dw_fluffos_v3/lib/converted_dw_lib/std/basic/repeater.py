# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/basic/repeater.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def set_repeater_owner(self, owner: MudObject) -> None:
            _repeater = owner


    def query_repeater_owner(self, ) -> MudObject:
            return _repeater


    def event_person_say(self, ob: MudObject, start: str, mess: str, lang: str) -> None:
            if (_repeater) {
            _repeater->repeat_event_person_say(self,
            ob,
            start,
            mess,
            lang)


    def event_emote(self, ob: MudObject, mess: str) -> None:
            if (_repeater) {
            _repeater->repeat_event_emote(self,
            ob,
            mess)


    def event_say(self, ob: MudObject, str: str, avoid: Any) -> None:
            if (_repeater) {
            _repeater->repeat_event_say(self,
            ob,
            str,
            avoid)


    def event_soul(self, ob: MudObject, str: str, avoid: Any) -> None:
            if (_repeater) {
            _repeater->repeat_event_soul(self,
            ob,
            str,
            avoid)



class Repeater(MudObject):
