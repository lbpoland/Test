# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/liaison/NEWBIE/align.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            object sign
            set_zone("Newbie")
            set_short("alignment room" )
            set_light( 75 )
            add_property("no teleport", 1)
            set_long( "This is a small, bare room that is quite empty apart from "
            "a lever stuck onto each of three walls and a small wooden "
            "sign placed in the centre of the room.\n"
            "A door to the east leads back to the foyer.\n")
            add_item(({"west wall", "south wall", "east wall"}),
            "A plain, flat wall with a lever sticking out of it.")
            sign=add_sign("A sign marked 'alignment'.\n",
            FOYER->format_sign(
            "Alignment is how good or evil you are.  This changes gradually "
            "depending on the things you do.  Because it changes so slowly "
            "you can choose to start out with a good, neutral or evil "
            "alignment.  To become evil, pull the black lever, to become "
            "good pull the white lever, and to stay neutral don't pull "
            "either lever, or pull the grey lever if you have already pulled "
            "one of the other ones.\n"),0,"sign","general")
            sign.set_short("sign")
            sign.add_adjective("wooden")
            add_property("no godmother", 1)
            add_exit( "foyer", PATH + "foyer", "door")
            add_alias( "east", "foyer")
            room_chat(({10, 40, ({"A voice which seems to come from the black lever "
            "says: Don't be a goody-goody, pull me!",
            "A voice which seems to come from the white lever "
            "says: You should be nice, pull me!",
            "A voice which seems to come from the grey lever "
            "says: It's all about balance in the end."})}))


    def init(self, ) -> None:
            if (_wlever) {
            this_player()->add_command("pull", _wlever, "<direct:object>",
            (: do_pull(_wlever) :))


    def reset(self, ) -> None:
            if(!_wlever) {
            _wlever = clone_object("/std/object")
            _wlever.set_name("lever")
            _wlever.add_adjective("white")
            _wlever.set_short("white lever")
            _wlever->set_long("This is a lever which is set into the wall.  It "
            "radiates a soft white glow.  The closer you stand "
            "to it the more peaceful you feel.\n")
            _wlever.reset_get()
            _wlever.add_property("there", "on the east wall")
            _wlever.move(self)


    def do_pull(self, lever: MudObject) -> int:
            int align
            if(lever == _glever) {
            add_succeeded_mess(["$N $V $I and feel an overwhelming urge to do "
            "absolutely nothing about the world's problems.\n",
            "$N $V $I and suddenly looks very apathetic.\n"],
            [_glever])
            this_player()->set_al(0)
            return 1



class Align(MudObject):
