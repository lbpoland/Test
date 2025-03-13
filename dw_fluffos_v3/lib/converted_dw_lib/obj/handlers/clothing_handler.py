# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/clothing_handler.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from .utilities import CLOTHING_HANDLER
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._types = ([ ])
            self._equivilants = ([ ])
            self._zones = ([ ])
            self._zone_level = []


    def query_items_blocking(self, thing: MudObject, player: MudObject) -> List[MudObject]:
            int i
            int j
            int k
            string *stuff
            object *blocking
            mixed junk
            mixed main_types
            object *wearing
            main_types = thing.query_type()
            if (stringp(main_types)) {
            main_types = [main_types]


    def can_wear_or_remove(self, thing: MudObject, player: MudObject) -> str:
            object *blocking
            blocking = query_items_blocking(thing, player)
            if (sizeof(blocking)) {
            return "when you are wearing "+ query_multiple_short(blocking)


    def query_clothing_depth(self, type: Any) -> int:
            class clothing_type bing
            int depth
            string str
            int min_depth
            if (stringp(type)) {
            bing = _types[type]
            if (bing) {
            return bing->_depth


    def query_clothing_maximum_depth(self, type: Any) -> int:
            class clothing_type bing
            int depth
            string str
            int max_depth
            if (stringp(type)) {
            bing = _types[type]
            if (bing) {
            return bing->_depth


    def query_zone_name(self, type: str) -> str:
            string zone
            string *stuff
            foreach (zone, stuff in _zones) {
            if (stuff.index(type) if type in stuff else -1 != -1) {
            return zone


    def query_zone_level(self, zone: str) -> int:
            int i
            i = _zone_level.index(zone) if zone in _zone_level else -1
            return i * 100


    def query_equivilant_type(self, type: str) -> str:
            return _equivilants[type]


    def query_valid_type(self, type: str) -> int:
            if (query_clothing_type(type) ||
            query_equivilant_type(type)) {
            return 1



class Clothing_handler(MudObject):

    _types = '([ ])'

    _equivilants = '([ ])'

    _zones = '([ ])'

    _zone_level = '[]'
