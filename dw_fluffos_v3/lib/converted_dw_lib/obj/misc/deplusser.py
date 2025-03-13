# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/deplusser.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short("deplusser")
            set_name("deplusser")
            set_long("It's shaped like a plus sign set in a circle, with a diagonal "
            "slash across it.  Type 'deplus <path>' to use.")
            set_weight(9)


    def init(self, ) -> None:
            add_command("deplus", "<string'file'>", (:self.deplus($4[0]):))


    def deplus(self, fname: str) -> int:
            string *files, *lines, last_line, this_line, next_line, old
            int i, j, sz
            seteuid(geteuid(this_player()))
            files = get_dir( this_player()->get_path( fname ) )
            if ( !sizeof(files) )
            return notify_fail( "No files found\n" )
            for (i = 0; i < sizeof(files); i++ )  {
            if ( file_size( this_player()->get_path( files[i] ) ) == -2 )  continue
            old = read_file( this_player()->get_path( files[i] ) )
            lines = explode( replace_string( old, "\t", "   " ), "\n" )
            if ( ( sz = sizeof( lines ) ) < 2 )  continue
            last_line = implode( explode( lines[0], " " ), "" )
            this_line = implode( explode( lines[1], " " ), "" )
            if ( sz > 2 )
            next_line = implode( explode( lines[2], " " ), "" )
            else next_line = ""
            for (j = 1, sz = sizeof(lines); j < sz - 1; j++ )  {
            if ( last_line[<2 .. <1] == "\"+"  &&
            strlen( this_line )  &&  this_line[0] == '\"' )
            lines[j-1] = lines[j-1][0 .. strsrch(lines[j-1], "+", -1) - 1]
            else if ( this_line[0 .. 1] == "+\""  &&
            strlen(last_line)  && last_line[<1] == '\"' )
            lines[j] = " " + delete( lines[j], strsrch(lines[j], "+"), 1 )
            last_line = this_line
            this_line = next_line
            if ( j < sz - 2 )
            next_line = implode( explode( lines[j+2], " " ), "" )



class Deplusser(MudObject):
