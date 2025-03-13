# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/lord/dinfo.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, name: str, option: str) -> Any:
            if (!name) {
            return notify_fail("You must give a domain.\n")


    def dinfo(self, name: str, cols: int, option: str) -> str:
            string ret, *members
            int i
            if("/secure/master"->query_domains(.index(name) if name in "/secure/master"->query_domains( else -1) == -1)
            return "No such domain: " + name + "\n"
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


    def dest_me(self, ) -> None:
            destruct(self)


    def clean_up(self, ) -> None:
            dest_me()


    def reset(self, ) -> None:
            dest_me()


    def get_last_log(self, last_log_on: int) -> str:
            string retval
            int tmp_time, sec, min, hour, day
            tmp_time = time()-last_log_on
            if (!tmp_time) {
            sec = min = hour = day = 0


    def query_patterns(self, ) -> Any:
            return ({
            "<string'domain'>", (: cmd($4[0], " ") :),
            "<string'domain'> [by] {n|name|p|project|l|login}",
            (: cmd($4[0], $4[1]) :)
            })



class Dinfo(MudObject):
