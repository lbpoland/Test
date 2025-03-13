# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/living/get.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def find_matching_obs(self, match_str: str, dob: MudObject) -> List[MudObject]:
            class obj_match result
            result = (class obj_match)match_objects_in_environments(match_str, dob)
            if (result->result != OBJ_PARSER_SUCCESS) {
            add_failed_mess(match_objects_failed_mess(result))
            return 0


    def cmd(self, : MudObject, dir: str, indir: str, args: Any) -> Any:
            object *dest
            object ob
            object dob
            object *fail_dest
            object *too_many
            mixed *fail
            mixed *ret
            mixed amt
            string sh
            string hand_unit
            string match_str
            int i
            int num
            int cap
            int perc
            int handful
            int total_num
            mixed we
            object env
            object *bing
            fail_dest = [})
            cap = (int) TP.query_max_weight()
            if (indir && sizeof(obs) > 10) {
            add_failed_mess("Please be more specific as to what you want "
            "to get from.\n")
            return 0



class Get(MudObject):
