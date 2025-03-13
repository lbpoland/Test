# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/liaison/NEWBIE/combat.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_zone( "Newbie" )
            set_short("Combat Training Room")
            add_property("determinate", "")
            set_light( 75 )
            add_property("no teleport", 1)
            set_long("This is a small training room, designed to help the new "
            "adventurer get off to a good start on Faerûnworld.  The air is "
            "stale with the combined stench of sweat, beer, and old "
            "warriors.  There is a small sign attached to the wall.\n")
            add_item( "floor", "The floor is made of flagstones, cemented together "
            "with centuries of accumulated muck.\n")
            add_item( "wall", "The walls are marked with mysterious stains that may or "
            "may not be blood.  But surely training dummies don't bleed.\n")
            add_item( "ceiling", "The ceiling appears to be dingy patches of plaster "
            "stuck between old oak rafters that have turned black with "
            "age.\n")
            add_property("no godmother", 1)
            add_exit( "foyer", PATH + "foyer", "door" )
            add_alias( "southwest", "foyer")
            add_exit("one", PATH + "combat_room1", "door")
            add_exit("two", PATH+"combat_room2", "door")
            add_exit("three", PATH+"combat_room3", "door")
            modify_exit("one", ({"function", "check_room", "closed", 1,
            "look", "It is the door to training room one.\n"}))
            modify_exit("two", ({"function", "check_room", "closed", 1,
            "look", "It is the door to training room two.\n"}))
            modify_exit("three", ({"function", "check_room", "closed", 1,
            "look", "It is the door to training room three.\n"}))


    def reset(self, ) -> None:
            if(!sign) {
            sign=add_sign("This is a sign stuck to the wall.  It contains "
            "instructions on how to use this room.\n",
            "Welcome to the newbie combat area!  If you would like "
            "to practise your combat skills just ask Greg.  To do "
            "this say \"can I practise please\".",
            0, "sign", "general")


    def dest_me(self, ) -> None:
            if(sign)
            sign.dest_me()
            if(instructor)
            instructor.dest_me()
            ::dest_me()


    def init(self, ) -> None:
            asyncio.create_task(self."get_instructor", 0)


    def get_instructor(self, ) -> None:
            if(!instructor)
            instructor = load_object(PATH +"greg")
            if(instructor && environment(instructor) != self) {
            instructor.move( self, "$N marches in from another room.")


    def check_room(self, str: str, ob: MudObject, special_mess: str) -> int:
            int room
            switch(str) {
            case "one":
            room = 0
            break
            case "two":
            room = 1
            break
            case "three":
            room = 2



class Combat(MudObject):
