# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/go_to.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> Any:
            object dest
            string *names, nick
            string tname
            if (!str)
            return notify_fail("Teleport where?\n")
            nick = (string)this_player()->expand_nickname(str)
            dest = find_living(nick)
            if (!dest && objectp(this_player()->get_obvar(str))) {
            dest = this_player()->get_obvar(str)
            if (dest == environment(this_player()))
            return notify_fail("You look around and realise you are already there.\n")
            this_player()->set_last_location(base_name(environment(this_player())))
            this_player()->move_with_look( dest,
            (string)this_player()->query_mmsgin(),
            (string)this_player()->query_mmsgout() )
            return 1


    def dest_me(self, ) -> None:
            destruct(self)


    def clean_up(self, ) -> None:
            dest_me()


    def reset(self, ) -> None:
            dest_me()



class Go_to(MudObject):
