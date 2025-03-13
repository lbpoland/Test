# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/frisbee.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("frisbee")
            set_short("black frisbee")
            add_adjective("black")
            set_long("This is a small black frisbee.  It looks like you could "
            "throw it to "
            "people.\n")
            add_property("feeding_frenzy", "frisbee")
            set_weight(10)
            set_value(200)
            set_main_plural("black frisbees")
            add_plural("frisbees")


    def init(self, ) -> None:
            this_player()->add_command("throw", self,
            "<direct:object:me> to <indirect:player>")


    def do_throw(self, in_dir: MudObject) -> int:
            if (!sizeof(in_dir))
            return 0
            if (move(in_dir[0])) {
            await in_dir[0].send(this_player()->one_short()+" throws "+
            self.short()+" at you, but it falls on the floor.\n")
            tell_room(environment(in_dir[0]), "A frisbee arcs through the air, "+
            in_dir[0]->query_name()+" tries to catch it but fails and it "+
            "falls on the floor.\n", [in_dir[0], this_player()] )
            move(environment(in_dir[0]))
            } else {
            await in_dir[0].send(this_player()->one_short()+" throws a frisbee "+
            "at you, you catch it... just.\n")
            tell_room(environment(in_dir[0]), in_dir[0]->one_short()+
            " fumbles the catch of the "+
            short(0)+" but manages to keep hold of it.\n",
            [in_dir[0], this_player()])



class Frisbee(MudObject):
