# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/liaison/NEWBIE/wizards.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short( "Wizards' Gazebo" )
            set_light( 75 )
            add_property("no teleport", 1)
            set_long( "As you enter this gazebo, it is obvious that it is the room "
            "of a mage.  Strewn around are pointy hats, wands and other "
            "items of wizardly paraphernalia.  A small sign catches your "
            "eye.  Maybe if you 'read sign' you'll find something out "
            "about this magical class.\n"
            "A small notice that, for some reason, is extremely fat, wearing "
            "a pointy hat and winking at you, states that this is not the "
            "place where you actually join the class.\n" )
            set_zone( "Newbies" )
            add_item( ["pointy hat", "wand", "item", "paraphernalia"],
            "There are many items around the room, but their function is "
            "beyond you for the most part." )
            add_item( "notice",
            "This notice is extremely fat, wears a pointy hat and winks at "
            "you -- that's magic for you." )
            add_sign( "The sign is floating, apparently unsupported, in the "
            "centre of the room.\n", "In this magical class, based at "
            "Unseen University in Waterdeep, you can learn many "
            "wonderful and exciting spells.  Learn how to tickle an "
            "enemy with a feather, create cabbage pets for your friends "
            "and hold your own against muggers using a carrot "
            "and a torch, or even a human eye!  The Library at the Unseen "
            "University (U.U.) is extensive, with many books in which to "
            "search for that special spell.  You'll learn all this and more "
            "if you decide to follow the Higher Art.", 0, 0, "general" )
            add_property("no godmother", 1)
            add_exit( "garden", PATH +"classs_foyer", "gate" )



class Wizards(MudObject):
