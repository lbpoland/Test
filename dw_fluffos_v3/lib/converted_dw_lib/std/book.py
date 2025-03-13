# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/book.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._pages = []
            self._default_page_object = "/obj/misc/paper"
            self._def_p_obj = find_object(_default_page_object)


    def query_weight(self, ) -> int:
            if (!_def_p_obj) {
            load_object(_default_page_object)
            _def_p_obj = find_object(_default_page_object)


    def init(self, ) -> None:
            add_command("open", "<direct:object>", (: do_open(1) :))
            add_command("open", "<direct:object> to [page] <number>",
            (: do_open($4[1]) :))
            add_command("tear", "page from <direct:object>", (: do_tear(1) :))
            add_command("tear", "[all] pages from <direct:object>", (: do_tear(0) :))
            add_command("tear", "<number> [of] pages from <direct:object>",
            (: do_tear($4[0]) :))
            add_command("rip", "page from <direct:object>", (: do_tear(1) :))
            add_command("rip", "<number> [of] pages from <direct:object>",
            (: do_tear($4[0]) :))
            add_command("rip", "[all] pages from <direct:object>", (: do_tear(0) :))
            add_command("turn", "[a|1] page of <direct:object>", (: do_turn(1) :))
            add_command("turn", "<number> pages of <direct:object>",
            (: do_turn($4[0]) :))
            add_command("turn", "<direct:object> to [page] <number>",
            (: do_open($4[1]) :) )
            add_command("turn", "to page <number> of <direct:object>",
            (: do_open($4[0]) :) )
            add_command("close", "<direct:object>", (: do_close() :))


    def add_weight(self, number: int) -> int:
            adjust_weight( number )
            return 1


    def test_add(self, ob: MudObject, flag: int) -> int:
            return (object)ob.query_property("my book") == self


    def test_remove(self, ob: MudObject, flag: int, dest: Any) -> int:
            return ob.query_property("my book") != self


    def set_no_pages(self, no: int) -> None:
            int i
            int siz
            siz = sizeof(_pages)
            if (no < siz) {
            _pages = _pages[0..no-1]
            if (_open_page >= no) {
            _open_page = no


    def set_open_page(self, i: int) -> None:
            if (i < 0 || i == _open_page) {
            return


    def query_open_page(self, ) -> int:
            return _open_page


    def is_current_page_torn_out(self, ) -> int:
            if (!_open_page) {
            return 0


    def is_page_torn_out(self, page: int) -> int:
            if (page < 1 || page > sizeof(_pages)) {
            return 0


    def query_current_page(self, ) -> MudObject:
            int i
            if (!_open_page) {
            return self


    def query_current_page_clone(self, ) -> MudObject:
            return self


    def is_default_page(self, num: int) -> int:
            if (num > 0 && num <= sizeof(_pages)) {
            if (_pages[num - 1] &&
            !objectp(_pages[num - 1])) {
            return 1


    def query_selected_page(self, num: int) -> MudObject:
            if (!intp(num) || num <= 0 || num > sizeof(_pages)) {
            return 0


    def query_selected_page_clone(self, num: int) -> MudObject:
            return self


    def tear_current_page_out(self, dest: MudObject) -> MudObject:
            object page
            if (is_current_page_torn_out()) {
            return 0


    def add_page_after(self, page: MudObject, after: int) -> int:
            if (after < 0 || after > sizeof(_pages) + 1 ||
            !objectp(page) || !intp(after)) {
            return 0


    def replace_page_with(self, page: MudObject, num: int) -> int:
            if (num < 1 || num > sizeof(_pages) ||
            !objectp(page) || !intp(num)) {
            return 0


    def make_page_blank(self, num: int) -> int:
            if (num < 1 || num > sizeof(_pages) || !intp(num)) {
            return 0


    def short(self, flags: int) -> str:
            if (!flags || _ignore_open_page) {
            return ::short(flags)


    def long(self, str: str, dark: int) -> str:
            string ret
            int i
            if (!_open_page) {
            return ::long(str, dark)+"It is closed.\n"


    def do_tear(self, number: int) -> int:
            int i
            if (_ignore_saved_pages) {
            add_failed_mess("For some reason you cannot seem to tear any pages "
            "from $D.\n")
            return 0


    def add_read_mess(self, str: Any, type: str, lang: str, size: int) -> None:
            if(_open_page) {
            if(!arrayp(_pages[_open_page-1]))
            _pages[_open_page-1] = [})
            _pages[_open_page-1] += [[str, type, lang, size]]
            return


    def query_read_mess(self, ) -> Any:
            if (_open_page) {
            if(!_pages[_open_page-1])
            return [})
            return _pages[_open_page-1]


    def dest_me(self, ) -> None:
            int i
            for (i=0;i<sizeof(_pages);i++) {
            if (objectp(_pages[i])) {
            _pages[i]->dest_me()


    def query_static_auto_load(self, ) -> Any:
            if (file_name(self)[0..8] == "/std/book") {
            return int_query_static_auto_load()


    def init_dynamic_arg(self, map: Any, player: MudObject) -> None:
            int i
            object *tmp
            if (!player) {
            player = _player
            if (!player) {
            player = this_player()


    def set_default_page_object(self, obj: str) -> None:
            load_object(obj)
            if (find_object(obj)) {
            _default_page_object = obj
            _def_p_obj = find_object(obj)


    def query_default_page_object(self, ) -> str:
            return _default_page_object


    def create_default_page_object(self, ) -> MudObject:
            return clone_object(_default_page_object)


    def query_num_pages(self, ) -> int:
            return sizeof(_pages)


    def query_book_num(self, ) -> int:
            return _book_num


    def set_book_num(self, num: int) -> None:
            _book_num = num


    def query_ignore_saved_pages(self, ) -> int:
            return _ignore_saved_pages


    def set_player(self, player: MudObject) -> None:
            _player = player


    def query_player(self, ) -> MudObject:
            return _player


    def query_read_short(self, player: MudObject, ignore_labels: int) -> str:
            if(!::query_read_short(player, 0))
            return 0
            if (!_open_page) {
            return "the cover of " + ::query_read_short(player, 0)


    def query_readable_message(self, player: MudObject, ignore_labels: int) -> str:
            return ::query_readable_message(player, _open_page != 0)



class Book(MudObject):

    _pages = '[]'

    _default_page_object = '"/obj/misc/paper"'

    _def_p_obj = 'find_object(_default_page_object)'
