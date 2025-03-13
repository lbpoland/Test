# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/findr_edef.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, ob: MudObject, var: str) -> int:
            string *files = find_stuff(ob, var)
            if(sizeof(files) > 1)
            printf("%s is defined in %s and %s.\n", var, implode(files[0..<2], ", "),
            files[<1])
            else
            write("No redefinition found.\n")
            return 1



class Findr_edef(MudObject):
