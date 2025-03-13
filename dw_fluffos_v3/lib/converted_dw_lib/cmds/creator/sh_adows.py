# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/sh_adows.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, indirect_obs: MudObject) -> int:
            object *objs, *shadows, ob, shad, nobj
            objs = indirect_obs
            foreach (ob in objs) {
            shadows = [})
            nobj = ob
            while(nobj = shadow(nobj, 0))
            shadows += [nobj]
            if(!sizeof(shadows)) {
            write(WIZ_PRESENT.desc_f_object(ob) + " is not being shadowed.\n")
            } else {
            write(WIZ_PRESENT.desc_f_object(ob) + " is being shadowed by:\n")
            foreach (shad in shadows)
            write("    " + file_name(shad) + "\n")



class Sh_adows(MudObject):
