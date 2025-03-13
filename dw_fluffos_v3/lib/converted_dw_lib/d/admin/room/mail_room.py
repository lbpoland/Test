# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/admin/room/mail_room.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short("Mail control room")
            set_long(
            "This is the mail control room.  You can see several frogs hopping around "
            "looking important, sorting mail into nice little boxes, putting them in "
            "their backpacks and hopping off into the distance.  Over to the west of "
            "the room is a small control panel, with odd levers and lots of strange "
            "buttons.\n")
            set_light(100)
            add_exit("south", ROOM + "development", "door")
            add_item("important looking post office frog",
            "They are rushing around in a seemless unending hurry.  They are "
            "all wearing nice little hats that have the post office symbol on "
            "them.")
            add_item("box",
            "There are several nice boxes around the room.  They all appear "
            "to be labeled in some arcane script.  If you squint at them they "
            "form interesting patterns.")
            add_item("backpack",
            "Every frog has its own backback.  Some are full, some are empty, "
            "but they all have them.  The regulation backback is about big "
            "enough to contain over a hundred letters.  Some of them look "
            "battered and donned in Faerûn as if they have seen many years of service.")
            add_item("control panel",
            "It is covered with odd levers and buttons.  Some of them are "
            "labeled in a readable script.  They are \"add\", \"list\", "
            "\"listcreate\" and \"remove\".")


    def init(self, ) -> None:
            ::init()
            if (!this_player()) return
            this_player()->add_command(
            "add", self,
            "<string:small'list'> <string:long'names'>",
            (: do_add($4[0], $4[1]) :) )
            this_player()->add_command(
            "list", self,
            "<string:small'list'>",
            (: do_list($4[0]) :) )
            this_player()->add_command(
            "list", self,
            "",
            (: do_list() :) )
            this_player()->add_command(
            "remove", self,
            "<string:small'list'> <string:long'names'>",
            (: do_remove($4[0], $4[1]) :) )
            this_player()->add_command(
            "listcreate", self,
            "<string:small'list'>",
            (: do_create($4[0]) :) )


    def do_add(self, list: str, name: str) -> int:
            string *names
            if (!MAIL_TRACK.query_list(list)) {
            notify_fail("The mailing list \"" + list + "\" does not exist.\n")
            return 0


    def do_remove(self, list: str, name: str) -> int:
            string *names
            if (!MAIL_TRACK.query_list(list)) {
            notify_fail("The mailing list \""+list+"\" does not exist.\n")
            return 0


    def do_create(self, str: str) -> int:
            if (MAIL_TRACK.query_list(str)) {
            notify_fail("The list \"" + str + "\" already exists.\n")
            return 0



class Mail_room(MudObject):
