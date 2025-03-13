# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/lord/dom_ain.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def list(self, arg: str) -> int:
            int i, num, cols
            string *members, *domains, mast
            if (this_player() != this_player(1))
            return 0
            domains = get_dir("/d/")
            if(!sizeof(domains)) {
            notify_fail("No domains exist.\n")
            return 0


    def add_creator(self, cre: str, dom: str) -> int:
            string mast
            if (this_player() != this_player(1))
            return 0
            if(file_size("/d/" + dom) != -2) {
            notify_fail("No such domain as " + dom + ".\n")
            return 0


    def delete_creator(self, cre: str, dom: str) -> int:
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


    def do_info(self, ) -> int:
            string *creators,
            *domains,
            *mem,
            *cre_not,
            bit
            mapping no_dir, not_creator
            int i, j, cols
            cols = (int)this_player()->query_cols()
            creators = get_dir("/w/")
            domains = "/secure/master"->query_domains()
            no_dir = ([ ])
            not_creator = ([ ])
            cre_not = [})
            for (i=0;i<sizeof(creators);i++)
            if (file_size("/w/"+creators[i]) != -2) {
            creators = delete(creators, i, 1)
            i--
            } else if (!PLAYER_HANDLER.test_creator(creators[i])) {
            cre_not += [creators[i]]
            creators = delete(creators, i, 1)
            i--


    def detailed_info(self, name: str, option: str) -> int:
            string ret, *members
            int i, cols
            if("/secure/master"->query_domains(.index(name) if name in "/secure/master"->query_domains( else -1) == -1)
            return notify_fail("No such domain: " + name + "\n")
            cols = this_player()->query_cols()
            master = "/d/"+name+"/master"
            write(master+"\n")
            members = master.query_members()
            switch (option[0..0]) {
            case "n":
            members = sort_array(members, 1)
            break
            case "p":
            members = sort_array(members,
            (: strcmp(master.query_project($1),
            master.query_project($2)) :))
            break
            case "l":
            members = sort_array(members,
            (:PLAYER_HANDLER.test_last($2) -
            PLAYER_HANDLER.test_last($1):))
            break


    def get_last_log(self, last_log_on: int) -> str:
            string retval
            int tmp_time, sec, min, hour, day
            tmp_time = time()-last_log_on
            if (!tmp_time) {
            sec = min = hour = day = 0



class Dom_ain(MudObject):
