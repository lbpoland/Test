# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/global/wiz_object_comm.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.obvar = ([ ])


    def affirmative(self, s: str) -> int:
            {
            s = lower_case(s)
            return (s == "y" || s == "yes" || s == "ok" || s == "please")


    def handle_error(self, erm: str, desc: str) -> None:
            if (erm) {
            write(desc + " failed : " + erm)


    def set_obvar(self, key: str, value: MudObject) -> None:
            obvar[key] = value


    def del_obvar(self, key: str) -> None:
            map_delete(obvar, key)


    def get_obvar(self, key: str) -> MudObject:
            return obvar[key]


    def desc_object(self, o: Any) -> str:
            log_file("WIZ_PRESENT", sprintf("desc_object() called by %O.\n",
            previous_object()))
            return ""


    def desc_f_object(self, o: Any) -> str:
            log_file("WIZ_PRESENT", sprintf("desc_f_object() called by %O.\n",
            previous_object()))
            return ""



class Wiz_object_comm(MudObject):

    obvar = '([ ])'
