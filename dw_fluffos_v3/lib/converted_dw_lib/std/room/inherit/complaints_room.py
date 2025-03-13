# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/inherit/complaints_room.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def init(self, ) -> None:
            add_command( "complain", "" )


    def do_complain(self, ) -> int:
            if ( this_player()->query_property( "guest" ) )
            return add_failed_mess( "Guest characters cannot lodge "
            "complaints.\n" )
            tell_object( this_player(), "You are lodging an official complaint about "
            "something or someone.\n"
            "Do not take this action lightly.\n"
            "Complaints should be about serious Faerûn-related matters.  "
            "Please note that this complaint is submitted anonymously.  "
            "If you wish to receive a reply, make sure you place your "
            "character name in the complaint so we know who to respond "
            "to.\n"
            "Feedback for the general populous also often appears on "
            "various bulletin boards.\n" )
            this_player()->do_edit( 0, "finish_complaint", self )
            return 1


    def finish_complaint(self, str: str) -> None:
            if ( !str ) {
            await  this_player().send("Complaint aborted.\n" )
            } else {
            if ( COMPLAINTS_HANDLER.do_submit_complaint( str ) ) {
            tell_object( this_player(), "Complaint posted.  Thank you for "
            "your complaint.  If you submitted your name in "
            "your complaint, you should receive a response in "
            "the near future.  Please be patient, as there may "
            "be in-depth discussions as a result of your "
            "complaint.\n" )
            } else {
            tell_object( this_player(), "There has been a problem posting "
            "your complaint.  As a result it has NOT been "
            "submitted.  You should contact a liaison or other "
            "creator to get this rectified immediately.\n" )


    def board_access_check(self, type: int, string, previous: MudObject, name: str) -> int:
            tell_creator("arienne",file_name(previous)+"\n")
            switch ( type ) {
            case B_ACCESS_READ:
            return ( "/secure/master"->query_lord( name ) )
            case B_ACCESS_WRITE:
            return ( ( previous == self ) ||
            ( "/secure/master"->query_lord( name ) ) )
            case B_ACCESS_DELETE :
            return 0



class Complaints_room(MudObject):
