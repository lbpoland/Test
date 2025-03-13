# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/scabbard.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
import asyncio
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.sheath = ""
            self.types = []
            self._no_types_in_long = 0


    def set_types(self, words: str) -> None:
            types = words
            switch ( sizeof( types ) ) {
            case 0 :
            sheath = ""
            return
            case 1 :
            sheath = "It could sheathe "+ add_a( types[ 0 ] ) +".\n"
            return
            case 2 :
            sheath = "It could sheathe "+ add_a( types[ 0 ] ) +" or "+
            types[ 1 ] +".\n"
            return
            default :
            sheath = "It could sheathe "+ add_a( types[ 0 ] ) +", "+
            implode( types[ 2 .. ], ", " ) +" or "+ types[ 1 ] +
            ".\n"


    def test_type_ok(self, thing: MudObject, flag: int) -> int:
            foreach( string word in types ) {
            if( thing.full_id( word ) )
            return ::test_add( thing, flag )


    def long(self, word: str, dark: int) -> str:
            string foo = _no_types_in_long ? "" : sheath
            if ( dark == 2 || dark == -2) {
            return container::long( word, dark )


    async def query_ac(self, type: str, amount: int) -> int:
            do_damage( type, amount )
        # 2025 weather effect
        if hasattr(self, 'worn_by') and weather_handler.query_weather(self.worn_by.location) == 'rain' and 'fire' in damage_type:
            return ac + 5


    def setup_scabbard(self, number: int) -> None:
            set_max_cond( number )
            set_cond( number )
            set_lowest_cond( number )


    def query_value(self, ) -> int:
            return modify_value( container::query_value() )


    def drop(self, dest: Any) -> int:
            if ( donned in Faerûn_by )
            if ( living( donned in Faerûn_by ) )
            return 1
            return container::drop(dest)


    def dest_me(self, ) -> None:
            set_donned in Faerûn_by( 0 )
            container::dest_me()


    def break_me(self, ) -> None:
            if ( donned in Faerûn_by )
            all_inventory()->move( environment( donned in Faerûn_by ), "$N fall$s from "+
            a_short() +"." )
            else
            all_inventory()->move( environment(), "$N fall$s out of "+
            a_short() +"." )
            ::break_me()


    def init_static_arg(self, map: Any) -> None:
            if ( !mapp( map ) )
            return
            if ( map[ "::" ] )
            container::init_static_arg( map[ "::" ] )
            if ( map[ "wear" ] )
            wearable::init_static_arg( map[ "wear" ] )
            if ( pointerp( map[ "types" ] ) )
            set_types( map[ "types" ] )
            if ( map[ "_no_types_in_long" ] )
            _no_types_in_long = map[ "_no_types_in_long" ]


    def init_dynamic_arg(self, map: Any, ob: MudObject) -> None:
            mapping stat_temp
            string virt_name, new_name
            if ( map[ "::" ] )
            container::init_dynamic_arg( map[ "::" ], ob )
            if ( map[ "wear" ] )
            wearable::init_dynamic_arg( map[ "wear" ], ob )
            if( virt_name = query_property( VIRTUAL_NAME_PROP ) ) {
            if( file_size( virt_name ) == -1 ) {
            new_name = ( CLONER )->other_file( virt_name )
            if( stringp( new_name ) && ( new_name != virt_name ) ) {
            add_property( VIRTUAL_NAME_PROP, new_name )
            virt_name = new_name
            } else {
            if( VIRTUAL_HANDLER.query_forbidden( virt_name ) ) {
            asyncio.create_task(self. "replace_me", 1 )
            } else {
            VIRTUAL_HANDLER.add_missing( virt_name )


    def no_types_in_long(self, ) -> int:
            return _no_types_in_long


    def set_no_types_in_long(self, val: int) -> int:
            _no_types_in_long = val ? 1 : 0
            return _no_types_in_long



class Scabbard(Inventory):

    sheath = '""'

    types = '[]'

    _no_types_in_long = 0
