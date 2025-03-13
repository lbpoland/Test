# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/global/alias.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def add_player_alias(self, name: str, value: Any) -> int:
            if (file_name(previous_object()) != ALIAS_CMD &&
            file_name(previous_object()) != EDIT_ALIAS_CMD) {
            return 0


    def remove_player_alias(self, name: str) -> int:
            if ((file_name(previous_object()) != UNALIAS_CMD) &&
            name != "" &&
            !this_player(1)->query_lord()) {
            printf("%O\n", file_name(previous_object()))
            return 0


    def alias_commands(self, ) -> None:
            add_command("END_ALIAS", "<string>", (:remove_alias_thing($4[0]):))


    def remove_all_aliases(self, ) -> int:
            if (!this_player(1)->query_lord()) {
            write("You can't do that :)\n")
            return 0


    def is_alias(self, verb: str) -> int:
            return aliases[verb] != 0


    def remove_alias_thing(self, verb: str) -> int:
            in_alias_command--
            map_delete(doing_alias, verb)
            this_player()->adjust_time_left(-DEFAULT_TIME)
            return 1



class Alias(MudObject):
