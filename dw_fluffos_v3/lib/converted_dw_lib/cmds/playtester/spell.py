# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/playtester/spell.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def finish_lookup(self, player: MudObject, word: str, result: int, results: Any) -> None:
            if (result == NETWORK_SUCCESS) {
            if (!sizeof(results)) {
            await player.send("Matches for " + word + ": None.\n")
            } else {
            tell_object(player, "Matches for " + word + ": " +
            query_multiple_short(map(results, (: $1[1] :))) +
            "\n")


    def cmd(self, word: str) -> int:
            NETWORK_DICTIONARY_HANDLER->spell_word(word, 0,
            (: finish_lookup($(this_player()), $1, $2, $3) :))
            write ("You look up a word.\n")
            return 1



class Spell(MudObject):
