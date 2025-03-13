# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/trig.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def sin(self, angle: int) -> int:
            {
            while (angle < 0) angle += 360
            while (angle >= 360) angle -= 360
            if (angle >= 270) return -sintab[360 - angle]
            if (angle >= 180) return -sintab[angle - 180]
            if (angle >= 90) return sintab[180 - angle]
            return sintab[angle]


    def cos(self, angle: int) -> int:
            {
            return sin(90 - angle)


    def tan(self, angle: int) -> int:
            {
            return 1000 * sin(angle) / (sin(90 - angle) / 1000)


    def pow1_5(self, n: int) -> int:
            {
            if (n > 30) n = 30
            else if (n < -30) n = -30
            return pow[30-n]



class Trig(MudObject):
