# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/living/echo.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> Any:
            if(!TP.query_creator() && !TP.query_property("echo"))
            return notify_fail(NOT_ALLOWED)
            if (!str || str == "")
            return notify_fail("Syntax : echo <text>\n")
            if (!TP.query_creator() && TP.adjust_sp(-ECHO_COST) < 0)
            return notify_fail(NO_POWER)
            if (TP.query_volume(D_ALCOHOL))
            str = TP.drunk_speech(str)
            log_file("ECHOS", ctime(time())+" "+this_player()->query_name()+" echos: "+
            str+"\n")
            str += "%^RESET%^"
            my_mess("You echo: ", str)
            TP.comm_event(environment(TP), "player_echo", str + "\n")
            return 1


    def my_mess(self, fish: str, erk: str) -> None:
            if(!interactive(TP)) return
            printf("%s%-=*s\n", fish, (int)TP.query_cols()-strlen(fish),
            TP.fix_string(erk))



class Echo(MudObject):
