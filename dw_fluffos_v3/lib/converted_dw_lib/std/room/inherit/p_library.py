# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/inherit/p_library.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def save_me(self, ) -> None:
            protected string make_pretty_catalog( string arg, string from, string to, string specific )
            protected int compare_widgets( object new_ob, int existing_id )
            protected void build_catalogs(){
            int id
            class _book book
            foreach( id, book in _catalog ){
            if( _catalog_by_author[ lower_case(book->cap_author) ] )
            _catalog_by_author[ lower_case(book->cap_author) ] += [id]
            else
            _catalog_by_author[ lower_case(book->cap_author) ] = [id]
            if( _catalog_by_title[ lower_case(book->cap_title) ] )
            _catalog_by_title[ lower_case(book->cap_title) ] += [id]
            else
            _catalog_by_title[ lower_case(book->cap_title) ] = [id]


    def __init__(self):
            self._catalog_by_author = ([ ])
            self._catalog_by_title = ([ ])
            self._player_contributable = 1
            self._library_name = "The illustrious library of fluff"
            self._save_file = base_name( this_object() ) + ".o"
            self._catalog = ([ ])
            self._accounts = ([ ])
            self._fines = ([ ])
            self._access = ([ ])
            self._loan_length = 3 * 24 * 60 * 60
            self._fine_per_day = 400
            self._lost_damaged_fine = 1050
            self._max_loans = 5


    def init(self, ) -> None:
            if( _player_contributable ){
            add_command( "add", "<indirect:object:me'book'> with "
            "title <string'title'> by author <word'author'>",
            (: do_add( $1, $4[1], $4[2] ) :) )
            add_command( "remove", "<number'book id'>",
            (: do_remove_book( $4[0] ) :))


    def do_add(self, obs: MudObject, title: str, author: str) -> int:
            object t_p, t_o
            int num, id, *ids
            t_p = this_player()
            t_o = self
            debug_printf( "Obs: %O\n", obs )
            if( query_access(this_player()) < LIBRARIAN_ACCESS ){
            add_failed_mess("Only librians can do this.\n")
            return 0


    def remove_book(self, id: int) -> None:
            object ob
            class _book book
            int i
            if( !_catalog[id] )
            return
            book = _catalog[id]
            for( i = 0; i < (book->copies - sizeof(book->loaned)); i++ ){
            if( book->path )
            ob = clone_object( book->path )
            if( book->auto_load )
            ob = PLAYER_OB.load_auto_load_to_array( book->auto_load, this_player() )[0]
            ob.move( self )


    def do_remove_book(self, id: int) -> int:
            int out
            string player, bit
            class _account account
            class _loan loan
            if( query_access(this_player()) < LIBRARIAN_ACCESS ){
            add_failed_mess("Only librians can do this.\n")
            return 0


    def do_borrow(self, arg: Any) -> int:
            int id, ret, t
            object ob
            class _book book
            class _loan loan
            string name
            name = this_player()->query_name()
            id = to_int(arg)
            if( query_access(this_player()) < USER_ACCESS ){
            add_failed_mess("You do not have access to this library.\n")
            return 0


    def do_return(self, obs: MudObject) -> int:
            string name, bit
            int id, *owed, i, *ours, due
            class _loan loan
            class _book book
            object ob, *not_ours, *wrong_player, *returned
            name = this_player()->query_name()
            owed = [})
            ours = not_ours = wrong_player = returned = [})
            if( !sizeof(_accounts[name]->loans) ){
            add_failed_mess( "You don't have any books out on loan.\n" )
            return 0


    def do_list(self, arg: str, from: str, to: str, specific: str) -> int:
            if( (to && !stringp(to)) || (from && !stringp(from)) ){
            add_failed_mess( "The ranges must be letters.\n")
            return 0


    def do_pay(self, ) -> int:
            int cash, fine
            string place, str
            place = query_property( "place" )
            if ( !place || ( place == "" ) )
            place = "default"
            cash = this_player()->query_value_in( place )
            if ( place != "default" )
            cash += this_player()->query_value_in( "default" )
            if( !cash ){
            add_failed_mess("You have money!.\n")
            return 0


    def do_status(self, player: str) -> int:
            int fine
            string place, str, bit
            class _loan loan
            if( !player )
            player = this_player()->query_name()
            player = lower_case(player)
            if( player != this_player()->query_name() &&
            query_access(this_player()) < LIBRARIAN_ACCESS ){
            add_failed_mess("You do not have access to see other accounts.\n")
            return 0


    def do_book_status(self, id: int) -> int:
            string str, name, date
            class _book book
            id = to_int(id)
            if( !_catalog[id] ){
            add_failed_mess("The id " +id+ ", does not point to an item.\n")
            return 0


    def do_set(self, player: str, type: str) -> int:
            player = lower_case(player)
            if( query_access(self) <= query_access(player) ){
            add_failed_mess( "You do not have permission to do this.\n")
            return -1


    def do_mark(self, id: int, flag: int) -> int:
            if( query_access(this_player()) < LIBRARIAN_ACCESS ){
            add_failed_mess("You do not have permission to do this.\n")
            return 0


    def do_set_fine(self, i: int) -> int:
            string place
            if( query_access(this_player()) < LIBRARIAN_ACCESS ){
            add_failed_mess("You do not have permission to do this.\n")
            return 0


    def do_set_loan_length(self, days: int) -> int:
            string str
            if( query_access(this_player()) < LIBRARIAN_ACCESS ){
            add_failed_mess("You do not have permission to do this.\n")
            return 0


    def do_set_max_loans(self, i: int) -> int:
            if( query_access(this_player()) < LIBRARIAN_ACCESS ){
            add_failed_mess("You do not have permission to do this.\n")
            return 0


    def do_lost_damaged_fine(self, i: int) -> int:
            string place
            if( query_access(this_player()) < LIBRARIAN_ACCESS ){
            add_failed_mess("You do not have permission to do this.\n")
            return 0


    def do_report(self, id: int, arg: str, player: str) -> int:
            string str
            class _loan loan, match
            if( player && query_access(this_player()) < LIBRARIAN_ACCESS ){
            add_failed_mess("You can only report your damaged or lost books.\n")
            return 0


    def clear_loan(self, player: Any, id: int, calc_fines: int) -> None:
            int fine
            class _loan loan
            if( objectp(player) && userp(player) )
            player = player.query_name()
            if( !stringp(player) )  return
            if( !_accounts[player] || !sizeof(_accounts[player]->loans) )  return
            foreach( loan in _accounts[player]->loans ){
            if( loan->id == id ){
            if( calc_fines && (loan->due_back - time() < 0) ){
            fine = (((time() - loan->due_back) / AM_SECONDS_PER_DAY) + 1) * _fine_per_day
            if( _fines[player] )
            _fines[player] += fine
            else
            _fines[player] = fine


    def extra_look(self, ob: MudObject) -> str:
            string *libs, str, place
            str = "Welcome to " + _library_name + ".\n"
            libs = filter( keys(_access), (: _access[$1] == LIBRARIAN_ACCESS :) )
            if( !sizeof(libs) )
            str += "Currently there are no caretakers of the books.\n"
            if( sizeof(libs) == 1 )
            str += PLAYER_HANDLER.query_cap_name(libs[0]) + " is the sole caretaker "
            " of the books.\n"
            if( sizeof(libs) > 1 ){
            libs = map( libs, (: PLAYER_HANDLER.query_cap_name($1) :) )
            str += query_multiple_short(libs) + " are caretakers of the books.\n"


    def save_me(self, ) -> None:
            if( find_asyncio.create_task(self."save_it") == -1 )
            asyncio.create_task(self. "save_it", 2 )


    def query_fine(self, name: str) -> int:
            mapping query_catalog(){
            return _catalog


    def set_access(self, player: str, access: int) -> None:
            if( !access ){
            map_delete( _access, player )
            } else {
            _access[player] = access


    def query_access(self, player: Any) -> int:
            return LIBRARIAN_ACCESS



class P_library(MudObject):

    _catalog_by_author = '([ ])'

    _catalog_by_title = '([ ])'

    _player_contributable = 1

    _library_name = '"The illustrious library of fluff"'

    _save_file = 'base_name( this_object() ) + ".o"'

    _catalog = '([ ])'

    _accounts = '([ ])'

    _fines = '([ ])'

    _access = '([ ])'

    _loan_length = '3 * 24 * 60 * 60'

    _fine_per_day = 400

    _lost_damaged_fine = 1050

    _max_loans = 5
