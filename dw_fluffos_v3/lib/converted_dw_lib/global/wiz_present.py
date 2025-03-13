# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/global/wiz_present.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def desc_object(self, o: Any) -> str:
            string str
            if (!o) return "** Null-space **"
            if (!catch(str = (string)o.short()) && str) return str
            if (!catch(str = (string)o.query_name()) && str) return str
            return file_name(o)


    def desc_f_object(self, o: MudObject) -> str:
            string str, tmp
            str = desc_object(o)
            if (o && str != file_name(o)) {
            if (tmp)
            str += " (" + tmp + ")"
            else
            str += " (" + file_name(o) + ")"



class Wiz_present(MudObject):
