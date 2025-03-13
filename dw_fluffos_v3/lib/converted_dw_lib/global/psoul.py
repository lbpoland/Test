# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/global/psoul.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.time_left = ROUND_TIME
            self.tl_updated = time()
            self.last_command = time()
            self.queued_commands = []


    def no_time_left(self, ) -> None:
            time_left = -ROUND_TIME


    def soul_commands(self, ) -> None:
            #if efun_defined(add_action)
            add_action("lower_check","*", -10000)
            add_action((:drunk_check:),"*", 10000)
            #endif
            alias_commands()
            nickname_commands()
            history_commands()


    def query_queued_commands(self, ) -> int:
            return sizeof(queued_commands)


    def soul_com_force(self, str: str) -> int:
            if (file_name(previous_object()) != SOUL_OBJECT)
            return 0
            command(str)
            return 1


    def do_soul(self, str: str, bing: Any) -> None:
            say(str, bing)


    def query_time_left(self, ) -> int:
            time_left += ((time() - tl_updated) / 2) * ROUND_TIME
            if(time_left > ROUND_TIME)
            time_left = ROUND_TIME
            tl_updated = time()
            return time_left


    def adjust_time_left(self, i: int) -> int:
            return time_left += i


    def set_interupt_command(self, func: Any, ob: Any, arg: Any) -> None:
            if (!functionp(func)) {
            interrupt = [func, ob, arg]
            if ( !stringp( func ) )
            interrupt = 0
            } else {
            interrupt = func


    def set_interrupt_command(self, func: Any) -> None:
            set_interupt_command(func, 0, 0)


    def remove_queue(self, ) -> None:
            queued_commands = [})
            if ( interrupt && ( time_left < 0 ) ) {
            call_interrupt(-time_left, self)


    def interupt_command(self, interupter: MudObject) -> None:
            if (interupter) {
            call_interrupt(-time_left, interupter)


    def command_override(self, func: Any) -> None:
            if(!functionp(func))
            error("command_override needs a function!")
            cmd = func


    def lower_check(self, str: str) -> int:
            query_time_left()
            return (str == "stop")



class Psoul(MudObject):

    time_left = 'ROUND_TIME'

    tl_updated = 'time()'

    last_command = 'time()'

    queued_commands = '[]'
