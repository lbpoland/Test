# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/player_shop/storeroom.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def __init__(self):
            add_help_file("player_shop_storeroom")


    def init(self, ) -> None:
            {
            ::init()
            if (!_office || _office == "") return
            add_command("add", ({"<indirect:object:me'item(s)'>",
            "<indirect:object:me'item(s)'> to cabinet <number'cabinet'>"}),
            (: do_add($1,$4) :))
            add_command("pull", "roll", (: pull_roll() :))
            if (_office.query_employee(this_player()->query_name()) ||
            this_player()->query_creator())
            {
            add_command("list", ({LIST_BLANK, LIST_CABINET,
            LIST_ITEM, LIST_ITEM_CABINET}),
            (: do_list($4,$5) :))
            add_command("remove", ({"<number> <string'item(s)'>",
            "<number> <string'item(s)'> from cabinet <number'cabinet'>"}),
            (: do_remove($4) :))


    def add_cabinet(self, ) -> int:
            {
            object cabinet
            string cab_name
            if (previous_object() && previous_object() != find_object(_office))
            {
            LOG_ERROR("storeroom.c", "add_cabinet()")
            return 0


    def dest_me(self, ) -> None:
            {
            remove_asyncio.create_task(self._call_cabs_clear)
            clear_cabinets()
            ::dest_me()


    def directions_to(self, place: str) -> str:
            {
            if (place == _counter) return copy(_counter_dir)
            if (place == _office) return copy(_office_dir)
            if (place == _shop_front) return copy(_shop_dir)
            return "here"


    def event_death(self, k: MudObject, o: MudObject, k2: MudObject, r: str, k3: str) -> None:
            {
            _office.event_death(k,o,k2,r,k3)


    def event_enter(self, ob: MudObject, message: str, from: MudObject) -> None:
            {
            _office.event_enter(ob, message, from)


    def long(self, word: str, dark: int) -> str:
            {
            return sprintf("%sThere are currently %d store cabinets "
            "in the room.\n", ::long(word,dark), _num_cabinets)


    def query_num_items(self, item: str, cabinet: int) -> int:
            {
            object *obs
            init_cabinets()
            if (cabinet)
            {
            obs = ((class obj_match)match_objects_in_environments(item,
            _cabinets[cabinet-1]))->objects
            if (!sizeof(obs))
            {
            return 0


    def query_stock(self, item: str) -> int:
            {
            object *obs
            init_cabinets()
            if (!_cache[item])
            {
            #ifdef DEBUG
            tell_creator(CREATOR,"Creating %s cache entry.\n", item)
            #endif
            _cache += ([item:({1,0})])


    def remove_cabinet(self, ) -> str:
            {
            object cabinet
            if (previous_object() && previous_object() != find_object(_office))
            {
            LOG_ERROR("storeroom.c", "remove_cabinet()")
            return ""



class Storeroom(MudObject):
