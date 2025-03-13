# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/usage.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, arg: str) -> Any:
            mapping info
            info = rusage()
            printf("Current statistics are:\n"+
            "Memory: %d\nMajorfaults: %d\nUser time: %d\nSystem time: %d\n",
            info["maxrss"], info["majflt"], info["minflt"],
            info["utime"] / 1000, info["stime"] / 1000)
            return 1


    def dest_me(self, ) -> None:
            destruct(self)


    def clean_up(self, ) -> None:
            dest_me()


    def reset(self, ) -> None:
            dest_me()



class Usage(MudObject):
