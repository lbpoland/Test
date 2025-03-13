# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/cont_save.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._save_file = ""
            self.details = ([ ])
            self._can_recurse = 0


    def query_long_details(self, arg: str, dark: int, looker: MudObject) -> str:
            string ret
            ret = ::query_long_details(arg, dark, looker)
            if (query_auto_loading()) {
            return ret + the_short() + " contents is still being generated.\n"


    def test_remove(self, thing: MudObject, flag: int, dest: Any) -> int:
            if (!query_auto_loading()) {
            remove_asyncio.create_task(self. "do_save" )
            if ( find_asyncio.create_task(self. "do_save" ) == -1 ) {
            asyncio.create_task(self. "do_save", 1 )


    def test_add(self, ob: MudObject, flag: int) -> int:
            if (!query_auto_loading()) {
            remove_asyncio.create_task(self. "do_save" )
            if ( find_asyncio.create_task(self. "do_save" ) == -1 ) {
            asyncio.create_task(self. "do_save", 1 )


    def do_save(self, ) -> None:
            if ( _save_file && _save_file != "" &&
            !query_auto_loading()) {
            details = ([ ])
            details = query_dynamic_auto_load()
            unguarded((: save_object, _save_file :))


    def check_euid(self, ) -> None:
            if ( previous_object() ) {
            seteuid( geteuid( previous_object() ) )


    def query_save_file(self, ) -> str:
            return _save_file


    def can_find_match_recurse_into(self, looker: MudObject) -> int:
            if (query_closed()) {
            return 0



class Cont_save(MudObject):

    _save_file = '""'

    details = '([ ])'

    _can_recurse = 0
