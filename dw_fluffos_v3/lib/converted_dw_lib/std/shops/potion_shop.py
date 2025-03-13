# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/potion_shop.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def set_message_function(self, wossname: Any) -> None:
            _message_function = wossname


    def set_shopkeeper(self, name: str) -> None:
            _shopkeeper = name


    def query_shopkeeper(self, ) -> str:
            return _shopkeeper


    def shopkeeper_say(self, message: str) -> None:
            object *frog
            if( !message || message == "" )
            message = "Tuppence a bucket, well stamped down!"
            if( _shopkeeper ) {
            frog = match_objects_for_existence( _shopkeeper, self )
            if( sizeof( frog ) == 1 ) {
            frog[0]->init_command( "' "+ message )
            return


    def is_potion_or_salve(self, ob: MudObject) -> int:
            object thing, *contents
            int found_something
            string contents_string
            if( !ob.query_volume() ) {
            tell_creator( this_player(), "ob has 0 volume.\n" )
            if( _message_function )
            evaluate( _message_function,
            CONVERT( "There's nothing in "+ ob.the_short() +" that "
            "can be described as either potion or salve, "+
            this_player()->the_short() +".\n" ) )
            return 0
            } else if( ob.query_volume() < MIN_VOLUME ||
            ob.query_volume() < ( 7 * ob.query_max_volume() / 10 ) ) {
            tell_creator( this_player(), "ob does not contain enough stuff.\n" )
            if( _message_function )
            evaluate( _message_function,
            CONVERT( "We don't deal in quantities smaller than a cup, "+
            this_player()->the_short() +".\n" ) )
            return 0



class Potion_shop(MudObject):
