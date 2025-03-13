# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/inherit/room_rental_office.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def set_domain(self, dom: str) -> None:
            _domain = dom


    def query_domain(self, ) -> str:
            return _domain


    def set_location(self, loc: str) -> None:
            _location = loc


    def query_location(self, ) -> str:
            return _location


    def __init__(self):


    def init(self, ) -> None:
            add_command( "list", "[rooms]" )
            add_command( "rent", "<string'room'>",
            (: do_rental( $4[0] ) :) )
            if ( this_player()->query_creator() ) {
            add_command( "add", "<string> for <number>",
            (: add_room( $4[0], $4[1] ) :) )
            add_command( "remove", "<string>", (: delete_room( $4[0] ) :) )


    def query_list(self, ) -> str:
            string room
            string list = ""
            string tenant
            object room_ob
            object office_ob = self
            tell_creator( "goldenthread", "getting list for %s ( %O )\n",
            office_ob.short(), office_ob )
            foreach( room in ROOM_RENTAL_HANDLER.query_rooms_to_rent( office_ob ) ) {
            tenant = ROOM_RENTAL_HANDLER.query_who_rents( room, office_ob )
            tell_creator( "goldenthread", "found %s\n", room )
            if ( room_ob = load_object( room ) ) {
            list += room_ob.query_short()
            if ( tenant != "nobody" )
            list += " (rented by " + tenant + ")\n"
            else
            list += " (available for " + MONEY_HAND->money_value_string(
            to_int( ROOM_RENTAL_HANDLER.query_rental_value( room ) ),
            _domain ) + ")\n"


    def do_list(self, ) -> int:
            string list = "Here are the rooms available to rent in " + _location
            + ":\n\n"
            this_player()->add_succeeded_mess( self, "$N ask$s for a list "
            "of available rooms.\n", [}) )
            list += query_list()
            await  this_player().send(list )
            return 1


    def add_room(self, room: str, cost: int) -> int:
            if ( ROOM_RENTAL_HANDLER.add_room( room, cost, self ) ) {
            this_player()->add_succeeded_mess( self,
            ["$N $V a room.\n", ""], [}) )
            return 1


    def delete_room(self, room: str) -> int:
            if( ROOM_RENTAL_HANDLER.delete_room( room, self ) ) {
            this_player()->add_succeeded_mess( self,
            ["$N $V a room.\n", ""], [}) )
            return 1


    def clear_rooms(self, ) -> int:
            if( ROOM_RENTAL_HANDLER.clear_rooms( self ) ) {
            this_player()->add_succeeded_mess( self,
            ["$N $V the list of rooms.\n", ""], [}) )
            return 1


    def do_rental(self, room: str) -> int:
            object ob = this_player()
            int ret = ROOM_RENTAL_HANDLER.do_rental( ob, room, self )
            switch( ret ) {
            case RENTAL_SUCCESS:
            ob->pay_money( MONEY_HAND->create_money_array(
            ROOM_RENTAL_HANDLER.query_rental_value( room ), query_domain() ),
            query_domain() )
            ob.add_succeeded_mess( self, ["$N $V a room.\n", ""],
            [}) )
            return 1
            case RENTAL_NO_SUCH_ROOM:
            ob->add_failed_mess( self, "There is no such room here.\n",
            [}) )
            return 0
            case RENTAL_ALREADY_RENTED:
            ob->add_failed_mess( self, "The room has already been rented.\n",
            [}) )
            return 0
            case RENTAL_NO_MONEY:
            ob->add_failed_mess( self, "You don't have enough money for "
            "that.\n", [}) )
            return 0
            default:
            ob->add_failed_mess( self, "Something has gone wrong.  Please "
            "contact a creator.\n", [}) )
            return 0


    def init_dynamic_arg(self, map: Any, ob: MudObject) -> None:
            _domain = map[ "domain" ]
            _location = map[ "location" ]



class Room_rental_office(MudObject):
