# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/simul_efun/add_action.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def enable_commands(self, ) -> None:
            efun::set_this_player(previous_object())
            LIV.enable_commands(previous_object())


    def set_living_name(self, name: str) -> None:
            LIV.set_living_name(name, previous_object())


    def living(self, ob: MudObject) -> int:
            if(!ob)
            return 0
            return ob._living()


    def _notify_fail(self, mes: str) -> int:
            _nf = mes
            return 0


    def query_notify_fail(self, ) -> str:
            return _nf


    def command(self, cmd: str) -> Any:
            int time = eval_cost()
            if(evaluate(bind((:call_other:), previous_object()),previous_object(),
            "_process_input", cmd))
            return eval_cost() - time + 1
            return 0


    def set_this_player(self, ob: MudObject) -> None:
            error("Illegal use of set_this_player.")



class Add_action(MudObject):
