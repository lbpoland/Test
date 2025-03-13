# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/simul_efun/find_match.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def is_in_me_or_environment(self, thing: MudObject, person: MudObject) -> int:
            object env
            if ((env = environment(thing)) == environment(person))
            return 1
            if (!env)
            return 1
            while (env  &&  !living(env))
            env = environment(env)
            if (env == person)
            return 1
            return 0


    def filter_in_me_or_environment(self, obs: Any, player: MudObject) -> List[MudObject]:
            return filter(obs, (: is_in_me_or_environment($1, $2) :), player)



class Find_match(MudObject):
