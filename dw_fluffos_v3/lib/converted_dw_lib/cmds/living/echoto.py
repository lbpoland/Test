# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/living/echoto.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> Any:
            string who, what
            object ob
            if(!TP.query_creator() && !TP.query_property("echoto"))
            return notify_fail(NOT_ALLOWED)
            if(!str || str == "")
            return notify_fail("Syntax : echoto <player> <text>\n")
            if(sscanf(str, "%s %s", who, what) != 2)
            return notify_fail("Syntax : echoto <player> <text>\n")
            who = lower_case(who)
            who = (string)TP.expand_nickname(who)
            if(!TP.query_creator() && TP.adjust_sp(-ECHOTO_COST) < 0)
            return notify_fail(NO_POWER)
            ob = find_player(who)
            if(!ob)
            return notify_fail("Can't find "+who+".\n")
            if (TP.query_volume(D_ALCOHOL))
            what = TP.drunk_speech(what)
            log_file("ECHOS", ctime(time())+" "+this_player()->query_name()+" echos "+
            "to "+who+": "+what+"\n" )
            what += "%^RESET%^"
            my_mess("You echo to " + who + ": ", what)
            event(ob, "player_echo_to", what + "\n", TP)
            return 1


    def my_mess(self, fish: str, erk: str) -> None:
            if(!interactive(TP)) return
            printf("%s%-=*s\n", fish, (int)TP.query_cols()-strlen(fish),
            TP.fix_string(erk))



class Echoto(MudObject):
