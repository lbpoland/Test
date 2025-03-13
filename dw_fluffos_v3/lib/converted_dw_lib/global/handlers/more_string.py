# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/global/handlers/more_string.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def string_display_file(self, more_string_info: Any) -> None:
            int i
            string stuff
            info->botl = info->topl + ROWS
            stuff = ""
            for ( i = info->topl; ( i < info->botl ) && ( i < info->fsize ); i++ ) {
            stuff += info->the_bit[ i ] +"\n"


    def more_string_status_line(self, more_string_info: Any) -> None:
            string *frog
            string s
            int i
            int percentage
            if (!info->stat_line) {
            info->stat_line = "$N From $T to $B of $S ($%%) - h for help. "


    def string_next_page(self, str: str, more_string_info: Any) -> None:
            int num
            int noargs
            int i
            int redraw
            string s1
            if (!str) {
            str = ""


    def internal_more_string(self, ) -> int:
            string text, bity
            int noreline
            if ( sizeof( _pending_more ) ) {
            text = _pending_more[ 0 ][ 0 ]
            bity = _pending_more[ 0 ][ 1 ]
            noreline = _pending_more[ 0 ][ 2 ]
            _pending_more = _pending_more[ 1 .. <1 ]
            more_string( text, bity, noreline )



class More_string(MudObject):
