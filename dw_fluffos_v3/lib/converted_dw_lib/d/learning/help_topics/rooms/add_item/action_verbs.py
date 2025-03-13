# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/learning/help_topics/rooms/add_item/action_verbs.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short( "'add_item' room telling about making verbs do stuff" )
            set_light(100)
            set_long( "This is the room telling about making verbs do stuff.\n"
            "Let's say you have a rat in a room and randomly (let's say one "
            "out of two times) want to let players touch it.\n"
            "Read the ratnote to get an explanation of what happens when "
            "you touch the rat.\n"
            "There is a rat on the floor and a ratnote on the wall.\n")
            add_item( "large filthy rat", ({
            "long", "It looks like it wants to be touched.",
            "touch", [self, "do_touch"]] )
            add_item( "ratnote", ({
            "long", "It can be read.",
            "read", "When the rat is touched, do_touch() is called.  The do_touch() "
            "function must return an integer - If the touch was successful it "
            "returns a 1, if the touch failed the function should return a 0.\n"
            "Note also that a success message is given to all in the room.  But, "
            "if the person fails, the add_item code looks for more matches - "
            "thinking that the function do_touch is the wrong one.  If there is "
            "no other function found that defines touching rats and that returns "
            "a 1, then the game returns the message 'You fail to touch a rat'.\n"
            "The self reference tells the add_item code what object is "
            "the direct object of the verb.  Just trust me, and leave it in your "
            "code without asking why for now.  It is one of those things that "
            "can give you more flexibility later on.\n"] )
            add_exit( "east", PATH +"verb_failure", "path" )
            add_exit( "west", PATH +"many_verbs", "path" )
            add_exit( "start", MAIN, "path" )
            add_exit( "exit", LEARNING +"search", "path" )


    def do_touch(self, ) -> int:
            if( random(2) ) {
            tell_object( this_player(), "\n ****  You feel deathly sick. ****\n"
            " (this is a await this_player().send(...))\n" )
            tell_object( this_player(),
            "do_touch is returning a 0, indicating failure!\n" )
            return 0



class Action_verbs(Room):
