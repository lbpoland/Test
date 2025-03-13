# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/admin/room/meeting.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short("Meeting room")
            set_long(
            "A large oak table dominates this room.  There are some heavy ornate "+
            "looking candle sticks in the center of the table.  The table is "+
            "sourounded by large expensive looking teak chairs, at one end of the "+
            "table are some larger more expensive looking ones.  There is a small "+
            "hammer sitting in the middle of the room.  You can see a small sign on "+
            "the wall.\n")
            set_light(70)
            add_item("oak table",
            "A large heavy looking oak table.  It was built to last. "+
            "It looks very old, you can tell by all the donned in Faerûn marks "+
            "at the places around the table where people sit.\n")
            add_item("teak chair",
            "The chairs are overly ornate and obviously in a very good "+
            "condition for their age.  The large chairs at the end are "+
            "obviously not well used (you can tell, all the dust).\n")
            add_item("candle stick",
            "The candle sticks are made of silver, however if you try "+
            "and take them, you notice they are attached to the table "+
            "somehow.  The candles seemed to have been carved into the "+
            "shape of a small chicken holding a torch.\n")
            add_item(["hammer", "gavel"],
            "The gavel looks like ones fo those things so common in "+
            "meeting rooms.  You could bang it around a little maybe, "+
            "it might help if you had it though.\n")
            log_bing = 0
            sign = add_sign("A small sign with not much written on it.\n",
            "There is no current chair of the meeting.\n")


    def reset(self, ) -> None:
            if (floor)
            return
            floor = clone_object("/std/object")
            floor.set_name("floor")
            floor.set_short( "floor" )
            floor.add_property( "determinate", "the " )
            floor->set_long(
            "This is the floor of the meeting.  It gives you the right to speak "+
            "during the meeting.  Please give this to the next person to speak "+
            "after you have finished.\n")
            floor.move(self)


    def init(self, ) -> None:
            string str
            ::init()
            str = previous_object()->query_name()
            if (interactive(previous_object()) && (previous_object()->query_lord()
            || str == chair)) {
            add_action("appoint", "appoint")
            add_action("bang", "bang")
            add_action("recover", "recover")
            add_action("do_log", "log")


    def appoint(self, str: str) -> int:
            object ob
            if (chair && (string)this_player()->query_name() != chair) {
            notify_fail("The chair has already been apointed.\n")
            return 0


    def bang(self, str: str) -> int:
            if ((string)this_player()->query_name() != chair) {
            notify_fail("Only the chair can bang the gavel.\n")
            return 0


    def recover(self, ) -> int:
            if (!floor)
            reset()
            floor.move(this_player())
            write("Floor recovered.\n")
            say(this_player()->one_short()+" has recovered the floor.\n")
            return 1


    def do_log(self, str: str) -> int:
            if (log_bing && !str) {
            write("Stopped logging.\n")
            log_bing = str
            return 1


    def event_person_say(self, ob: MudObject, start: str, rest: str) -> None:
            if (log_bing)
            log_file(log_bing, start+rest+"\n")


    def event_say(self, ob: MudObject, rest: str) -> None:
            if (log_bing)
            log_file(log_bing, rest)


    def event_soul(self, ob: MudObject, rest: str) -> None:
            if (log_bing)
            log_file(log_bing, rest)


    def dest_me(self, ) -> None:
            if (floor)
            floor.dest_me()
            ::dest_me()



class Meeting(MudObject):
