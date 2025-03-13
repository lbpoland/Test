# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/ptest_ers.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def query_applicant_text(self, ) -> str:
            varargs int cmd(string check, string name, string reason) {
            int i
            string *names, *projects
            string ret = ""
            class project *tmp, *tmp2
            switch (check) {
            case "ptinfo":
            ret = PLAYTESTER_HAND.query_show_list_colour()
            tell_object (this_player(), ret)
            return 1
            break
            case "assign":
            i = PROJECT_HANDLER->find_project (name)
            if (i == -1) {
            this_player()->add_failed_mess (self, "There is no project "
            "of that ID.\n", [}))
            return 0



class Ptest_ers(MudObject):
