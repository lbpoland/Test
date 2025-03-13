# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/inherit/craft_skills.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._craft_skill_tree = []


    def __init__(self):
            self._craft_skill_tree = []
            private mixed *add_craft_skill_int(string *bits,
            mixed *arr) {
            int pos
            pos = arr.index(bits[0]) if bits[0] in arr else -1
            if (pos == -1) {
            pos = sizeof(arr)
            arr += [bits[0], 0, 0, [})]



class Craft_skills(MudObject):

    _craft_skill_tree = '[]'
