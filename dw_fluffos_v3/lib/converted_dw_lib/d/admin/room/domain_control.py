# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/admin/room/domain_control.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_light(100)
            set_short("domain-control room")
            add_property("determinate", "the ")
            set_long("You float in nothingness, before a vast turtle, its shell pocked "
            "by asteroid craters. In all directions stars twinkle in the black "
            "curtain of space.\n"
            "Available commands:\n"
            "  list                         : list all domains.\n"
            "  list <domain>                : list members of a domain.\n"
            "  create <domain>              : create a domain (you are lord).\n"
            "  create <domain> <lord>       : create a domain for someone else.\n"
            "  add <creator> <domain>       : add a creator to a domain you own.\n"
            "  delete <creator> <domain>    : remove a creator from a domain you own.\n"
            "  project <cre> <dom> <proj>   : Set the creators project.\n"
            "  deputy <cre> <dom>           : Appoint creator as a deputy.\n"
            "  undeputy <cre> <dom>         : Remove creator as a deputy.\n"
            )
            add_item("turtle", "On its back you can see four elephants, and they bear " +
            "the weight of the disc upon their wide backs.\n")
            add_item("elephants", "The four great elephants labour endlessly in the " +
            "task of turning the disc upon their backs.\n")
            add_item("disc", "The whole discworld, from hub to rim, rides upon the " +
            "elephant's backs.\n")
            add_alias("elephant", "elephants")
            add_exit("north", ROOM+"development", "corridor")
            add_exit("south", ROOM+"site_control", "corridor")
            add_exit("west", ROOM+"access_control", "corridor")
            seteuid("Admin")


    def init(self, ) -> None:
            ::init()
            add_command("list", "", (: do_list_all() :) )
            add_command("list", "<word>", (: do_list($4[0]) :) )
            add_command("create", "<word>", (: do_create($4[0], 0) :) )
            add_command("create", "<word> <word>", (: do_create($4[0], $4[1]) :) )
            add_command("add", "<word> <word>", (: do_add($4[0], $4[1]) :) )
            add_command("delete", "<word> <word>", (: do_delete($4[0], $4[1]) :) )
            add_command("project", "<word> <word> <string>",
            (: do_project($4[0], $4[1], $4[2]) :) )
            add_command("deputy", "<word> <word>", (: do_deputy($4[0], $4[1]) :) )
            add_command("undeputy", "<word> <word>", (: do_undeputy($4[0], $4[1]) :) )


    def do_list_all(self, ) -> int:
            int i, num
            string *members, *domains, mast
            if (this_player() != this_player(1))
            return 0
            domains = "/secure/master"->query_domains()
            if(!sizeof(domains)) {
            notify_fail("No domains exist.\n")
            return 0


    def do_list(self, arg: str) -> int:
            int i, cols
            string *members, *domains, mast
            if (this_player() != this_player(1))
            return 0
            domains = "/secure/master"->query_domains()
            if(!sizeof(domains)) {
            notify_fail("No domains exist.\n")
            return 0


    def do_create(self, dom: str, lord: str) -> int:
            if (this_player() != this_player(1))
            return 0
            if(!MASTER.high_programmer(geteuid(previous_object()))) {
            notify_fail("You lack the Power of Change on this scale!\n")
            return 0


    def do_add(self, cre: str, dom: str) -> int:
            string mast
            if (this_player() != this_player(1))
            return 0
            if(file_size("/d/" + dom) != -2) {
            notify_fail("No such domain as " + dom + ".\n")
            return 0


    def do_delete(self, cre: str, dom: str) -> int:
            string mast
            if (this_player() != this_player(1))
            return 0
            if(file_size("/d/" + dom) != -2) {
            notify_fail("No such domain as " + dom + ".\n")
            return 0


    def do_project(self, cre: str, dom: str, project: str) -> int:
            string mast
            if (this_player() != this_player(1))
            return 0
            if(file_size("/d/" + dom) != -2) {
            notify_fail("No such domain as " + dom + ".\n")
            return 0


    def do_deputy(self, cre: str, dom: str) -> int:
            string mast
            if (this_player() != this_player(1))
            return 0
            if(file_size("/d/" + dom) != -2) {
            notify_fail("No such domain as " + dom + ".\n")
            return 0


    def do_undeputy(self, cre: str, dom: str) -> int:
            string mast
            if (this_player() != this_player(1))
            return 0
            if(file_size("/d/" + dom) != -2) {
            notify_fail("No such domain as " + dom + ".\n")
            return 0



class Domain_control(MudObject):
