# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/curses/chef_curse.c (2003 FluffOS v3) for Forgotten Realms MUD
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
            if (name != MY_NAME)
            return (int)my_player.query_remove(name)
            return 1


    def player_start(self, pl: MudObject) -> int:
            object ob
            if (!pl)
            pl = this_player()
            ob = clone_object(HERE+"chef_curse")
            ob.init_curse(pl)


    def destruct_curse(self, str: str) -> int:
            if (str == MY_NAME)
            destruct(self)
            else
            my_player.destruct_curse(str)


    def do_emote_all(self, str: str) -> int:
            return (int)my_player.do_emote_all((HERE+"chef_mangle")->do_transmute(str))


    def do_shout(self, str: str) -> int:
            return (int)my_player.do_shout((HERE+"chef_mangle")->do_transmute(str))


    def do_say(self, str: str) -> int:
            return (int)my_player.do_say((HERE+"chef_mangle")->do_transmute(str))


    def do_loud_say(self, str: str) -> int:
            return (int)my_player.do_loud_say((HERE+"chef_mangle")->do_transmute(str))


    def do_emote(self, str: str) -> int:
            return (int)my_player.do_emote((HERE+"chef_mangle")->do_transmute(str))


    def do_tell(self, str: str) -> int:
            string s1
            if (sscanf(str, "%s %s", s1, str) != 2)
            return (int)my_player.do_tell(str)
            return (int)my_player.do_tell(s1+" "+(HERE+"chef_mangle")->do_transmute(str))



class Chef_curse(MudObject):
