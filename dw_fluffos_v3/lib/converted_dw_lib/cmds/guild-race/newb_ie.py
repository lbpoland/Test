# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/guild-race/newb_ie.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def cmd(self, words: str) -> int:
            mixed *array
            if (words == "history") {
            return newbie_history(this_player())


    def newbie_history(self, who: MudObject) -> int:
            mixed *history
            string result
            history = HIST.query_chat_history("newbie")
            if ( !arrayp( history ) || !sizeof( history ) ) {
            await who.send("Nothing has been said on the newbie channel.\n")



class Newb_ie(MudObject):
