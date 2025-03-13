# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/al_ias.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def alias_string(self, al: Any) -> str:
            int i
            int num
            int *add_thing
            string str
            str = ""
            add_thing = [})
            for (i=0;i<sizeof(al);i++) {
            if (stringp(al[i])) {
            str += replace(al[i], ({";", "\\;"}))
            } else {
            num = al[i] & ALIAS_MASK
            switch (al[i] - num) {
            case NEW_LINE  :
            str += ";"
            break
            case ALL_ARGS  :
            str += "$*$"
            break
            case ONE_ARG   :
            str += "$"+num+"$"
            break
            case TO_ARG    :
            str += "$*"+num+"$"
            break
            case FROM_ARG  :
            str += "$"+num+"*$"
            break
            case ALL_ARG   :
            str += "$arg:"+al[++i]+"$"
            break
            case ARG_THING :
            str += "$arg"+num+":"+al[++i]+"$"
            break
            case ELSE_THING :
            str += "$else$"
            break
            case ALL_IFARG :
            str += "$ifarg:"
            break
            case IFARG_THING :
            str += "$ifarg"+num+":"
            break
            case CURR_LOC :
            str += "$!$"
            break
            case END_IF      :
            str += "$endif$"
            break


    def print_aliases(self, filter: str, sorted: int) -> int:
            int i
            int len
            string str
            string str1
            string str2
            string *tmp
            string bing
            mapping aliases
            string ret
            aliases = this_player()->query_aliases()
            if (!m_sizeof(aliases)) {
            notify_fail("None defined.\n")
            return 0


    def print_some_aliases(self, str: str, every: int) -> int:
            if (this_player()->is_alias(str) && !every) {
            printf("%s: %-=*s\n", str,
            (int)this_player()->query_cols() - strlen(str) -2,
            alias_string(this_player()->query_player_alias(str)))
            return 1



class Al_ias(MudObject):
