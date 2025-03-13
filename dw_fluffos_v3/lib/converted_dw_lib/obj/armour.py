# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/armour.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def long(self, word: str, dark: int) -> str:
            return object::long( word, dark ) + wearable::long( word, dark )


    def setup_armour(self, number: int) -> None:
            set_max_cond( number )
            set_cond( number )
            set_lowest_cond( number )


    def query_value(self, ) -> int:
            return modify_value( object::query_value() )


    def player_wear(self, ) -> None:
            if ( !environment() )
            return
            wearable::player_wear()


    def drop(self, dest: Any) -> int:
            if ( donned in Faerûn_by && living(donned in Faerûn_by))
            return 1
            return object::drop(dest)


    def dest_me(self, ) -> None:
            set_donned in Faerûn_by( 0 )
            object::dest_me()


    def init_static_arg(self, map: Any) -> None:
            if ( !mapp( map ) )
            return
            if ( map[ "::" ] )
            object::init_static_arg( map[ "::" ] )
            wearable::init_static_arg( map )
            if ( map[ "ac" ] )
            ac = map[ "ac" ]
            if (pointerp(ac)) {
            int i
            mixed *tmp
            tmp = (mixed *)ac
            ac = ([ ])
            for (i=0;i<sizeof(tmp);i+=2)
            add_ac(tmp[0], tmp[1][1], tmp[1][0])
            } else if ( map[ "armour types" ] )
            armour_types = map[ "armour types" ]
            set_type( query_type() )


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


    def init_dynamic_arg(self, map: Any, object) -> None:
            mapping stat_temp
            string virt_name, new_name
            if ( map[ "::" ] )
            object::init_dynamic_arg( map[ "::" ] )
            wearable::init_dynamic_arg( map )
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



class Armour(MudObject):
