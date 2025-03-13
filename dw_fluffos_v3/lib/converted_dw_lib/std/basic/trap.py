# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/basic/trap.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def basic_trap(self, action: str) -> int:
            if(!_trap_armed || action != _trap_trigger)
            return 1
            switch(TASKER.perform_task(this_player(), SKILL, _trap_difficulty,
            TM_FREE)) {
            case AWARD:
            write("%^YELLOW%^You feel you have learned something about avoiding "
            "traps.%^RESET%^\n")
            case SUCCEED:
            return 1
            default:
            if(arrayp(_trap_message)) {
            write(_trap_message[0])
            say(_trap_message[1], this_player())
            } else
            write(_trap_message)
            if(intp(_trap_effect)) {
            if(_trap_effect > this_player()->query_hp())
            this_player()->do_death()
            else
            this_player()->adjust_hp(-(_trap_effect))
            } else if(arrayp(_trap_effect)) {
            if(sizeof(_trap_effect) == 2)
            this_player()->add_effect(_trap_effect[0], _trap_effect[1])
            else
            this_player()->add_effect(_trap_effect[0], _trap_effect[1..])
            } else
            this_player()->add_effect(_trap_effect)
            return 0



class Trap(MudObject):
