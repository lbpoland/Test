# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/player_shop/shop_notice.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            {
            set_name("notice")
            set_short("policy notice")
            set_long("")
            add_adjective("policy")
            reset_get()


    def long(self, word: str, dark: int) -> str:
            {
            mapping policies= _office.get_policies(_type)
            int i = 1
            string display
            if (!_type)
            {
            display = sprintf("This is the list of shop's policies.  The policies "
            "on this notice are definitive and final.  This shop deals strictly "
            "in %s.  Items that do not fit this description should not be "
            "stocked.\n\n", "%^BOLD%^"+ _stock_policy+ "%^RESET%^")


    def set_office(self, office: str) -> None:
            {
            _office = office
            _stock_policy = _office.get_stock_policy()



class Shop_notice(MudObject):
