# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/learning/help_topics/rooms/situations/sitroom1.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            add_property( "commented functions",
            [] )
            add_property( "keywords",
            ["situation"] )
            set_short("Basic situation example room")
            set_light(100)
            set_long("This is a very simple situation example.  "
            "To start it \"press\" the button.  "
            "Please more here to see how it is done.\n"
            "%^CYAN%^Functions shown:%^RESET%^\n"
            "%^YELLOW%^add_situation,  change_situation.%^RESET%^\n")
            add_exit( "next", SIT+"sitroom2", "path" )
            add_exit( "back", LEARNING +"search", "path" )
            add_exit( "exit", ENTRANCE, "path" )
            add_item( "button", "There is a button on the wall you might \"press\".")
            add_situation( "frog",
            new(class situation,
            start_mess: "A little frog appears from nowhere.\n",
            extra_look: "There is a little frog here.",
            add_items: [["frog", "The frog is small but happy."]],
            chat_rate: [10, 30],
            chats: ({"The little frog hops on the spot.",
            "The little frog says:  Ribbit."] ,
            end_mess: "The little frog disappears into thin air."
            )
            )


    def do_press(self, ) -> int:
            {
            await this_player().send("You press the button.\n")
            tell_object(this_player(),"%^YELLOW%^You just started the frog situation.  "
            "It will go for 60 seconds.  It adds an add_item ( look frog ), "
            "an extra_look to the room ( look ) and some chats.%^RESET%^\n")
            change_situation( "frog", 60 )
            return 1


    def init(self, ) -> None:
            {
            this_player()->add_command( "press", self, "button" )
            ::init()



class Sitroom1(Room):
