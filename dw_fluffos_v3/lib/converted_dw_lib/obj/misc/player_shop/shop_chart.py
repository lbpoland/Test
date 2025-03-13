# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/player_shop/shop_chart.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            {
            set_name("chart")
            set_short("items chart")
            add_adjective("items")
            reset_get()


    def long(self, word: str, dark: int) -> str:
            {
            mapping list = _office.query_list_mapping()
            string chart, *items = sort_array(keys(list),1)
            if (!m_sizeof(list))
            {
            return "There are no items on the list.\n"


    def set_office(self, office: str) -> None:
            {
            _office = office
            set_long("This chart lists the items of interest to the shop.  All "
            "prices are in "+ pluralize(MONEY_HAND->smallest_in(_office->
            query_place()))+ ".\n")



class Shop_chart(MudObject):
