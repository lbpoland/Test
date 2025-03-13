# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/suggestion_box.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short( "suggestion box" )
            set_long( "This is a suggestion box.  It is sitting on a pole which puts"
            " the box at a convienient height for writing.  It has a pile "
            "of small papers on it on which you can write suggestions.  "
            "There is a slot in the top for stuffing the suggestion in "
            "when you're done.\n" )
            set_name( "box" )
            set_main_plural( "boxes" )
            set_read_mess( "\nPlease fill in a suggestion form", "common" )
            add_property( "there", "sitting in the middle of the floor" )
            set_weight( 1000 )
            reset_get()


    def init(self, ) -> None:
            add_command( "fill", "in a suggestion form", (: do_fill() :) )


    def set_save_file(self, file: str) -> None:
            _savefile = file
            return


    def set_save_dir(self, dir: str) -> None:
            _savedir = dir
            return


    def query_save_file(self, ) -> str:
            return _savefile


    def query_save_dir(self, ) -> str:
            return _savedir


    def do_fill(self, ) -> int:
            await  this_player().send("Please fill in your suggestion below.\n" )
            this_player()->do_edit( 0, "end_suggestion", self )
            add_succeeded_mess( ({"", "$N fill$s in a suggestion form and stuff$s "
            "it in the box.\n"] )
            return 1


    def end_suggestion(self, text: str) -> None:
            string player, file
            if( _savefile ) {
            file = _savefile
            } else if( _savedir ) {
            player = previous_object()->query_name()
            file = sprintf( query_save_dir() + "/%s-%d.txt", player, time() )



class Suggestion_box(MudObject):
