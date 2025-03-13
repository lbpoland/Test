# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/learning/common.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_light( 100 )
            set_short( "somewhat boring commonroom of the learning domain" )
            add_property( "determinate", "the " )
            set_long( "This is the common room of the domain of learning, the place "
            "where creators come to learn.  It is a somewhat boring room "
            "except for some chairs strewn around the place which happen to "
            "be an example of having commands defined in add_items, and some "
            "sort of list hanging on the wall which is an example of using "
            "add_command in rooms.\n" )
            add_item( "chair", ({
            "long", "This chair looks comfortable, perhaps you can sit in it.",
            "sit", [(: do_sit :), "[in] <direct:object>"]
            }), 1 )
            add_item( "chairs", ({
            "long", "These chairs look comfortable, "
            "perhaps you can sit in one of them.",
            "sit", [(: do_sit :),  "[in] <direct:object>"]
            }), 1 )
            add_item( "list",
            "This list has several actions associated with it:\n"
            "\"show list\" will show the current requests.\n"
            "\"request documentation\" will ask for "
            "documentation on something.\n"
            "\"request example\" will ask for an example of "
            "something to be coded.\n"
            "\"claim <number>\" is use to claim a request, thereby attempting "
            "to make sure that only one creator is writing the documentation/"
            "coding the examples." )
            add_exit( "entrance", PATH +"main", "path" )
            add_exit( "drum", CONFIG_START_LOCATION, "path" )
            chairs = [})
            add_extra_look( self )
            add_property( "commented functions", ["add_extra_look", "extra_look",
            "remove_extra_look", "add_command"] )
            add_property( "keywords", ["room", "add_item", "action"] )
            board = clone_object( "/obj/misc/board" )
            board.set_datafile( DOMAIN )
            board.move( self )


    def init(self, ) -> None:
            ::init()
            add_command( "show", "list" )
            add_command( "claim", "<number>", (:do_claim( $4[0] ):) )
            add_command( "request", "{documentation|example} <string'subject'>",
            (:do_request( $4[0], $4[1] ):))
            add_command( "remove", "<number>", (:do_remove( $4[0] ):) )


    def do_show(self, ) -> int:
            write( HANDLER.query_list() )
            return 1


    def do_claim(self, i: int) -> int:
            if ( HANDLER.claim_request( this_player()->query_name(), i ) ) {
            add_succeeded_mess("$N $V a request.\n", ({}))
            } else {
            return notify_fail( "Illegal request number.\n" )


    def do_remove(self, i: int) -> int:
            if ( HANDLER.remove_request( this_player()->query_name(), i ) ) {
            add_succeeded_mess("$N $V a request.\n", ({}))
            } else {
            return notify_fail( "You can't remove that request.\n" )


    def do_request(self, option: str, words: str) -> int:
            if ( option == "documentation" ){
            HANDLER.add_request( this_player()->query_name(),
            "documentation for "+ words )
            write( "You request some documentation.\n")
            say( this_player()->the_short() +" requests some documentation.\n")
            return 1


    def extra_look(self, thing: MudObject) -> str:
            if ( thing == self ) {
            chairs = filter_array( chairs, (: $1 != 0 :) )
            chairs = filter_array( chairs,
            (: environment( $1 ) == self :) )
            if ( !sizeof( chairs ) ) {
            return ""
            } else {
            if ( sizeof( chairs ) == 1 ) {
            if ( chairs[ 0 ] == this_player() ) {
            return "You are sitting in one of the chairs.\n"
            } else {
            return (string)chairs[ 0 ]->the_short()
            +" is sitting in one of the chairs.\n"



class Common(MudObject):
