# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/inherit/meeting.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._floor = create_floor()


    def init(self, ) -> None:
            add_command("bang", "gavel", (: do_bang() :))
            add_command("recover", "floor", (: do_recover() :))
            add_command("start", "meeting", (: do_start() :))
            add_command("finish", "meeting", (: do_finish() :))


    def create_floor(self, ) -> MudObject:
            object floor
            floor = clone_object("/std/object")
            floor.set_name("floor")
            floor.set_short( "floor" )
            floor.add_property( "determinate", "the " )
            floor.add_property( "no burial", 1)
            floor->set_long("This is the floor of the meeting.  It gives you the "
            "right to speak during the meeting.  Please give this "
            "to the next person to speak after you have finished.\n")
            return floor


    def do_start(self, ) -> int:
            if (_leader &&
            find_player(_leader) &&
            environment(find_player(_leader)) == self) {
            add_failed_mess("There is already a meeting started with " +
            find_player(_leader)->the_short() +
            " as the leader.\n")
            return 0


    def do_bang(self, ) -> int:
            if (this_player()->query_name() != _leader) {
            add_failed_mess("Only the leader can bang the gavel!\n")
            return 0


    def do_recover(self, ) -> int:
            if (this_player()->query_name() != _leader) {
            add_failed_mess("Only the leader can recover the floor.\n")
            return 0


    def do_finish(self, ) -> int:
            if (this_player()->query_name() != _leader) {
            add_failed_mess("Only the leader can stop the meeting!\n")
            return 0


    def event_dest_me(self, ob: MudObject) -> None:
            object *inv
            if (living(ob)) {
            if (userp(ob) &&
            ob.query_name() == _leader) {
            tell_room(self,
            "The meeting finishes abruptly as the leader leaves.\n")


    def event_quit(self, ob: MudObject) -> None:
            object *inv
            if (living(ob)) {
            if (userp(ob) &&
            ob.query_name() == _leader) {
            tell_room(self,
            "The meeting finishes abruptly as the leader leaves.\n")



class Meeting(MudObject):

    _floor = 'create_floor()'
