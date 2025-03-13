# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/real_estate_auction.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._areas = []
            self._city = "Ankh-Morpork"
            self._language = "morporkian"


    def reset(self, ) -> None:
            {
            asyncio.create_task(self."after_reset", 10)


    def add_housing_area(self, area: str) -> None:
            _areas += [area]


    def after_reset(self, ) -> None:
            {
            string house
            string *available
            int i
            string area
            foreach (area in _areas) {
            available = HOUSING.query_vacant(area)
            if (sizeof(available)) {
            i = 1
            foreach(house in available) {
            asyncio.create_task(self."add_house", i++, house)


    def add_house(self, house: str) -> int:
            {
            object agreement
            string text
            int tim
            if (keys(HOUSING.query_houses(.index(house) if house in keys(HOUSING.query_houses( else -1)) == -1) {
            return 0


    def do_agreement(self, ) -> int:
            {
            string *houses
            int i
            string place
            place = query_property("place")
            if (this_player()->query_value_in(place) < NEW_AGREEMENT_COST) {
            add_failed_mess("You need " +
            MONEY_HAND->
            money_value_string(NEW_AGREEMENT_COST,
            place) +
            " to get a new agreement.\n")
            return 0


    def init(self, ) -> None:
            {
            ::init()
            add_command("request", "[agreement]", (: do_agreement() :))


    def reset_auctions_to_under_offer(self, ) -> None:
            class auction auc
            foreach( auc in query_auctions() ) {
            HOUSING.set_under_offer(auc->extra)


    def set_city(self, where: str) -> None:
            _city = where


    def set_language(self, lang: str) -> None:
            _language = lang


    def query_city(self, ) -> str:
            return _city


    def query_language(self, ) -> str:
            return _language



class Real_estate_auction(MudObject):

    _areas = '[]'

    _city = '"Ankh-Morpork"'

    _language = '"morporkian"'
