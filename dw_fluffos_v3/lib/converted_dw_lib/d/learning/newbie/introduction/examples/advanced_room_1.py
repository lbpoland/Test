# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/learning/newbie/introduction/examples/advanced_room_1.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short("market square")
            set_day_long("This is a lovely market square, where people mill about "
            "doing the kind of things you would expect people to do in a lovely "
            "market square.  Brightly coloured stalls stand in the corners of "
            "the market.  They seem to do good business judging by the steady "
            "stream of consumers ducking under the flaps.\n")
            set_night_long("The darkness settles on this market square like a thick "
            "black blanket.  The stalls, undoubtedly merry and brightly coloured "
            "during the day, lie dormant and unusued.  The silence is "
            "deafening.\n")
            add_property("climate",({20, 20, 10}))
            set_light(80)
            add_zone("my rooms")
            set_linker(({PATH + "advanced_room_2", PATH + "advanced_room_3"}),
            "onto", "on", "the newbie creator marketplace")
            add_day_item(({"people", "consumers"}), "The people mill around happily, "
            "browsing the goods and talking with the stallowners.")
            add_night_item(({"people", "consumers"}), "They're all tucked up in "
            "bed.  Only crazed retrobrates like you are awake at this time of "
            "night.")
            add_day_item("stall", "The stalls are brightly coloured and really "
            "quite merry.")
            add_night_item("stall", "The stalls lie dormant in the night.  Creepy!")
            room_day_chat(({120,240,({
            "People mill around happily.",
            "The brightly coloured stalls attract the eye.",
            })}))
            room_night_chat(({120,240,({
            "The only sound is the chirping of the crickets.",
            "The stalls loom ominously in the darkness.",
            })}))
            add_exit("north", PATH + "advanced_room_3", "road")
            add_exit("south", PATH + "advanced_room_2", "road")
            add_exit("east", "/w/drakkos/workroom", "road")
            add_exit("west", PATH + "simple_room", "road")
            modify_exit("east",({"look", "You get the feeling that peeking into a "
            "creator's workroom is very rude!", "function", "test_creator"}))


    def do_search(self, str: str) -> int:
            if(!sizeof(str)) {
            return -1


    def query_death_reason(self, ) -> str:
            return "a nasty cut in the newbie creator tutorial room"


    def test_creator(self, str: str, ob: MudObject, special_mess: str) -> int:
            if(!ob.query_creator()) {
            notify_fail ("")
            tell_object (ob, "You are not a creator!  You may not pass!\n")
            return 0



class Advanced_room_1(MudObject):
