# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shadows/npc/gossip.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def event_person_say(self, ob: MudObject, start: str, mess: str, lang: str) -> None:
            int i
            string *bits
            string *filter
            player.event_person_say(ob, start, mess, lang)
            if (!userp(ob)) {
            return


    def do_gossip_say(self, str: str) -> None:
            int i
            string *stuff
            int chance
            if (!str) {
            str = "$name$ said: $mess$"



class Gossip(MudObject):
