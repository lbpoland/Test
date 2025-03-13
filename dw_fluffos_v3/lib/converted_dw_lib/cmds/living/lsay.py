# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/living/lsay.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, arg: str) -> Any:
            int *co_ords
            int status
            class message mess
            if (!arg)  arg = ""
            mess = build_message("@loudly " + arg, 0, "say")
            status = say_it(mess)
            if(status && TP && environment(TP))  {
            co_ords = environment(TP)->query_co_ord()
            BROADCASTER->npc_shout_event(TP, mess->notify_mess, mess->text,
            mess->language, co_ords, 20)



class Lsay(MudObject):
