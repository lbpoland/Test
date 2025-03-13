# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/dupd_ate.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def do_it(self, str: str) -> int:
            object ob, *obs
            string *all, *dil, file, fnob
            obs = WIZ_PRESENT.wiz_present(str, this_player())
            if(!sizeof(obs))
            return 0
            foreach(ob in obs){
            fnob = file_name(ob)
            all = inherit_list(ob)
            foreach(file in all){
            if (other){
            dil = deep_inherit_list(find_object(file))
            if (!((dil.index(other) if other in dil else -1 != -1) || other == file))
            continue


    def cmd(self, str: str) -> int:
            object *tmp
            other = 0
            notify_fail("usage: dupdate <object> [<object>]\n")
            if (!str)
            return 0
            sscanf(str, "%s %s", str, other)
            if (other){
            tmp = WIZ_PRESENT.wiz_present(other, this_player())
            if (sizeof(tmp)){
            other = file_name(tmp[0])
            other += ".c"



class Dupd_ate(MudObject):
