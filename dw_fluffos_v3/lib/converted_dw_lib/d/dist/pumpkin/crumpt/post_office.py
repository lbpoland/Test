# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/dist/pumpkin/crumpt/post_office.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            add_help_file("mail_room")
            set_short("Post Office")
            set_light(70)
            set_long(
            "Black and orange colours seem to dominate the room, you can see a counter "
            "or something in amongst all the clashing colours.\n")
            add_item("counter", ["long",
            "There are some envelopes and bits of paper strewn "
            "about on the counter.",
            "position", "the counter"])
            add_exit("southeast", CRUMPT + "crumpt2", "door")
            add_exit("north", CRUMPT + "parcel_post", "corridor")
            add_property("place", "Pumpkin")


    def reset(self, ) -> None:
            if ( !_dictionary ) {
            _dictionary = clone_object( "/net/obj/dict" )
            _dictionary.add_property( "there", "attached to the counter" )
            _dictionary.reset_get()
            _dictionary.move( self )


    def init(self, ) -> None:
            ::init()
            add_command("mail", "<string>", (: do_mail($4[0]) :))
            add_command("mail", "", (: do_mail(0) :))


    def do_mail(self, words: str) -> int:
            return (int)MAIL_TRACK.mail( words )


    def send_message(self, from: str, parcel: int) -> int:
            #if 0
            object thing
            thing = clone_object( CHARS +"post_et" )
            thing.set_home( file_name( self ) )
            thing.move( self, "$N pop$s out of the counter and grab$s the mail." )
            if ( find_player( recipient ) ) {
            thing.goto_player( recipient, from )
            } else {
            thing.goto_dest( COMM_ROOM, from )



class Post_office(MudObject):
