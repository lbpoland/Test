# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/liaison/NEWBIE/common.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def dest_money(self, coins: MudObject) -> None:
            if(coins.query_number_coins() > 1)
            tell_room(self, "As the coins hit the ground they "
            "slip between the cracks and disappear.\n")
            else
            tell_room(self, "As the coin hits the ground it "
            "slips between the cracks and disappears.\n")
            coins.move("/room/rubbish")


    def event_enter(self, ob: MudObject, mess: str, from: MudObject) -> None:
            if(base_name(ob) == "/obj/money") {
            asyncio.create_task(self."dest_money", 0, ob)



class Common(MudObject):
