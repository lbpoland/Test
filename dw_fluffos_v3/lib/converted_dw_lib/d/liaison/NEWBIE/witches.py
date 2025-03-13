# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/liaison/NEWBIE/witches.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short( "Witches' Gazebo" )
            set_light( 75 )
            add_property("no teleport", 1)
            set_long( "As you wander in through the small gate to this little room, "
            "you are overwhelmed by an array of smells.  Of course, you "
            "can't identify any of these smells nor any of the items that "
            "are strewn about haphazardly.  The only thing you can identify "
            "is a nicely embroidered sign hanging on the wall.  Maybe if you "
            "'read sign' you'll learn a bit about the Witches' Guild.\n"
            "A small notice, which seems to have been used as a teabag, "
            "states that this is not actually the place where you join this "
            "class.\n" )
            set_zone( "Newbie" )
            add_item( ["item"], "There "
            "are several items of inexplicable function scattered around the "
            "room.  Some of these may be the source of the smells, but you "
            "wisely hesitate to test this possibility." )
            add_item( ["notice"],
            "This small, tea stained notice is casually leaned against a "
            "strange item." )
            add_sign( "The sign is beautifully embroidered and somehow makes the "
            "room brighter and darker at the same time.\n",
            FOYER->format_sign("This class "
            "is very unusual in that it only accepts those of the "
            "*female* persuasion.  It is "
            "a magical class, but not the magic of wizards and mages.  "
            "Witch magic is the magic of herbs, cursing, flying around, "
            "and most importantly, headology.\n\n"
            "The prominent witches of the Faerûnworld will be "
            "able to tell you more about headology.  Granny Weatherwax, "
            "whom you must see to join the class, will be particularly "
            "helpful.  So, if you think you have what it takes to learn "
            "how to know what is real, what is not, and how to tell the "
            "difference, then give the Witches' Guild a go!  Granny, "
            "Nanny Ogg, and Magrat Garlick will be there to greet you.  "
            "Oh, and if you need help getting there, just go see good old "
            "Gennie Applebottom in Waterdeep.  She'll help you out, as "
            "will almost any witch!  "
            "And don't forget, Witches prefer to use the back door "
            "to enter a house.\n"), 0, 0, "general")
            add_property("no godmother", 1)
            add_exit( "garden", PATH +"classs_foyer", "gate" )



class Witches(MudObject):
