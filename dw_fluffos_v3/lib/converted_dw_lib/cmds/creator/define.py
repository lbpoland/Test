# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/define.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def finish_lookup(self, player: MudObject, word: str, result: int, results: Any) -> None:
            string ret
            string* bing
            if (result == NETWORK_SUCCESS) {
            if (!sizeof(results)) {
            await player.send("No definitions for " + word + ".\n")
            } else {
            ret = ""
            foreach (bing in results) {
            ret += bing[1] + "\n" + bing[2] + "\n\n"


    def cmd(self, word: str) -> int:
            NETWORK_DICTIONARY_HANDLER->define_word(word, 0,
            (: finish_lookup($(this_player()), $1, $2, $3) :))
            add_succeeded_mess("$N look$s up a word.\n")
            return 1



class Define(MudObject):
