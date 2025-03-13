# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/liaison/NEWBIE/fighters.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short( "Warriors' gazebo" )
            set_light( 75 )
            add_property("no teleport", 1)
            set_long( "As you enter this gazebo, you are overwhelmed with a smell of "
            "decaying limbs and dried blood.  A sign catches your eye and you "
            "notice it's the only non-blood covered item in the room.  Maybe "
            "if you 'read sign' you'll get some information about this "
            "deadly class.\n"
            "A small notice pinned to the wall with a sword states that this "
            "is not the place where you actually join the class.  The rest "
            "of the note is too torn to read.\n" )
            set_zone( "Newbie" )
            add_item( ["armour"],
            "There are many items around the room, but their function is "
            "beyond you for the most part." )
            add_item( ["notice"],
            "This notice was probably pinned to the wall during combat "
            "practice, and is therefore more or less unreadable after the "
            "battering it got during the session.\n" )
            add_sign( "This sign seems to cower in the corner of the room "
            "unsure of it's place here.\n", "In this deadly class, "
            "the fine art of killing and berserking is taught.  Learn how "
            "to be deadly with accuracy and lots of pain!  To be a warrior "
            "you must endure lots of pain, practice as much as you can, have "
            "a strong stomach, and have the ability to kill without batting "
            "an eye.  Remember to always keep your class motto with you: 'If "
            "It Moves Kill It.  If It Doesn't Move, Wait For It To Move, "
            "Then Kill It.'", 0, 0, "general" )
            add_property("no godmother", 1)
            add_exit( "garden", PATH +"classs_foyer", "gate" )



class Fighters(MudObject):
