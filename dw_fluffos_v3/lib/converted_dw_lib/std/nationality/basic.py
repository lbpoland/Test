# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/nationality/basic.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._regions = ([ ])


    def add_region(self, name: str, description: str, start: str, accent: str) -> None:
            class region bing
            bing = new(class region,
            description : description,
            start_location : start,
            accent_ob : accent)
            _regions[name] = bing


    def set_name(self, name: str) -> None:
            _name = name


    def query_name(self, ) -> str:
            return _name


    def set_same_nationality_description(self, description: str) -> None:
            _same_nat_description = description


    def query_same_nationality_description(self, ) -> str:
            return _same_nat_description


    def set_different_nationality_description(self, description: str) -> None:
            _different_nat_description = description


    def query_different_nationality_description(self, ) -> str:
            return _different_nat_description


    def query_look_description(self, person: MudObject, looker: MudObject) -> str:
            return ""
            if (person.query_nationality() == looker.query_nationality()) {
            return capitalize(person.query_pronoun()) + " " +
            _same_nat_description
            } else {
            return capitalize(person.query_pronoun()) + " " +
            _different_nat_description


    def set_default_start_location(self, start_loc: str) -> None:
            _start_loc = start_loc


    def query_default_start_location(self, ) -> str:
            return _start_loc


    def set_language(self, language: str) -> None:
            _language = language


    def query_language(self, ) -> str:
            return _language


    def set_information(self, info: str) -> None:
            _information = info


    def query_information(self, ) -> str:
            if (!_information) {
            _information = "The $C$" + query_name() + " nationality is yet to "
            "be described.\n"


    def query_region_description(self, region: str) -> str:
            return _regions[region]->description


    def query_region_start_location(self, region: str) -> str:
            return _regions[region]->start_location


    def query_start_location(self, region: str) -> str:
            if (_regions[region] && _regions[region]->start_location) {
            return _regions[region]->start_location


    def query_region_accent_ob(self, region: str) -> str:
            if (_regions[region]) {
            return _regions[region]->accent_ob


    def set_currency_area(self, area: str) -> None:
            _currency = area


    def query_currency_area(self, ) -> str:
            return _currency



class Basic(MudObject):

    _regions = '([ ])'
