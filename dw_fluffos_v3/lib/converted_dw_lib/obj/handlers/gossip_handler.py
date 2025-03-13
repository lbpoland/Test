# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/gossip_handler.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.filter_these = ['fuck', 'fucking', 'fucker', 'cunt', 'bitch', 'shit']
            self.gossip = []
            self.rumours = []


    def add_gossip(self, name: str, mess: str) -> None:
            string *bits
            int i
            bits = explode(mess, " ")
            for (i = 0; i < sizeof(bits); i++) {
            if (filter_these.index(bits[i]) if bits[i] in filter_these else -1 != -1) {
            return


    def add_rumour(self, name: str, mess: str) -> None:
            rumours += [[name, mess]]
            save_stuff()



class Gossip_handler(MudObject):

    filter_these = "['fuck', 'fucking', 'fucker', 'cunt', 'bitch', 'shit']"

    gossip = '[]'

    rumours = '[]'
