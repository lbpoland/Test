# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/clock.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def query_time_string(self, ) -> str:
            string mess
            int minute, hour, *arr
            minute = (AM_TIME_HANDLER.query_am_minute(time()) % 60)
            hour = AM_TIME_HANDLER.query_am_hour(time())
            if(minute > 30 )
            hour = hour + 1
            hour = hour % 12
            mess = ""
            switch(minute) {
            case 53..57:
            mess += "five to " + HOURS[hour]; break
            case 48..52:
            mess += "ten to " + HOURS[hour]; break
            case 43..47:
            mess += "quarter to " + HOURS[hour]; break
            case 38..42:
            mess += "twenty to " + HOURS[hour]; break
            case 33..37:
            mess += "twenty-five to " + HOURS[hour]; break
            case 28..32:
            mess += "half past " + HOURS[hour]; break
            case 23..27:
            mess += "twenty-five past " + HOURS[hour]; break
            case 18..22:
            mess += "twenty past " + HOURS[hour]; break
            case 13..17:
            mess += "a quarter past " + HOURS[hour]; break
            case 8..12:
            mess += "ten past " + HOURS[hour]; break
            case 3..7:
            mess += "five past " + HOURS[hour]; break
            default:
            mess += HOURS[hour] + " o'clock"


    def extra_look(self, thing: MudObject) -> str:
            return query_time_string() + ".\n"


    def set_chimes(self, num: int, mess: str) -> None:
            CHIME_HANDLER.register_for_chimes(self, num, mess)


    def chime(self, chime_message: str, type: int) -> None:
            say(chime_message)



class Clock(MudObject):
