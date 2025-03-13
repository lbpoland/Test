# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/global/wiz_file_comm.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.allowed = []


    def is_friend(self, str: str) -> int:
            return ::is_friend(str) ||
            allowed.index(str) if str in allowed else -1 != -1


    def query_friend_tag(self, str: str) -> str:
            string womble
            if(!userp(previous_object())) {
            womble = ::query_friend_tag(str)
            if (!womble) {
            if (allowed.index(str) if str in allowed else -1 != -1) {
            return "allowed to reference"


    def query_visible(self, thing: MudObject) -> int:
            string word
            if (thing == self) {
            return 1


    def query_in_editor(self, ) -> Any:
            return _in_wiz_editor || ::query_in_editor()


    def set_in_editor(self, what: Any) -> None:
            _in_wiz_editor = what


    def query_path(self, ) -> str:
            return query_current_path()


    def query_ed_setup(self, ) -> int:
            return query_property("ed_setup")


    def set_ed_setup(self, i: int) -> None:
            add_property("ed_setup", i)


    def review(self, ) -> int:
            playtester::review()
            wiz_info_comm::review()
            return 1


    def query_last_location(self, ) -> Any:
            protected string process_input(string inp){
            int start
            start = strsrch(inp, '@')
            if(start > 0){
            int space = strsrch(inp, ' ')
            if(!(space > 0 && ((space == start+1) || space < start))){
            inp = inp[0..start] + " " + inp[start+1..]



class Wiz_file_comm(MudObject):

    allowed = '[]'
