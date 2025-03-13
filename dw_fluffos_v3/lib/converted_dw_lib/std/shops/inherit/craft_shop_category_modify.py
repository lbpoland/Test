# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/inherit/craft_shop_category_modify.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._minimum_age_to_vote = 2 * DAY


    def set_minimum_age_to_vote(self, age: int) -> None:
            _minimum_age_to_vote = age


    def set_minimum_age_to_nominate(self, age: int) -> None:
            _minimum_age_to_nominate = age


    def set_minimum_nomination_number(self, num: int) -> None:
            _minimum_number_nominated = num


    def set_nomination_time(self, tim: int) -> None:
            _nomination_time = tim


    def set_election_time(self, tim: int) -> None:
            _election_time = tim


    def set_deletion_time(self, tim: int) -> None:
            _deletion_time = tim



class Craft_shop_category_modify(MudObject):

    _minimum_age_to_vote = '2 * DAY'
