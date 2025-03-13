# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/council_archive.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def query_case_short(self, nomic_case: Any) -> str:
            string ret
            ret = "Case #" + the_case->id + " \"" +
            the_case->short + "\" opened by " + the_case->opener +
            " against " + query_multiple_short(the_case->people) + " at " +
            ctime(the_case->time_opened)
            return ret


    def do_list_all_cases(self, ) -> int:
            int* cases
            string ret
            int id
            cases = NOMIC_HANDLER.query_closed_cases(query_council_area())
            if (!sizeof(cases)) {
            add_failed_mess("There are no open cases.\n")
            return 0


    def do_list_case(self, case_id: int) -> int:
            string ret
            class nomic_case the_case
            class nomic_case_note note
            class nomic_case_event event
            int id
            ret = ""
            the_case = NOMIC_HANDLER.query_closed_case(query_council_area(), case_id)
            if (!the_case) {
            add_failed_mess("Unable to find the case.\n")
            return 0


    def do_list_citizens(self, ) -> int:
            object* cits
            string ret
            string area
            area = self.query_council_area()
            cits = filter( users(), (: NOMIC_HANDLER->is_citizen_of(
            self.query_council_area(), $1.query_name() ) &&
            $1.query_visible( this_player() ) :) )
            cits = sort_array(cits, (: strcmp($1.query_name(), $2.query_name()) :))
            ret = "The online citizens (and magistrates) of " + area + " are:\n\n"
            ret += query_multiple_short(cits)
            write("$P$Citizens Online$P$" + ret)
            return 1


    def init(self, ) -> None:
            add_command("list", "", (: do_list_all_cases() :))
            add_command("list", "[case] <number>", (: do_list_case($4[0]) :))
            add_command("list", "citizens", (: do_list_citizens() :))



class Council_archive(MudObject):
