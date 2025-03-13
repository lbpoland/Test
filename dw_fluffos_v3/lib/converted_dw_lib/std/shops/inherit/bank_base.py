# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/inherit/bank_base.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._account_cost = 400
            self._total_difference = 0
            self._percentage = 10


    def query_bank(self, ) -> int:
            return 1


    def adjust_total_difference(self, amount: int) -> None:
            _total_difference += amount


    def set_total_difference(self, amount: int) -> None:
            _total_difference = amount


    def get_account(self, player: str) -> int:
            return HANDLER.query_account( player, _bank_name )


    def set_account(self, player: str, amount: int) -> None:
            HANDLER.set_account( player, _bank_name, amount )


    def adjust_account(self, person: str, amount: int) -> None:


    def query_franchise(self, ) -> str:
            return _franchise


    def set_franchise(self, franchise: str) -> None:
            _franchise = franchise


    def can_adjust_account(self, person: str, amount: int) -> int:
            if ( ( get_account( person ) + amount ) >= 0 ) {
            return 1


    def find_main_bank(self, ) -> MudObject:
            object office
            string room
            room = BANK_HANDLER.query_bank_master_office(_bank_name)
            if (!room) {
            return 0


    def query_main_branch_owner(self, ) -> str:
            object branch
            branch = find_main_bank()
            if (!branch) {
            return "no owner"


    def do_balance(self, ) -> int:
            int amount
            if (!query_bank_name()) {
            add_failed_mess("This is a forgotten bank in a dusty land.\n")
            return 0


    def do_withdraw(self, type: str) -> int:
            int amount
            int total
            object money
            if (this_player()->query_property("dead"))  {
            add_failed_mess("You are dead.  You know what they say; you can't take "
            "it with you.\n")
            return 0


    def do_deposit(self, words: str) -> int:
            int amount
            int total
            int tmp
            int howmuch
            mixed money
            if (!query_bank_name()) {
            add_failed_mess("This is a forgotten bank in a dusty land.\n")
            return 0


    def do_open(self, ) -> int:
            int amount
            if (!is_open_for("open account", this_player()->query_name())) {
            add_failed_mess("The bank is not open for new accounts.\n")
            return 0


    def check_open(self, word: str) -> None:
            object money
            int amount
            object main
            word = lower_case( word )
            if (!strlen(word) || word [ 0 ] !=  'y') {
            write( "Okay, not opening an account.\n" )
            return


    def do_close(self, ) -> int:
            int total
            object money
            total = get_account(this_player()->query_name())
            if ( total < 0 ) {
            notify_fail( "You do not have an account here.\n" )
            return 0


    def init(self, ) -> None:
            add_command( "balance", "" )
            add_command( "withdraw", "<string>",
            (: do_withdraw($4[0]) :) )
            add_command( "open", "account" )
            add_command( "close", "account" )
            add_command( "deposit", "<string>", (: do_deposit($4[0]) :) )



class Bank_base(MudObject):

    _account_cost = 400

    _total_difference = 0

    _percentage = 10
