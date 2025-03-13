# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/boring_stick.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("stick")
            set_state(0)
            set_weight(2)
            set_value(10)


    def init(self, ) -> None:
            this_player()->add_command("turn", self,
            "<direct:object> {on|off}")
            this_player()->add_command("flick", self,
            "switch on <direct:object>")
            this_player()->add_command("press", self,
            "switch on <direct:object>")
            this_player()->add_command("push", self,
            "switch on <direct:object>")
            this_player()->add_command("flick", self,
            "<direct:object>")
            this_player()->add_command("turn", self,
            "switch {on|off} on <direct:object>")
            this_player()->add_command("switch", self,
            "<direct:object> {on|off}")


    def set_state(self, new_state: int) -> None:
            state = new_state
            if (state) {
            set_long(
            "The long straight black stick vibrates slightly in your hands, you "
            "get a nice massage from it.  There is something which looks a bit "
            "like a switch down near the base of the stick.  Flashing lights "
            "rush up and down the side of the stick in a mad progression.\n")
            } else {
            set_long(
            "The long straight black stick vibrates slightly in your hands, you "
            "get a nice massage from it.  There is something which looks a bit "
            "like a switch down near the base of the stick.\n")


    def extra_look(self, ) -> str:
            return capitalize(previous_object()->query_pronoun())+
            " is surrounded by an aura of bees.\n"


    def do_flick(self, ) -> int:
            set_state(!state)
            this_player()->add_succeeded_mess(self,
            "$N $V the switch on $D to the "+(state?"on":"off")+" position.\n", [}))
            return 1


    def do_press(self, ) -> int:
            return do_flick()


    def do_push(self, ) -> int:
            return do_flick()


    def init_dynamic_arg(self, map: Any) -> None:
            set_state(map["state"])
            if ( map[ "::" ] )
            held::init_dynamic_arg( map[ "::" ] )



class Boring_stick(MudObject):
