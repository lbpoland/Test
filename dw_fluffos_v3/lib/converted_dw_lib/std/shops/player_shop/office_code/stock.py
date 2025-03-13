# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/player_shop/office_code/stock.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def adjust_bought(self, item: str, amt: int) -> None:
            {
            if (previous_object() && previous_object() != find_object(_storeroom))
            {
            LOG_ERROR("office.c", "adjust_bought("+item+","+amt+")")
            return


    def adjust_sold(self, item: str, amt: int) -> None:
            {
            if (previous_object() && previous_object() != find_object(_storeroom))
            {
            LOG_ERROR("office.c", "adjust_sold("+item+","+amt+")")
            return


    def query_ave(self, item: str) -> int:
            {
            return (!_list[item])?0:copy(_list[item][CHART_AVE])


    def query_buy(self, item: str) -> int:
            {
            return (!_list[item])?0:copy(_list[item][CHART_BUY])


    def query_max(self, item: str) -> int:
            {
            return (!_list[item])?0:copy(_list[item][CHART_MAX])


    def query_sell(self, item: str) -> int:
            {
            return (!_list[item])?0:copy(_list[item][CHART_SELL])



class Stock(MudObject):
