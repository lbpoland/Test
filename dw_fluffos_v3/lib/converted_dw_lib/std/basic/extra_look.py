# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/basic/extra_look.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.extra_looks = []


    def calc_extra_look(self, ) -> str:
            int i
            string s1, s2
            s1 = ""
            if (!extra_looks) {
            extra_looks = [})


    def add_extra_look(self, ob: MudObject) -> None:
            if(extra_looks.index(ob) if ob in extra_looks else -1 != -1) {
            return


    def remove_extra_look(self, ob: MudObject) -> None:
            int i
            i = extra_looks.index(ob) if ob in extra_looks else -1
            if (i < 0) {
            return



class Extra_look(MudObject):

    extra_looks = '[]'
