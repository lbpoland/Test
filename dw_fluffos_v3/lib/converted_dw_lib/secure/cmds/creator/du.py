# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/cmds/creator/du.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, path: str) -> int:
            if ( !path )
            return 0
            _counts[this_player()] = 0
            if ( master()->valid_read( path, geteuid( this_player() ) ) ) {
            printf( "%-30s %5d\n", "Total:", rec_du( path ) )
            if(_counts[this_player()] >= MAX_FILES)
            printf("Note: count truncated due to file limit\n")
            return 1



class Du(MudObject):
