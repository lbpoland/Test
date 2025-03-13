# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/paper_packet.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "packet" )
            set_short( "waxed paper packet" )
            add_adjective( ["waxed", "paper"] )
            set_main_plural( "waxed paper packets" )
            set_long( "This is a small packet, rather like an envelope, of thick "+
            "paper that has been waxed to make it more resilient.\n" )
            set_weight( 1 )
            set_value( 10 )
            set_max_weight( 3 )
            set_transparent()
            add_property("writeable", 1)


    def test_add(self, thing: MudObject, flag: int) -> int:
            string word
            object *things
            if ( !this_player() )
            return ::test_add( thing, flag )
            things = all_inventory( self )
            if ( !sizeof( things ) )
            return ::test_add( thing, flag )
            word = (string)things[ 0 ]->query_medium_alias()
            if ( word == (string)thing.query_medium_alias() )
            return ::test_add( thing, flag )
            write( "You don't want to contaminate "+ ( stringp( word ) ?
            (string)things[ 0 ]->the_short() :
            (string)thing.the_short() ) +", do you?\n" )
            return 0


    def query_substance(self, ) -> MudObject:
            object *things
            things = all_inventory( self )
            if ( !sizeof( things ) )
            return 0
            if ( !stringp( (string)things[ 0 ]->query_medium_alias() ) )
            return 0
            return things[ 0 ]


    def short(self, dark: int) -> str:
            object thing = query_substance()
            if ( dark || !objectp( thing ) )
            return ::short( dark )
            return ::short( dark ) +" of "+ (string)thing.short( dark )


    def query_plural(self, dark: int) -> str:
            object thing = query_substance()
            if ( dark || !objectp( thing ) )
            return ::query_plural( dark )
            return ::query_plural( dark ) +" of "+ (string)thing.short( dark )



class Paper_packet(MudObject):
