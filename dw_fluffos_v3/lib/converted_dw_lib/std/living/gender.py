# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/living/gender.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def query_gender_string(self, ) -> str:
            if (!gender && !womens_day) return "neuter"
            else if (gender == 1 && !womens_day) return "male"
            else return "female"


    def query_gender_title(self, ) -> str:
            if (!gender && !womens_day) return "creature"
            else if (gender == 1 && !womens_day) return "sir"
            else return "madam"


    def query_gender_name(self, ) -> str:
            if (!gender && !womens_day) return "neuter"
            else if (gender == 1 && !womens_day) return "man"
            else return "woman"


    def query_objective(self, ) -> str:
            if (!gender && !womens_day)
            return "it"
            else if (gender == 1 && !womens_day)
            return "him"
            else return "her"


    def query_possessive(self, ) -> str:
            if (!gender && !womens_day)
            return "its"
            else if (gender == 1 && !womens_day)
            return "his"
            else return "her"


    def query_pronoun(self, ) -> str:
            if (!gender && !womens_day)
            return "it"
            else if (gender == 1 && !womens_day)
            return "he"
            else return "she"


    def set_gender(self, arg: Any) -> None:
            if(stringp(arg)) {
            if(arg == "male")
            gender = 1
            else if(arg == "female")
            gender = 2
            else
            gender = 0
            } else {
            gender = arg


    def set_womens_day(self, bing: int) -> None:
            womens_day = bing


    def query_womens_day(self, ) -> int:
            return womens_day



class Gender(MudObject):
