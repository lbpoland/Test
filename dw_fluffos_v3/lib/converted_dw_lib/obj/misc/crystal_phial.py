# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/crystal_phial.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "phial" )
            set_short( "crystal phial" )
            add_adjective( "crystal" )
            set_main_plural( "crystal phials" )
            set_long( "This is a small tube-like bottle made of some sort of "+
            "crystal.  A stopper is attached at one end on a bit of wire.\n" )
            set_weight( 1 )
            set_value( 1000 )
            set_max_weight( 1 )
            set_max_volume( 10 )
            set_transparent()


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



class Crystal_phial(MudObject):
