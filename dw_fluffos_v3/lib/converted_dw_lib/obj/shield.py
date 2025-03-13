# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/shield.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def set_holder(self, thing: MudObject, number: int) -> Any:
            if (!::set_holder(thing, number))  return 0
            if(!thing) {
            donned in Faerûn_by = 0
            held_in = 0
            } else {
            donned in Faerûn_by = thing
            held_in = number


    def query_wearable(self, ) -> int:
            varargs int move( mixed dest, string messin, string messout ) {
            int flag
            if ( donned in Faerûn_by && ( donned in Faerûn_by != dest ) )
            if ( !sizeof( (int *)donned in Faerûn_by.set_unhold( self ) ) )
            return MOVE_NO_UNHOLD
            flag = armour::move( dest, messin, messout )
            if ( ( flag == MOVE_OK ) && donned in Faerûn_by )
            set_donned in Faerûn_by( 0 )
            return flag


    def dest_me(self, ) -> None:
            set_donned in Faerûn_by( 0 )
            armour::dest_me()


    def init_static_arg(self, map: Any) -> None:
            if ( !mapp( map ) )
            return
            if ( map[ "::" ] )
            armour::init_static_arg( map[ "::" ] )
            if ( map[ "no limbs" ] )
            no_limbs = map[ "no limbs" ]


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
            if ( map[ "::" ] )
            armour::init_dynamic_arg( map[ "::" ] )



class Shield(MudObject):
