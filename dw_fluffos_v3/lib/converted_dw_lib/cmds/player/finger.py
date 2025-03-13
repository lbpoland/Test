# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/finger.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, ) -> Any:
            string ret
            object ob, *obs
            string type
            string str
            obs = users()
            obs = sort_array(obs, (: strcmp($1.query_cap_name(),
            $2.query_cap_name()) :))
            str = sprintf("%-12.12s    %-20.20s %-20.20s %-20.20s\n",
            "Name", "Real name", "Where", "Birthday")
            foreach (ob in obs) {
            string euid
            type = (ob.query_earmuffs() ? "e" : " ")
            euid = geteuid(ob)
            type += ob.query_object_type()
            str += sprintf("%-12.12s %2.2s %-20.20s %-20.20s %-20.20s\n",
            (ob.query_invis()?"("+ob.query_cap_name()+")":(string)ob.query_cap_name()),
            type,
            ((ret = (string)ob.query_real_name())?ret:"-"),
            ((ret = (string)ob.query_where())?ret:"-"),
            ((ret = (string)ob.query_birthday())?ret:"-"))


    def finger_player(self, str: str) -> int:
            string ret
            string mud
            if (str) {
            str = lower_case(str)
            str = (string)this_player()->expand_nickname(str)



class Finger(MudObject):
