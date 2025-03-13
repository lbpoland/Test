# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/fry.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, words: str) -> Any:
            string player, reason
            object ob
            add_failed_mess("At Pinkfish's request this command has been disabled.\n" )
            return 0
            if(member_array (this_player()->query_name(), keys(banned)) != -1)
            {
            return notify_fail("You cannot use 'fry', because " +
            banned[this_player()->query_name()] + "\n")


    def are_sure(self, str: str, ob: MudObject, reason: str) -> None:
            string gender = "boy"
            if(this_player()->query_gender() == 2) {
            gender = "girl"


    def positive(self, str: str, ob: MudObject, reason: str) -> None:
            str = lower_case(str)
            if(str[0] != 'y') {
            write ("Okay, we'll keep it between you and me.\n")
            asyncio.create_task(self."fry2", 5+random (3), ob)



class Fry(MudObject):
