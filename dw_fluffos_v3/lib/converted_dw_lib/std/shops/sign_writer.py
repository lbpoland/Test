# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/sign_writer.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._signtypes = []
            self._paintcolours = ([ ])
            self._signs = ([ ])


    def is_open(self, ) -> int:
            if (_open_func) {
            return evaluate(_open_func)


    def set_open_func(self, func: Any) -> None:
            _open_func = func


    def set_language(self, lang: str) -> None:
            _language = lang


    def query_language(self, ) -> str:
            return _language


    def set_save_file_name(self, save: str) -> None:
            _save_file = save


    def query_save_file_name(self, ) -> str:
            return _save_file


    def do_save(self, ) -> None:
            if (_save_file) {
            save_object(_save_file)


    def do_load(self, ) -> None:
            if (_save_file) {
            restore_object(_save_file)


    def add_paint_colour(self, colour: str, cost: int) -> None:
            _paintcolours[colour] = cost


    def do_order(self, type: str) -> int:
            int pos
            int cost
            string place
            if (!is_open()) {
            add_failed_mess(the_short() + " is not currently open.\n")
            return 0


    def finish_editing_message(self, mess: str, type: int) -> None:
            string colour
            int cost
            string place
            class sign_type bing
            if (!mess) {
            write("Aborting sign writing process.\n")
            return


    def finish_sign(self, colour: str, type: int, mess: str) -> None:
            int cost
            string place
            class sign_type bing
            colour = lower_case(colour)
            bing = _signtypes[type]
            if (!strlen(colour)) {
            write("Aborting the sign process.\n")
            return


    def do_collect(self, ) -> int:
            class sign_making sign
            class sign_type type
            object* ok
            string* not_yet
            string* bits
            object ob
            if (!is_open()) {
            add_failed_mess(the_short() + " is not currently open.\n")
            return 0


    def do_browse(self, type: str) -> int:
            class sign_type bing
            string place
            int pos
            if (!is_open()) {
            add_failed_mess(the_short() + " is not currently open.\n")
            return 0


    def do_list(self, ) -> int:
            class sign_type bing
            int i
            string ret
            string place
            string colour
            int cost
            if (!is_open()) {
            add_failed_mess(the_short() + " is not currently open.\n")
            return 0


    def init(self, ) -> None:
            add_command("list", "", (: do_list() :))
            add_command("browse", "<string'sign'>", (: do_browse($4[0]) :))
            add_command("collect", "sign", (: do_collect() :))
            add_command("buy", "<string'sign'>", (: do_order($4[0]) :))
            add_command("order", "<string'sign'>", (: do_order($4[0]) :))



class Sign_writer(MudObject):

    _signtypes = '[]'

    _paintcolours = '([ ])'

    _signs = '([ ])'
