# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/rem_ote.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, obs: MudObject, words: str) -> Any:
            object other
            object *ok
            object *ignoring
            object *roleplaying
            object *net_dead
            object *fail
            object *earmuffed
            object *multiple_earmuffed
            object *update_list
            string* prop
            string me_name
            string tmp
            string pad = " "
            string* ok_string
            int colour
            if ( this_player()->query_role_playing() ) {
            add_failed_mess( "You cannot use remotes when you are role playing.\n" )
            return -1



class Rem_ote(MudObject):
