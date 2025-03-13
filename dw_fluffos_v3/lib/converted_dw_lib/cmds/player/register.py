# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/register.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, alt: str) -> int:
            string p1
            string p2
            alt = lower_case(alt)
            if (!PLAYER_HANDLER.test_user(alt))
            return notify_fail(alt + " is not a player.\n")
            p1 = PLAYERINFO_HANDLER.query_alt_of(this_player()->query_name())
            if(!p1 || p1 == "") {
            p1 = this_player()->query_name()


    def get_pw(self, pass: str, player: MudObject, alt: str) -> None:
            if (!PLAYER_HANDLER.test_password(player->query_name(), pass)) {
            write("Sorry, incorrect password.\n")
            return


    def get_alt_pw(self, pass: str, player: MudObject, alt: str) -> None:
            string result
            string p1, p2
            write("\n")
            if(this_player() != player) {
            write("Something has gone wrong, player objects don't match.\n")
            return


    def cmd_list(self, ) -> int:
            string* alts
            string p1
            p1 = PLAYERINFO_HANDLER.query_alt_of(this_player()->query_name())
            if (!p1) {
            p1 = this_player()->query_name()



class Register(MudObject):
