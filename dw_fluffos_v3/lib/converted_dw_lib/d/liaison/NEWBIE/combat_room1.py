# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/liaison/NEWBIE/combat_room1.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short("Xrazzicaz' Boot Camp")
            add_property("determinate", "")
            set_light( 75 )
            add_property("no teleport", 1)
            set_long("This is a small training room, designed to help the new "
            "adventurer get off to a good start on Faerûnworld.  The air is "
            "stale with the combined stench of sweat, beer, and old "
            "warriors.  Off to one side is a rather unusual training "
            "dummy above which is a small plaque.\n")
            add_item( "face", "As you stare at it, squinting and turning your head "
            "side to side, you realise it looks rather like your old maths "
            "teacher!\n")
            add_item( "floor", "The floor is made of flagstones, cemented together "
            "with centuries of accumulated muck.\n")
            add_item( "wall", "The walls are marked with mysterious stains that may or "
            "may not be blood.  But surely training dummies don't bleed.\n")
            add_item( "ceiling", "The ceiling appears to be dingy patches of plaster "
            "stuck between old oak rafters that have turned black with "
            "age.\n")
            add_property("no godmother", 1)
            add_exit( "combat", PATH + "combat", "door" )
            add_alias( "southeast", "foyer")


    def reset(self, ) -> None:
            if(!sign) {
            sign=add_sign("This is a plaque that seems to describe how to have "
            "your combat skills assessed.\n", "To assess your "
            "skills, attack the dummy with the weapon you want to "
            "test your proficiency in.  Each time you hit the "
            "dummy, the instructor will comment on your "
            "performance.  After a number of rounds, the "
            "instructor will stop you and give you an overall "
            "performance rating.\n\n"
            "Don't forget to hold your weapon of choice before "
            "attacking the training dummy!\n",
            "small plaque", "plaque", "general")
            sign.add_property("there", "on the wall")


    def dest_me(self, ) -> None:
            if(sign)
            sign.dest_me()
            if(dummy)
            dummy.dest_me()
            if(trainer)
            trainer.dest_me()
            ::dest_me()


    def get_trainer(self, ) -> None:
            if(!trainer)
            trainer = clone_object(PATH +"trainer")
            if (trainer) {
            trainer.whichone("xrazzicaz")
            trainer.move( self, "$N hobble$s toward you on his straw-filled stumps." )
            dummy.set_trainer(trainer)


    def stop_them(self, who: MudObject) -> None:
            if(trainer && dummy)
            trainer.stop_them(who, dummy)


    def query_quit_handler(self, ) -> str:
            return "/d/liaison/NEWBIE/combat"



class Combat_room1(MudObject):
