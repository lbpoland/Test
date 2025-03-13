# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/quill.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "quill" )
            set_long( "This is a nice, long, feathery quill.  You could \"write\" "
            "on things with it.\n")
            set_weight( 3 )
            set_value( 1000 )
            new_weapon( 240 )
            add_help_file("quill")
            set_damage_chance( 100 )
            add_attack( "stab", 90, [10, 2, 10], "pierce", "sharp", 0 )
            add_property( "paper writer", 1 )
            type = "ink"


    def init(self, ) -> None:
            add_command( "write", "on <indirect:object> with <direct:object>" )
            add_command( "write", "with <direct:object> on <indirect:object>" )
            add_command( "sign", "<indirect:object> with <direct:object>")
            add_command( "scribble",
            "<string'message'> on <indirect:object> with <direct:object>",
            (: do_scribble($1, $4[0]) :))


    def do_scribble(self, things: MudObject, mess: str) -> int:
            string language
            if ( query_wielded() != this_player() ) {
            this_player()->add_failed_mess( self, "You need to be "+
            "holding $D to $V with it.\n", [}) )
            return 0


    def do_write(self, things: MudObject) -> int:
            string language
            if ( query_wielded() != this_player() ) {
            this_player()->add_failed_mess( self, "You need to be "+
            "holding $D to $V with it.\n", [}) )
            return 0


    def begin_writing(self, writer: MudObject) -> None:
            if ( !writer ) {
            writing_on = 0
            return


    def end_writing(self, words: str) -> None:
            string language
            if ( !words || ( words == "" ) ) {
            write( "You don't write anything on "+
            (string)writing_on.the_short() +".\n" )
            say( (string)this_player()->the_short() +" doesn't "+
            "write anything after all.\n" )
            writing_on = 0
            return


    def do_sign(self, things: Any) -> int:
            object ob
            string language
            if ( query_wielded() != this_player() ) {
            add_failed_mess( "You need to be "+
            "holding $D to $V with it.\n", [}) )
            return 0


    def do_copy(self, in_dir: Any, direct: str, indirect: str, args: Any) -> int:
            mixed src_mess, mess
            string lang, cur_lang
            int i, c, siz, perr
            if ( !present(direct, this_player()) ) return 0
            if ( query_wielded() != this_player() ) {
            this_player()->add_failed_mess( self, "You need to be "
            "holding $D to $V with it.\n", [}) )
            return 0



class Quill(MudObject):
