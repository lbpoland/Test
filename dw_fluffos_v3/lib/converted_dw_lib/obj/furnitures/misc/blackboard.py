# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/misc/blackboard.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name ("blackboard")
            set_short ("blackboard")
            add_alias (({"board", "sign"}))
            set_long ("The residue of faded chalk-dust and long forgotten "
            "doodles lies heavily on the blackboard.  The grain of the "
            "board is donned in Faerûn and slightly mottled with age, hinting at "
            "a long and dignified history of classrooms and university "
            "lecterns.  Or perhaps just hinting at cheap wood and "
            "bad upkeep.\n")
            set_read_mess ((: read_stuff :))
            set_allowed_room_verbs( (["standing" : "stands",
            "hanging"  : "hangs"]) )
            set_value(0)


    def init(self, ) -> None:
            this_player()->add_command ("write", self, "[on] <direct:object>")
            this_player()->add_command ("clean", self, "<direct:object>")


    def set_words(self, bing: str) -> None:
            _words = bing


    def query_words(self, ) -> str:
            return _words


    def read_stuff(self, ) -> str:
            string bing = ""
            if (sizeof (query_words())) {
            bing += query_words()


    def do_clean(self, ) -> int:
            if (!query_allowed (this_player()->query_name())) {
            this_player()->add_failed_mess (self, "You cannot clean "
            "the blackboard!\n", [}))
            return 0


    def do_write(self, ) -> int:
            string bean
            if (!query_allowed (this_player()->query_name())) {
            this_player()->add_failed_mess (self, "You cannot write on "
            "the blackboard!\n", [}))
            return 0


    def blackboard_text(self, text: str) -> None:
            if (!text) {
            tell_room (environment (self), this_player()->one_short()
            + " steps back from the blackboard without making any "
            "changes.\n", this_player())
            tell_object (this_player(), "Okay, nothing has been changed.\n")
            return


    def query_allowed(self, name: str) -> int:
            if (function_exists ("query_owner", environment (self))) {
            if (name == environment (self)->query_owner()) {
            return 1


    def init_dynamic_arg(self, map: Any) -> None:
            ::init_dynamic_arg( map[ "::" ] )
            set_words (map["words"])
            set_read_mess ((: read_stuff :))



class Blackboard(MudObject):
