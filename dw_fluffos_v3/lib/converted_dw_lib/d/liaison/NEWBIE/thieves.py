# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/liaison/NEWBIE/thieves.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short( "Thieves' Gazebo" )
            set_light( 75 )
            add_property("no teleport", 1)
            set_long( "You carefully sneak into this small gazebo.  You're not "
            "really sure why, but you don't feel comfortable in here.  You "
            "hope to make it out, without anyone noticing you.  Sneaking a "
            "quick glance around here you see piles of stolen items from the "
            "citizens of Waterdeep.  There is a small sign cowering in "
            "a corner.  If you 'read sign' maybe you'll be able to find "
            "out a bit more about this dangerous profession.\n"
            "A small notice resembling the backside of a receipt states that "
            "this is not actually the place where you join the class.\n" )
            set_zone( "Newbie" )
            add_item( ["item"], "There "
            "are many items around the room, but their function is beyond "
            "you for the most part." )
            add_item( ["notice"],
            "This small notice looks like the backside of a receipt of some "
            "kind.\n" )
            add_sign( "This poor sign sits huddled in a dark corner of this "
            "foreboding room.\n", "This class specializes in stealing all "
            "they can from the citizens and player killers of Waterdeep.  They "
            "will teach you the fine art of thieving - how to steal from your "
            "friends and enemies.  Not only is this a dangerous profession, "
            "but it is also a great way to get some pocket change.  Picking "
            "pockets is just one of the things you will get to learn from "
            "this bunch of Authorized Income Redistributors.",
            0, 0, "general")
            add_property("no godmother", 1)
            add_exit( "garden", PATH +"classs_foyer", "gate" )



class Thieves(MudObject):
