# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/gag.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, victim: MudObject, reason: str, number: int) -> int:
            victim.add_property( "gagged", reason, 60 * number )
            log_file( "GAG", ctime(time()) +": "+ this_player()->query_short()
            + " gagged " + victim.query_short() + " for " + number
            + " minutes.  Reason: " + reason +".\n")
            PLAYERINFO_HANDLER.add_entry( this_player(), victim.query_name(),
            "gag", "Gagged for " + number + " minutes.  Reason: '" + reason +
            "'.\n")
            tell_object( victim,
            "%^RED%^%^BOLD%^You have been gagged by " +
            this_player()->query_short() + " for the reason: '" + reason +
            "'.\nYou will not be able to shout, chat or use the newbie "
            "channel until the gag is removed.%^RESET%^\n" )
            write( "Okay, gagged " + victim.query_short() + " for " + number +
            " minutes.  Now please discuss your reason for gagging with "
            "them.  IMPORTANT! You should only be gagging for deliberately "
            "offensive language.\n" )
            event( users(), "inform", this_player()->query_short()
            + " gagged " + victim.query_short() + " for: " + reason, "gag")
            return 1



class Gag(MudObject):
