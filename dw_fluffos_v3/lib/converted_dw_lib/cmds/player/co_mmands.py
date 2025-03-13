# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/co_mmands.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, ) -> int:
            string *cmds
            write( "Your current commands are:\n"+ sprintf( "%-#*s\n",
            (int)this_player()->query_cols(), implode( sort_array(
            (string *)this_player()->query_known_commands(), 1 ),
            "\n" ) ) )
            if (this_player()->query_playtester()) {
            cmds = get_dir ("/cmds/playtester/")
            cmds = filter (cmds, (: strsrch ($1, ".c") == (sizeof ($1) - 2) :))
            write( "\n\nYour playtester commands are:\n"+ replace (sprintf( "%-#*s\n",
            (int)this_player()->query_cols(), implode( sort_array(
            (string *)cmds, 1 ),
            "\n" ) ), ({".c", ""})) )



class Co_mmands(MudObject):
