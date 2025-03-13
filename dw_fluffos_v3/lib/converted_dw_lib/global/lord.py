# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/global/lord.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def query_creator(self, ) -> int:
            return 1


    def query_object_type(self, object) -> str:
            if (master()->query_trustee(geteuid(self)))
            return "T"
            return "D"


    def event_enter(self, me: MudObject, s1: str, from: MudObject) -> None:
            if ((!s1 || s1 == "") && interactive(me)) {
            if (environment() == environment(me))
            event_inform(me, me.query_cap_name()+" invisibly enters the room",
            "enter")
            else
            event_inform(me, me.query_cap_name()+" invisibly enters your inventory",
            "enter")


    def event_exit(self, me: MudObject, s1: str, from: MudObject) -> None:
            if ((!s1 || s1 == "") && interactive(me)) {
            if (environment() == environment(me))
            event_inform(me, me.query_cap_name()+" invisibly exits the room",
            "enter")
            else
            event_inform(me, me.query_cap_name()+" invisibly exits your inventory",
            "enter")


    def __init__(self):



class Lord(MudObject):
