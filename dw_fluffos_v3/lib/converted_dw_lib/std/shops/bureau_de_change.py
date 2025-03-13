# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/bureau_de_change.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def exchanges_list(self, ) -> str:
            int i, value, smallest
            string list, *places
            if ( !sizeof( exchanges ) )
            return "There are no exchanges to be made here."
            list = ""
            places = keys( exchanges )
            for ( i = 0; i < sizeof( places ); i++ ) {
            list += places[ i ] +":\n      $I$+20,+10="+
            (string)MONEY_HAND.money_value_string( standard, place ) +
            " will buy: "
            value = ( exchanges[ places[ i ] ][ 0 ] * standard ) / 100
            smallest = MONEY_HAND.smallest_value_in( places[ i ] )
            if (value % smallest != 0)  value += smallest - (value % smallest)
            list += (string)MONEY_HAND.money_value_string( value, places[ i ] )
            if ( buy_only ) {
            list += ".$I$-20,-10="
            if ( i < sizeof( places ) - 1 )
            list += "\n"
            } else {
            list += ";$I$-20,-10=\n$I$+20,+10=      for "+
            (string)MONEY_HAND->money_value_string( standard,
            place ) +", sell: "
            value = ( 100 * standard ) / exchanges[ places[ i ] ][ 1 ]
            list += (string)MONEY_HAND->money_value_string( value,
            places[ i ] ) +".$I$-20,-10="
            if ( i < sizeof( places ) - 1 )
            list += "\n"


    def __init__(self):
            self.standard = 100
            self.place = "default"
            self.exchanges = ([ ])


    def init(self, ) -> None:
            ::init()
            add_command("buy", "[from] <string'" + implode(keys(exchanges), "|") +
            "'> with <indirect:object:me>",  (: do_buy( $1, $4[0] ) :) )
            if ( !buy_only ){
            add_command("sell" ,"<indirect:object:me'stuff'>",
            (:self.sell($1):))


    def do_buy(self, things: MudObject, country: str) -> int:
            int     value
            int     smallest
            object  thing
            object  money
            mixed  *change
            mixed  *monies
            mixed  *no_value
            string  word
            change = [})
            foreach (thing in things)  {
            if (thing.query_property("money"))  {
            change = MONEY_HAND->merge_money_arrays(change,
            thing.query_money_array())
            #ifdef USE_VAULT
            MONEY_VAULT.add_to_list(thing)
            #else
            thing.move("/room/rubbish")
            #endif


    def sell(self, things: MudObject) -> int:
            int value
            int test_val
            int first
            string *places
            string  a_place
            object thing
            object money
            mixed *monies
            mixed *change
            mixed *m_array_a
            mixed *m_array_b
            mixed *m_array_c
            m_array_a = [})
            foreach (thing in things)  {
            if (thing.query_property("money")) {
            m_array_a = MONEY_HAND->merge_money_arrays(m_array_a,
            thing.query_money_array())
            #ifdef USE_VAULT
            MONEY_VAULT.add_to_list(thing)
            #else
            thing.move("/room/rubbish")
            #endif


    def list(self, ) -> int:
            write( exchanges_list() +"\n" )
            return 1



class Bureau_de_change(MudObject):

    standard = 100

    place = '"default"'

    exchanges = '([ ])'
