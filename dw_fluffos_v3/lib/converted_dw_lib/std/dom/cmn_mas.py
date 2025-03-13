# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/dom/cmn_mas.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def __init__(self):


    def init(self, ) -> None:
            ::init()
            add_command("list", "<word'domain'>", (:do_list($4[0]):))
            add_command("list", "", (:do_list(0):))
            add_command("add", "<word'creator'>", (:add_creator($4[0]):))
            add_command("delete", "<word'creator'>" ,(:delete_creator($4[0]):))
            add_command("project", "<word'name'> <string'project'>",
            (:set_project($4[0], $4[1]):))


    def do_list(self, arg: str) -> int:
            string *domains, mast, s = ""
            string *members
            int i, j
            if(arg == "all")
            domains = get_dir("/d/")
            else if(!arg)
            domains = [_dom_name]
            else {
            domains = [arg]


    def add_creator(self, arg: str) -> int:
            string mast
            arg = (string)this_player()->expand_nickname(arg)
            mast = "/d/" + _dom_name + "/master"
            if((string)mast.query_lord() != geteuid(this_player())) {
            this_player()->add_failed_mess(self, "You are not the Lord of "
            "this Domain.\n", [}))
            return 0


    def delete_creator(self, arg: str) -> int:
            string mast
            arg = (string)this_player()->expand_nickname(arg)
            mast = "d/" + _dom_name + "/master"
            if((string)mast.query_lord() != geteuid(this_player())) {
            this_player()->add_failed_mess(self, "You are not the Lord of "
            "this Domain.\n", [}))
            return 0


    def set_project(self, arg: str, project: str) -> int:
            {
            string mast
            mast = "d/" + _dom_name + "/master"
            if((string)mast.query_lord() != geteuid(this_player())) {
            this_player()->add_failed_mess(self, "You are not the Lord of "
            "this Domain.\n", [}))
            return 0



class Cmn_mas(MudObject):
