# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/armour_logic.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.ac = ([ ])
            self.armour_types = []


    def add_ac(self, name: str, type: str, a_c: Any) -> int:
            int i
            if (!stringp(type))
            return 0
            if (!ac) ac = ([ ])
            if (ac[name])
            return 0
            ac[name] = [a_c, type]
            if ((i=armour_types.index(type) if type in armour_types else -1) == -1)
            armour_types += [type, [name]]
            else
            armour_types[i+1] += [name]
            return 1


    def remove_ac(self, name: str) -> int:
            int j, k
            if (!ac[name])
            return 0
            j = armour_types.index(ac[name][1]) if ac[name][1] in armour_types else -1
            k = armour_types[j+1].index(name) if name in armour_types[j+1] else -1
            armour_types[j+1] = delete(armour_types[j+1], k, 1)
            if (!sizeof(armour_types[j+1]))
            armour_types = delete(armour_types, j, 2)
            map_delete(ac, name)
            return 1


    def calc_value(self, arr: Any) -> int:
            int i, val
            if (intp(arr)) {
            if(!random(10))
            return random(arr)
            else
            return arr


    def calc_string(self, b: Any) -> str:
            if (intp(b))
            return "rand("+b+")"
            if (!pointerp(b))
            return "Dead"
            switch (sizeof(b)) {
            case 1 :
            return ""+b[0]
            case 2 :
            return ""+b[0]+"+rand("+b[1]+")"
            case 3 :
            return ""+b[0]+"+"+b[1]+"d"+b[2]
            default :
            return "Oh hell"


    def set_ac(self, bing: Any) -> None:
            int i
            for (i=0;i<sizeof(ac);i+=A_ARRAY_SIZE)
            add_ac(ac[i], ac[i+1][A_TYPE], ac[i+1][A_AC])



class Armour_logic(MudObject):

    ac = '([ ])'

    armour_types = '[]'
