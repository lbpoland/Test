# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/haggle_handler.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.accept_sayings = []
            self.bodged_sayings = []
            self.finalb_sayings = []
            self.finals_sayings = []
            self.insult_sayings = []
            self.offerb_sayings = []
            self.offers_sayings = []
            self.sodoff_sayings = []


    def insult_factor(self, keeper: MudObject, customer: MudObject) -> int:
            return 150


    def bargain_factor(self, keeper: MudObject, customer: MudObject) -> int:
            return 50



class Haggle_handler(MudObject):

    accept_sayings = '[]'

    bodged_sayings = '[]'

    finalb_sayings = '[]'

    finals_sayings = '[]'

    insult_sayings = '[]'

    offerb_sayings = '[]'

    offers_sayings = '[]'

    sodoff_sayings = '[]'
