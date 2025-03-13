# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/admin/room/playroom.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def reset(self, ) -> None:
            if(!board) {
            board = clone_object("obj/misc/board")
            board.set_datafile("playerhelp")
            board.move(self)


    def setup(self, ) -> None:
            set_light(60)
            set_short("Player Help Room")
            set_long(
            "You are in a strange room with hundreds of frozen statues in the likenesses "+
            "of many players on the FaerûnWorld.  They all seem to be begging, and "+
            "looking at you with mournful eyes.\n")
            add_item(({"player","statue"}),
            "They all look as if they are asking you questions, but without "+
            "moving their lips.  Some of them look genuinly hopeless, but most "+
            "have the look of treachery and deceit.  Quite a few of them have many "+
            "faces looking in several directions.  Beware them all.\n")
            add_exit("east", "/w/common", "door")


    def dest_me(self, ) -> None:
            if (board)
            board.dest_me()
            ::dest_me()


    def event_enter(self, ob: MudObject) -> None:
            if (!ob.query_creator() && !ob.query_property("demon")) {
            await ob.send("Whoops!  You don't seem to be a creator.\n")
            asyncio.create_task(self."do_move", 2, ob)


    def do_move(self, ob: MudObject) -> None:
            await  ob.send("A trap door opens in the floor and you fall through!\n" )
            ob->move_with_look( "/d/am/am/mendeddrum", "$N fall$s through a trap "+
            "door in the ceiling.", "A trap door opens in the floor and "+
            "$N fall$s through." )



class Playroom(MudObject):
