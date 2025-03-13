# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/birthdays.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, ) -> int:
            object *peeps
            peeps = filter(users(), (: $1.query_visible(this_player())  &&
            $1.query_is_birthday_today() :))
            if (sizeof(peeps) == 0)
            return notify_fail("No one has a birthday today.\n")
            if (sizeof(peeps) == 1)
            printf("%s has a birthday today.\n", peeps[0]->short())
            else
            write(query_multiple_short(peeps) + " have a birthday today.\n")
            return 1



class Birthdays(MudObject):
