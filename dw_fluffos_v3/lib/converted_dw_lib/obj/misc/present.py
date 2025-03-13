# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/present.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "wrappingpaper" )
            set_short( "piece of wrapping paper" )
            add_alias( "paper" )
            add_adjective( ["piece of", "wrapping"] )
            set_main_plural( "pieces of wrapping paper" )
            add_plural( ["pieces of wrapping paper", "pieces of paper",
            "papers"] )
            set_long( PAPER_LONG )
            set_weight( 2 )
            set_max_weight( 225 )
            set_value( 600 )
            set_stuck(1)
            add_property( "writeable", 1 )
            add_property( "paper", 1)


    def set_colour(self, word: str) -> None:
            if( _colour ) {
            return


    def set_type(self, word: str) -> None:
            if( _type ) {
            return


    def test_remove(self, thing: MudObject, flag: int) -> int:
            if( ( query_verb() == "get" ) || ( query_verb() == "take" ) ) {
            return !wrapped


    def test_add(self, thing: MudObject, flag: int) -> int:
            if( ( query_verb() == "put" ) || ( query_verb() == "give" ) ) {
            return 0


    def init(self, ) -> None:
            add_command( "wrap", "<indirect:object:me> in <direct:object'present'>" )
            add_command( "unwrap", "<direct:object:'present'>", (: do_unwrap :) )
            add_command( "open", "<direct:object:'present'>", (: do_unwrap :) )


    def do_wrap(self, things: MudObject) -> int:
            object *valid, *failed
            things -= [self]
            if( wrapped ) {
            add_failed_mess( "The paper has already been used to wrap something.\n" )
            return 0


    def do_unwrap(self, ) -> int:
            int i
            object *things
            if( !wrapped ) {
            write( "There is nothing wrapped in the paper.\n" )
            return 0


    def init_static_arg(self, args: Any) -> None:
            _colour = args[ "colour" ]
            ::init_static_arg( args[ "::" ] )


    def init_dynamic_arg(self, args: Any) -> None:
            _colour = args[ "colour"  ]
            _type   = args[ "type"    ]
            wrapped = args[ "wrapped" ]
            ::init_dynamic_arg( args[ "::" ] )
            if(!_colour) {
            _colour = "plain"


    def query_closed(self, ) -> int:
            return 1


    def long_status(self, ) -> str:
            return ""



class Present(MudObject):
