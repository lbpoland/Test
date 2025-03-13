# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/bank.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.account_cost = 0
            self.percentage = 90
            self.total_account = 0
            self.total_made = 0
            self.bank_name = "Bing's First"
            self.place = "default"


    def init(self, ) -> None:
            add_command( "balance", "" )
            add_command( "withdraw", "<number> <string>",
            (: do_withdraw($4[0], $4[1]) :) )
            add_command( "open", "account" )
            add_command( "close", "account" )
            add_command( "deposit", "<string>", (: do_deposit($4[0]) :) )
            ::init()


    def set_save_file(self, word: str) -> None:
            save_file = word
            if ( file_size( save_file +".o" ) > 0 )
            unguarded((: restore_object, save_file :))


    def do_save(self, ) -> None:
            if ( !save_file ) {
            return


    def get_account(self, ) -> int:
            int amount
            if ( amount = (int)this_player()->query_property( "bank "+ OLD_BANK ) ) {
            HANDLER.adjust_account( NAME, bank_name, amount )
            this_player()->remove_property( "bank "+ OLD_BANK )
            total_account += amount
            do_save()


    def set_account(self, amount: int) -> int:
            HANDLER.set_account( NAME, bank_name, amount )


    def do_balance(self, ) -> int:
            int amount
            amount = get_account()
            if ( amount < 0 ) {
            notify_fail( "You do not have an account here.\n" )
            return 0


    def do_withdraw(self, number: int, type: str) -> int:
            int amount
            int best
            int total
            object money
            total = get_account()
            if ( total < 0 ) {
            notify_fail( "You do not have an account here.\n" )
            return 0


    def do_deposit(self, words: str) -> int:
            int amount
            int total
            int tmp
            mixed money
            object *tender
            object legal
            object illegal
            string howmuch
            total = get_account()
            if ( total < 0 ) {
            notify_fail("You don't have an account here.\n")
            return 0


    def do_open(self, ) -> int:
            int amount
            object money
            if ( get_account() >= 0 ) {
            notify_fail( "You already have an account here.\n" )
            return 0


    def check_open(self, word: str) -> int:
            object money
            word = lower_case( word )
            if (word [ 0 ] ==  110 ) {
            write( "Okay, not opening an account.\n" )
            return 1


    def do_close(self, ) -> int:
            int total
            object money
            total = get_account()
            if ( total < 0 ) {
            notify_fail( "You do not have an account here.\n" )
            return 0


    def make_bank_robbers(self, ) -> int:
            int i, amount, loss, number, percent_loss, total
            string player_name
            object *bags, *money, *players, *robbers
            mixed *mon_array
            percent_loss = 2 + random( 4 )
            players = users()
            for ( i = 0; i < sizeof( players ); i++ ) {
            player_name = (string)players[ i ]->query_name()
            if ( ( amount = (int)HANDLER.query_account( player_name, bank_name ) ) ) {
            switch( amount ) {
            case 1 .. 10:
            loss = 0
            break
            case 11 .. 100:
            loss = ( amount * percent_loss ) / 100
            break
            case 101 .. 1000:
            loss = ( amount * percent_loss * 2 ) / 100
            break
            case 1001 .. 10000:
            loss = ( amount * percent_loss * 3 ) / 100
            break
            case 10001 .. 100000:
            loss = ( amount * percent_loss * 4 ) / 100
            break
            default:
            loss = ( amount * percent_loss * 5 ) / 100



class Bank(MudObject):

    account_cost = 0

    percentage = 90

    total_account = 0

    total_made = 0

    bank_name = '"Bing\'s First"'

    place = '"default"'
