# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/global/more_string.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def __init__(self):
            private void string_display_file(class more_string_info info) {
            int i
            string stuff
            info->botl = info->topl + ROWS
            stuff = ""
            for ( i = info->topl; ( i < info->botl ) && ( i < info->fsize ); i++ ) {
            stuff += info->the_bit[ i ] +"\n"



class More_string(MudObject):
