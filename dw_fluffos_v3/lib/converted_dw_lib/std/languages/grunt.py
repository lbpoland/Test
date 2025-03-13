# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/languages/grunt.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def long(self, ) -> str:
            return "Consists of grunting noises.\n"


    def garble_say(self, start: str, rest: str) -> Any:
            string nam, loud
            sscanf(start, "%s %s:", nam, start)
            if (sscanf(start, "%s loudly", start) == 1)
            loud = " loudly"
            else
            loud = ""
            switch (start) {
            case "asks" :
            nam = nam+" quizzically grunts"+loud
            break
            case "exclaims" :
            nam = nam+" pointedly grunts"+loud
            break
            default :
            nam = nam+" grunts"+loud
            break



class Grunt(MudObject):
