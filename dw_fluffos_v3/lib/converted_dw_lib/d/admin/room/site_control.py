# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/admin/room/site_control.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_light(100)
            set_short("site-access control room")
            add_property("determinate", "the ")
            set_long(
            "In front of you teem hundreds of small packages.  They rush around "+
            "yelling out strange numbers and get directed into various parts "+
            "of the maze by large mice with red flags.  Everything happens at "+
            "break neck speed.  Every now and then one of the packages "+
            "spontaneously combusts.\n"+
            "Available commands:\n"+
            "  ban       :  Ban a site.\n"+
            "  access    :  Show the current access of various sites.\n"+
            "  suspend   :  Suspend someones access.\n"+
            "  unsuspend :  Unsuspend someones access.\n")
            seteuid("Admin")
            add_exit("north", ROOM+"domain_control", "corridor")


    def init(self, ) -> None:
            ::init()
            if (!interactive(previous_object(NUM))) return 0
            if ("/secure/master"->query_lord(geteuid(previous_object(NUM))))
            add_command("ban", "<string>", (:do_banish($4[0]):))
            add_command("access", "", (:do_access():))
            add_command("suspend", "<string'person'>", (:do_suspend($4[0]):))
            add_command("unsuspend", "<string'person'>", (:do_unsuspend($4[0]):))


    def print_access(self, bit: str, bing: Any, depth: int, cols: int) -> int:
            mixed *bits
            int i
            if (this_player() != this_player(1))
            return 0
            bits = m_indices(bing)
            if (depth == 4) {
            for (i=0;i<sizeof(bits);i++)
            switch (bing[bits[i]][0]) {
            case NO_NEW :
            printf("%s@%-=*s", bits[i], cols - strlen(bits[i]), bit +
            " set to no new characters.\n")
            break
            case NO_ACCESS :
            printf("%s@%-=*s", bits[i], cols - strlen(bits[i]), bit +
            " set to no characters.\n")
            break
            case ACCESS :
            printf("%s@%-=*s", bits[i], cols - strlen(bits[i]), bit +
            " set to normal access.\n")
            break


    def do_access(self, ) -> int:
            mixed bing
            if (this_player() != this_player(1))
            return 0
            bing = (mixed)"/secure/bastards"->query_all_access()
            if (!m_sizeof(bing)) {
            notify_fail("No access control defined.\n")
            return 0


    def do_banish(self, str: str) -> int:
            string ip, ident, reason
            int level
            if (this_player() != this_player(1))
            return 0
            if (!"/secure/master"->high_programmer(geteuid(previous_object())))
            return 0
            notify_fail("Syntax: banish <ip number> <ident> <level> <reason>\n"+
            "        <level> := 0 delete ident, 1 normal access,\n"+
            "                   2 no new players, 3 No access.\n")
            if (!str)
            return 0
            if (sscanf(str, "%s %s %d %s", ip, ident, level, reason) != 4)
            return 0
            if (!"/secure/bastards"->change_access(explode(ip, "."), ident, level,
            reason))
            return 0
            write("Access permisions changed.\n")
            return 1


    def do_suspend(self, str: str) -> int:
            string reason
            string name
            int tim
            if (this_player() != this_player(1))
            return 0
            if (!"/secure/master"->query_lord(geteuid(previous_object())))
            return 0
            if (!str || sscanf(str, "%s %d %s", name, tim, reason) != 3) {
            notify_fail("Syntax: suspend <name> <time> <reason>\nWhere time is in hours.\n")
            return 0


    def do_unsuspend(self, str: str) -> int:
            if (this_player() != this_player(1))
            return 0
            if (!"/secure/master"->query_lord(geteuid(previous_object())))
            return 0
            notify_fail("We failed!\n")
            if (!"/secure/bastards"->unsuspend_person(str))
            return 0
            write(str+" unsuspended.\n")
            return 1



class Site_control(MudObject):
