# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/qwho.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, guild_name: str) -> int:
            int i
            int countcre
            int countplay
            int counttest
            int countloginq
            int countlogins
            int compressed
            string obtyp
            string tmp
            object *arr
            string nam
            string cres
            string plays
            string testers
            string *login_q
            string logins
            int showmasters
            mapping user_data
            object *liaisons
            string friends
            int countFriends
            int totalUsers
            int totalPlayers
            int totalCompressed
            if (this_player()->query_creator()) {
            showmasters = 1
            } else {
            showmasters = 0


    def playercompare(self, p1: MudObject, p2: MudObject) -> int:
            return strcmp(p1.query_name(), p2.query_name())



class Qwho(MudObject):
