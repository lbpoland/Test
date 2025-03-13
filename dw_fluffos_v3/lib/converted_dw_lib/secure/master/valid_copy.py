# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/master/valid_copy.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def valid_copy(self, path: str, euid: Any, func: str) -> int:
            object master_ob
            string *bits = explode(path, "/") - ["", "."]
            mapping perms
            perms = permission_match_path(permissions, path)
            if(sizeof(bits) < 2 || bits[0] == "open" || bits[0] == "doc" ||
            bits[0] == "log" || bits[0] == "mudlib" || bits[0] == "w")
            return check_permission(euid, func, path, perms, READ_MASK)
            master_ob = find_object("/d/" + bits[1] + "/master")
            if((master_ob && master_ob.copy_with_read(path, euid, func)) ||
            (!master_ob && master()->query_senior(euid)))
            return check_permission(euid, func, path, perms, READ_MASK)
            else
            return check_permission(euid, func, path, perms, WRITE_MASK)



class Valid_copy(MudObject):
