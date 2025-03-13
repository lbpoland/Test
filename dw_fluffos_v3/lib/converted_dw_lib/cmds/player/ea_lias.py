# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/ea_lias.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.editing_alias = ([ ])


    def finish_alias_edit(self, str: str) -> None:
            string alias
            if (!editing_alias[this_player()]) {
            write("Oh dear.  We got terribly confused and forgot "
            "what you were trying to do.  Terribly sorry.\n")
            return


    def clean_up(self, ) -> int:
            if (sizeof(editing_alias) == 0)
            ::clean_up()
            return 1


    def reset(self, ) -> None:
            if (sizeof(editing_alias) == 0)
            ::reset()
            return



class Ea_lias(MudObject):

    editing_alias = '([ ])'
