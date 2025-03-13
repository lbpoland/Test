# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/curses/shout_curse.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def init_curse(self, pl: MudObject) -> int:
            string str, i
            if (sscanf((str = file_name(self)), "%s#%d", str, i) != 2) {
            seteuid((string)"/secure/master"->creator_file(str))
            return (int)clone_object(str)->init_curse(pl)


    def query_remove(self, name: str) -> int:
            return 1


    def player_start(self, pl: MudObject) -> int:
            object ob
            if (!pl)
            pl = this_player()
            ob = clone_object(HERE+"shout_curse")
            ob.init_curse(pl)


    def destruct_curse(self, str: str) -> int:
            if (str == MY_NAME)
            destruct(self)
            else
            my_player.destruct_curse(str)


    def do_emote_all(self, str: str) -> int:
            write("Your voice is too hoarse to shout.\n")
            return 1


    def do_shout(self, str: str) -> int:
            write("Your voice is too hoarse to shout.\n")
            return 1



class Shout_curse(MudObject):
