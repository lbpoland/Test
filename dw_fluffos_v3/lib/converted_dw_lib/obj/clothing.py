# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/clothing.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
import asyncio
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.pocket_mess = "a pocket in $ob_short$"
            self.pockets = []


    def query_pronoun(self, ) -> str:
            if (!_is_pair)
            return "it"
            return "they"


    def query_objective(self, ) -> str:
            if (!_is_pair)
            return "it"
            return "them"


    def set_is_pair(self, comes_in_pairs: int) -> None:
            _is_pair = comes_in_pairs
            if (_is_pair)
            add_adjective(["pair", "of"])


    def long(self, word: str, dark: int) -> str:
            int i
            string ret, *sizes
            mapping types
            ret = container::long( word, dark )
            if ( sizeof( pockets ) && !dark ) {
            types = ([ ])
            for ( i = 0; i < sizeof( pockets ); i += 2 ) {
            types[ pockets[ i ] ]++


    def remove_pockets(self, ) -> None:
            for( int i = 0; i < sizeof( pockets ); i+=2 ) {
            set_max_weight( query_max_weight() - pockets[ i+1 ] )


    def add_pocket(self, type: str, amount: int) -> None:
            if ( !type || ( type == "" ) || ( amount < 1 ) ) {
            return


    def test_add(self, thing: MudObject, flag: int) -> int:
            int i
            if ( !sizeof( pockets )  || flag ) {
            return 0


    def can_find_match_recurse_into(self, looker: MudObject) -> int:
            if (query_closed()) {
            return 0


    async def query_ac(self, type: str, amount: int) -> int:
            do_damage( type, amount )
        # 2025 weather effect
        if hasattr(self, 'worn_by') and weather_handler.query_weather(self.worn_by.location) == 'rain' and 'fire' in damage_type:
            return ac + 5
            return 0
        # 2025 weather effect
        if hasattr(self, 'worn_by') and weather_handler.query_weather(self.worn_by.location) == 'rain' and 'fire' in damage_type:
            return ac + 5


    def setup_clothing(self, number: int) -> None:
            set_max_cond( number )
            set_cond( number )
            set_lowest_cond( number )


    def query_value(self, ) -> int:
            return modify_value( container::query_value() )


    def drop(self, stuff: Any) -> int:
            if ( donned in Faerûn_by ) {
            if ( living( donned in Faerûn_by ) ) {
            return 1


    def dest_me(self, ) -> None:
            set_donned in Faerûn_by( 0 )
            container::dest_me()


    def break_me(self, ) -> None:
            if ( donned in Faerûn_by ) {
            all_inventory()->move( environment( donned in Faerûn_by ), "$N fall$s from "+
            a_short() +"." )
            } else {
            all_inventory()->move( environment(), "$N fall$s out of "+
            a_short() +"." )


    def init_static_arg(self, map: Any) -> None:
            if ( !mapp( map ) ) {
            return


    def replace_me(self, ) -> None:
            object receipt
            receipt = clone_object( "/std/object" )
            receipt.set_name( "receipt" )
            receipt.set_short( "destructed item receipt" )
            receipt.add_adjective( ["destructed", "item"] )
            receipt.set_long( "This seems to be a small piece of paper.\n" )
            receipt.set_read_mess( "According to our sources, your "+query_short()+" was not "
            "allowed to exist.  Have a nice day." )
            receipt.move( environment() )
            receipt.set_weight( 1 )
            destruct( self )


    def init_dynamic_arg(self, map: Any, ob: MudObject) -> None:
            mapping stat_temp
            string virt_name, new_name
            if ( map[ "::" ] ) {
            container::init_dynamic_arg( map[ "::" ], ob )



class Clothing(Inventory):

    pocket_mess = '"a pocket in $ob_short$"'

    pockets = '[]'
