# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/liaison/NEWBIE/assassins.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short( "Assassins' gazebo" )
            set_light( 80 )
            add_property("no teleport", 1)
            set_long("This is a very comfortably furnished gazebo.  Obviously assassins "+
            "have excellent taste.  There is no sign at all of anything even "
            "remotely dangerous or threatening.  There is a large plaque on "
            "the wall explaining more about this rather enigmatic "
            "profession. You can view it by typing 'read sign'.\n"
            "A small, black, and elegant looking notice states that this is not "
            "where you actually join this class.\n" )
            set_zone( "Newbie" )
            add_item("notice", "A small, black, and elegant looking notice that "
            "states that this is not where you actually join the class.")
            add_item( ["furnishing"], "The room is furnished in an expensive, "
            "although tasteful manner.  On the walls are a variety of "
            "quality oil paintings and the floor is covered with a thick "
            "carpet.  Against one wall is a chaise longue and in a corner "
            "is a well stocked drinks cabinet.")
            add_item("carpet", "A well-made carpet, thick and luxurious.")
            add_item("painting", "A variety of landscapes from some of the Faerûn's "
            "more notable painters.")
            add_item(({"chaise longue", "chaise", "longue"}),
            "Upholstered in the softest leather "
            "it looks very comfortable.")
            add_item(({"drink", "cabinet"}), "Its most notable feature is that it "
            "is locked.  Behind the glass door you can see a variety of "+
            "bottles, crystal decanters and glasses.")
            add_sign("A plaque entitled 'Guild of Assassins'\n",
            "The class of assassins provides an excellent all-round "
            "education.  Graduates of the class (graduation is by "+
            "competitive examination) will be skilled in a wide variety of "
            "subjects and able to move in all social circles.\n"
            "All assassins automatically become player killers (see "
            "'help playerkilling') on graduation.  This is not "+
            "a class for the faint-hearted.  Becoming an assassin is a "
            "challenge.  Assassins are a proud class, neither giving nor"
            " asking for information on how to join.\n", 0, 0, "general")
            add_property("no godmother", 1)
            add_exit( "garden", PATH +"classs_foyer", "gate" )



class Assassins(MudObject):
