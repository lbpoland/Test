# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/commercial/blackboard.c (2003 FluffOS v3) for Forgotten Realms MUD
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
            set_allowed_room_verbs( (["standing" : "stands",
            "hanging"  : "hangs"]) )
            set_commercial_size(1)
            set_weight(2000)
            set_value(240000)


    def init(self, ) -> None:
            add_command ("write", "[on] <direct:object'blackboard'> in <string'language'>",
            (: do_write($4[1]) :) )
            add_command ("clean", "<direct:object>")


    def query_readable_message(self, player: MudObject, ignore_labels: int) -> str:
            if (!sizeof(query_read_mess())) {
            return "A few random letters that escaped cleaning can be seen on "
            "the blackboard"


    def do_clean(self, ) -> int:
            if (!is_allowed (this_player()->query_name())) {
            this_player()->add_failed_mess (self, "You cannot clean "
            +  capitalize (query_owner()) + "'s blackboard!\n", [}))
            return 0


    def find_words(self, language: str) -> str:
            string words
            words = implode( map( filter( query_read_mess(),
            (: $1[READ_LANG] == $(language) :) ), (: $1[READ_MESS] :) ), "\n" )
            return words


    def do_write(self, language: str) -> int:
            {
            string existing_text
            if (!is_allowed (this_player()->query_name())) {
            this_player()->add_failed_mess (self, "You cannot write on "
            +  capitalize (query_owner()) + "'s blackboard!\n", [}))
            return 0


    def blackboard_text(self, text: str, language: str) -> None:
            {
            if (!text)
            {
            tell_room (environment (self), this_player()->one_short()
            + " steps back from the blackboard without making any "
            "changes.\n", this_player())
            tell_object (this_player(), "Okay, nothing has been changed.\n")
            return


    def init_dynamic_arg(self, map: Any) -> None:
            string my_words
            commercial::init_dynamic_arg(map, player)
            my_words = query_auto_load_value(map, BOARD_TAG, "words")
            if ( stringp(my_words) ) {
            add_read_mess(my_words, "chalk", DEFAULT_LANGUAGE)



class Blackboard(MudObject):
