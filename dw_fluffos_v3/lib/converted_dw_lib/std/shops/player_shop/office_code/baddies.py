# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/player_shop/office_code/baddies.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def do_ban(self, args: Any) -> int:
            {
            if (!test_player(lower_case(args[0])))
            {
            await this_player().send(args[0]+ " is not a player.\n")
            return 1


    def do_unban(self, person: str) -> int:
            {
            if (!query_baddie(person))
            {
            await this_player().send(person+ " is not currently banned.\n")
            return 1



class Baddies(MudObject):
