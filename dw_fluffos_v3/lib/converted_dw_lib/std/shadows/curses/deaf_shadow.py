# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shadows/curses/deaf_shadow.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def event_whisper(self, ob: MudObject, start: str, mess: str, d: MudObject, lang: str) -> None:
            int i
            i = (int)arg() / 2
            if (random(100) < i) {
            player.event_whisper(ob, start, mess, d, lang)
            } else {
            player->add_message(ob, "$N %hiss% something at you, but you just "+
            "can't make it out.\n", 1)


    def event_person_say(self, ob: MudObject, start: str, mess: str, lang: str) -> None:
            string dum1, dum2
            if (sscanf(start, "%sloud%s", dum1, dum2)) {
            if (random(100) > (100 - (int)arg()) / 2) {
            player.event_person_say(ob, start, mess, lang)
            } else {
            player->add_message(ob, "$N say$s something loudly, but "+
            "you fail to hear it properly.\n", 1)



class Deaf_shadow(MudObject):
