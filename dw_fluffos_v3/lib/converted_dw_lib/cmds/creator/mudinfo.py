# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/mudinfo.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> Any:
            mapping r
            float cpu
            string name, cc, tmp
            int *ltype
            name = capitalize(mud_name()) + "   (" + query_host_name() + " " +
            __PORT__ + ")"
            cc = __COMPILER__ + "   (" + __OPTIMIZATION__ + ")"
            r = rusage()
            cpu = ((r["utime"] + r["stime"]) / uptime() / 10.0)
            num_obs = 0
            objects((: num_obs++ :))
            ltype = implode(users(), (:$1[compressedp($2)]++, $1:), ({0,0}))
            tmp = PAD("Mud name", name) +
            PAD("Driver", __VERSION__) +
            PAD("Architecture", __ARCH__) +
            PAD("Compiler", cc) +
            PAD("Driver uptime", pretty_time(uptime(), 4)) +
            PAD("Avg Cpu usage", sprintf("%4.2f%%",cpu)) +
            PAD("Load Average", query_load_average()) +
            PAD("No of users", sizeof(users())) +
            PAD("Using MCCP", ltype[1]) +
            PAD("Plain telnet", ltype[0]) +
            PAD("Named Livings", sizeof(named_livings())) +
            PAD("Objects", num_obs) +
            PAD("Call Outs", sizeof(call_out_info()) + " pending.") +
            PAD("Memory usage", memory_info())
            await this_player().send(tmp)
            return 1



class Mudinfo(MudObject):
