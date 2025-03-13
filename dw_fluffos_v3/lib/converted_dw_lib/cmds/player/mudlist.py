# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/mudlist.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> int:
            mixed *info
            string *list
            mapping borg
            string mud
            if( str && str != "") {
            mapping tmp
            string opt, tmpstr
            tmp = (mapping)INTERMUD_D.GetMudList()
            if( str[0] != '-' ) str = "-n " + str
            opt = str[1..1]
            str = str[3..]
            borg = ([])
            foreach(mud, info in tmp) {
            int x, y, z
            switch(opt) {
            case "m":
            x = 5
            break
            case "d":
            x = 7
            break
            case "n":
            x = 0
            break


    def alphabet(self, a: str, b: str) -> int:
            if((a = lower_case(a)) == (b = lower_case(b))) return 0
            else if(a > b) return 1
            else return -1


    def help(self, ) -> None:
            message("help", "Syntax: <mudlist>\n"
            "        <mudlist -dmn [arg]>\n\n"
            "Without any arguments, it gives a full listing of all muds "
            "with which this mud is capable of communication through "
            "tell, mail, finger, rwho, and other intermud services.  "
            "With arguments, <mudlist> requires one and only one option "
            "which must be one of the following:\n"
            "\t-d [driver]: List only muds using the named driver\n"
            "\t-m [mudlib]: List only muds using the named mudlib\n"
            "\t-n [mudname]: List only the muds with the name given\n\n"
            "Note that the argument need not be complete, for example:\n"
            "\t mudlist -n idea\n"
            "will list IdeaExchange as well as any other mud whose name "
            "begins with the string \"idea\".\n\n"
            "See also: finger, mail, rwho, tell", this_player())


    def clean_up(self, ) -> None:
            destruct(self)


    def reset(self, ) -> None:
            destruct(self)


    def dest_me(self, ) -> None:
            destruct(self)



class Mudlist(MudObject):
