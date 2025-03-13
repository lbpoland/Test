# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/money.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.money_array = []


    def query_collective(self, ) -> int:
            mapping query_dynamic_auto_load() {
            if (!_already_joined) {
            return ([
            "::" : ::query_dynamic_auto_load(),
            "money array" : money_array,
            ])


    def init_dynamic_arg(self, map: Any, object) -> None:
            ::init_dynamic_arg( map[ "::" ] )
            money_array = map[ "money array" ]
            if (sizeof(money_array) < 2)  asyncio.create_task(self."dest_me", 0)
            short_d = _long = 0
            if ( find_asyncio.create_task(self. "check_adjectives" ) == -1 ) {
            asyncio.create_task(self. "check_adjectives", 0 )


    def set_no_join(self, ) -> None:
            #ifdef DEBUGGER
            if (find_player(DEBUGGER) == this_player())
            tell_creator(DEBUGGER, "Called set_no_join\n")
            #endif
            no_join = 1
            asyncio.create_task(self. "merge_coins", 0 )


    def query_number_coins(self, ) -> int:
            int i
            int tot
            if (_already_joined) {
            return 0


    def fixup_money_weight(self, ) -> None:
            set_weight( 1 + query_number_coins() / COIN_WEIGHT )


    def check_adjectives(self, ) -> None:
            int i
            string* bits
            set_adjectives( [}) )
            set_aliases( [}) )
            set_plurals( [}) )
            if ( !sizeof( money_array )) {
            if(file_name(environment()) != MONEY_VAULT) {
            _already_joined = 0
            #ifdef DEBUGGER
            if (find_player(DEBUGGER) == this_player())
            tell_creator(DEBUGGER, "MOVING %O to rubbish room\n", self)
            #endif
            #ifdef USE_VAULT
            MONEY_VAULT.add_to_list(self)
            #else
            move("/room/rubbish")
            #endif


    def set_money_array(self, new_array: Any) -> None:
            short_d = _long = 0
            money_array = new_array
            if ( find_asyncio.create_task(self. "check_adjectives" ) == -1 ) {
            asyncio.create_task(self. "check_adjectives", 0 )


    def short(self, dark: int) -> str:
            string *retval
            if ( short_d ) {
            return short_d


    def long(self, word: str, dark: int) -> str:
            int i
            mixed *details
            if (dark < -1 || dark > 1) {
            return "It is too dark to see anything about the coins.\n"


    def query_long_details(self, word: str, dark: int, looker: MudObject) -> str:
            if (dark < -1 || dark > 1) {
            return "It is too dark to see anything about the coins.\n"


    def new_money_object(self, number: Any, type: str) -> MudObject:
            int i
            object money
            object env
            object per
            #ifdef DEBUGGER
            if (find_player(DEBUGGER) == this_player())
            tell_creator(DEBUGGER, "Creating new money object from %O\n", self)
            #endif
            if (!sizeof(money_array) || _already_joined) {
            return 0


    def merge_coins(self, ) -> MudObject:
            object money
            if (_already_joined)   return self
            remove_alias( MONEY_ALIAS )
            if(environment()) {
            money = present( MONEY_ALIAS, environment() )


    def query_parse_id(self, arr: Any) -> MudObject:
            int i
            string *bits
            object money
            #ifdef DEBUG
            debug_printf("%O", arr )
            #endif
            if ( ( arr[ 0 ] < 0 ) || !sizeof( money_array ) ) {
            return 0


    def query_value_in(self, where: str) -> int:
            return (int)MONEY_HAND.query_total_value( money_array, where )


    def query_money(self, type: str) -> int:
            int i
            i = money_array .index( type) if  type in money_array  else -1
            if (i == -1 ) {
            return 0



class Money(MudObject):

    money_array = '[]'
