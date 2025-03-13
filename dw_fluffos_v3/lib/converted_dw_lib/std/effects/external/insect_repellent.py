# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/external/insect_repellent.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def query_classification(self, ) -> str:
            return "herb.insect.repellent"


    def beginning(self, them: MudObject, power: int, id: int) -> int:
            if (power <= 0) {
            them.submit_ee(0, 1, EE_REMOVE)
            return 0


    def merge_effect(self, them: MudObject, power: int, adjust: int) -> int:
            power += adjust
            if (power <= 0) {
            them.submit_ee(0, 1, EE_REMOVE)
            return 0


    def start_mess(self, them: MudObject, power: int, id: int) -> None:
            string start_mess
            switch (power) {
            case 1:
            start_mess = "You smell rather pleasant, much as you might wish to for a "
            "date."
            break
            case 2..3:
            start_mess = "A pungent smell envelops you."
            break
            default:
            start_mess = "A horribly pungent smell envelops you, sufficient to make "
            "anyone with a sense of smell keep their distance."


    def smell(self, them: MudObject, power: int, id: int) -> None:
            string self_mess, other_mess
            object env
            if (--power <= 0) {
            await them.send("The herbal odour around you fades away.\n")
            them.remove_property("insect")
            them.submit_ee(0, 1, EE_REMOVE)
            return 0



class Insect_repellent(MudObject):
