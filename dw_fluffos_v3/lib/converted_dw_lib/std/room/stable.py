# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/stable.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def load_me(self, ) -> None:
            class stable {
            int date_in
            int last_paid
            string name
            mixed* save_info


    def __init__(self):
            self._start_cost = 400
            self._cost_per_week = 400
            self._stable_cache = ([ ])
            self._accounts = ([ ])
            self._stable_types = []


    def init(self, ) -> None:
            add_command( "list", "", (: do_list() :) )
            add_command( "stable", "<indirect:object:here>", (: do_stable($1) :) )
            add_command( "deposit", "<string'money'>", (: do_deposit($4[0]) :) )
            add_command( "return", "<string'horse num'>", (: do_return($4[0]) :) )


    def set_save_directory(self, directory: str) -> None:
            if ( directory[<1] != '/' )
            directory += "/"
            _directory = directory
            load_me()


    def query_save_directory(self, ) -> str:
            return _directory


    def set_start_cost(self, start_cost: int) -> None:
            _start_cost = start_cost


    def query_start_cost(self, ) -> int:
            return _start_cost


    def set_cost_per_week(self, cost_per_week: int) -> None:
            _cost_per_week = cost_per_week


    def query_cost_per_week(self, ) -> int:
            return _cost_per_week


    def save_me(self, ) -> None:
            unguarded( (: save_object(_directory + "main_account") :) )


    def load_me(self, ) -> None:
            unguarded( (: restore_object(_directory + "main_account", 1) :) )


    def query_balance(self, name: str) -> int:
            return _accounts[name]


    def set_balance(self, name: str, amt: int) -> None:
            _accounts[name] = amt
            save_me()


    def adjust_balance(self, name: str, amt: int) -> None:
            _accounts[name] += amt
            save_me()


    def query_player_money(self, player: MudObject, place: str) -> int:
            return player.query_value_in( place ) +
            query_balance( player.query_name() )


    def remove_player_money(self, player: MudObject, amt: int, place: str) -> None:
            int balance
            balance  = query_balance( player.query_name() )
            if ( balance < 0 ) {
            amt += -balance
            balance = 0
            } else {
            if ( amt <= balance ) {
            balance -= amt
            amt = 0
            } else {
            amt -= balance
            balance = 0


    def add_stable_type(self, type: str) -> None:
            if ( _stable_types .index( type) if  type in _stable_types  else -1 == -1) {
            _stable_types += [type]


    def can_stable_type(self, type: str) -> int:
            if ( _stable_types .index( type) if  type in _stable_types  else -1 != -1 ) {
            return 1


    def query_stabling_cost(self, name: str, pos: int) -> int:
            class stable* bing
            bing = query_stable( name )
            if ( pos < 0 || pos >= sizeof( bing ) ) {
            return 0


    def add_to_stable(self, name: str, horses: Any) -> int:
            class stable* bing
            class stable womble
            object horse
            bing = query_stable( name )
            if ( !bing ) {
            bing = [})


    def print_ok_message(self, me: MudObject, horses: Any) -> None:
            write( "You stable " + query_multiple_short( horses ) + " into " +
            the_short() + ".\n" )
            say( this_player()->the_short() + " stables " +
            query_multiple_short( horses ) + " into " + the_short() + ".\n" )


    def do_stable(self, obs: MudObject) -> int:
            class stable* bing
            int cost
            object horse
            object *ok
            string place
            place = query_property( "place" )
            if ( !place )
            place = "default"
            bing = query_stable( this_player()->query_name() )
            ok = [})
            foreach ( horse in obs ) {
            if ( !can_stable_type( horse.query_transport_type() ) ) {
            add_failed_mess( "$I is not able to be stabled here.\n", [horse] )
            } else if ( horse.query_owner() != this_player()->query_name() ) {
            add_failed_mess( "You do not own $I and therefore cannot stable them.\n",
            [horse] )
            } else {
            ok += [horse]
            cost += _start_cost


    def do_list(self, ) -> int:
            class stable* bing
            int i
            int cost
            int balance
            string debt
            string place
            place = query_property( "place" )
            if ( !place )
            place = "default"
            bing = query_stable( this_player()->query_name() )
            balance = query_balance( this_player()->query_name() )
            if ( !bing || !sizeof( bing ) ) {
            if( !balance ) {
            add_failed_mess( "You do not have any horses stabled here.\n" )
            return 0


    def do_return(self, num: str) -> int:
            class stable* bing
            int pos
            int cost
            object* horses
            string place
            place = query_property( "place" )
            if ( !place )
            place = "default"
            bing = query_stable( this_player()->query_name() )
            if ( !sizeof( bing ) ) {
            add_failed_mess( "You do not have any horses stabled here.\n" )
            return 0


    def do_deposit(self, mon: str) -> int:
            string place
            mixed money
            int amt
            place = query_property( "place" )
            if ( !place )
            place = "default"
            if ( undefinedp( query_balance( this_player()->query_name() ) ) ) {
            add_failed_mess( "You do not currently have a balance here.\n" )
            return 0



class Stable(MudObject):

    _start_cost = 400

    _cost_per_week = 400

    _stable_cache = '([ ])'

    _accounts = '([ ])'

    _stable_types = '[]'
