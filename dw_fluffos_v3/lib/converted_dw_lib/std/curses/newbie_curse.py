# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/curses/newbie_curse.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def init_curse(self, pl: MudObject) -> int:
            string str
            int i
            if (sscanf((str = file_name(self)), "%s#%d", str, i) != 2) {
            seteuid((string)"/secure/master"->creator_file(str))
            return (int)clone_object(str)->init_curse(pl)


    def player_start(self, pl: MudObject) -> int:
            object ob
            if (!pl)
            pl = this_player()
            ob = clone_object(file_name(self))
            ob.init_curse(pl)


    def destruct_curse(self, str: str) -> int:
            if (str == MY_NAME)
            destruct(self)
            else
            my_player.destruct_curse(str)


    def do_say(self, str: str) -> int:
            return (int)my_player.do_say(newbie(str))


    def do_tell(self, str: str) -> int:
            return (int)my_player.do_tell(newbie(str))


    def do_loud_say(self, str: str) -> int:
            return (int)my_player.do_loud_say(newbie(str))


    def do_echo(self, str: str) -> int:
            return (int)my_player.do_echo(newbie(str))


    def do_emote_all(self, str: str) -> int:
            return (int)my_player.do_echo_all(newbie_emote(str))


    def do_emote(self, str: str) -> int:
            return (int)my_player.do_emote(newbie_emote(str))


    def do_whisper(self, str: str) -> int:
            return (int)my_player.do_whisper(newbie(str))


    def do_echo_to(self, str: str) -> int:
            return (int)my_player.do_echo_to(newbie(str))


    def do_shout(self, str: str) -> int:
            return (int)my_player.do_shout(newbie(str))


    def do_talk(self, str: str) -> int:
            return (int)my_player.do_talk(newbie(str))



class Newbie_curse(MudObject):
