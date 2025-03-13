# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/pe_ople.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def num_sort(self, first: MudObject, second: MudObject) -> int:
            int one, two
            one = first.query_level()
            two = second.query_level()
            if(one < two)
            return 1
            if(one > two)
            return -1
            return 0


    def guild_sort(self, first: MudObject, second: MudObject) -> int:
            object g1, g2
            g1 = first.query_class_ob()
            g2 = second.query_class_ob()
            return strcmp(g1 ? g1.query_name() : "",
            g2 ? g2.query_name() : "")


    def domain_sort(self, first: MudObject, second: MudObject) -> int:
            object d1, d2
            d1 = environment(first)
            d2 = environment(second)
            return strcmp(d1 ? file_name(d1) : "", d2 ? file_name(d2) : "")


    def age_sort(self, first: MudObject, second: MudObject) -> int:
            int one, two
            one = first.query_time_on()
            two = second.query_time_on()
            if(one < two)
            return -1
            if(one > two)
            return 1
            return 0


    def cmd(self, str: str) -> Any:
            mixed *stuff
            string bit, *bits
            function sort_func
            stuff = this_player()->query_property("people list")
            if (!stuff)
            stuff = P_DEFAULT
            if(str) {
            bits = explode(str, " ")
            str = 0
            foreach(bit in bits) {
            switch(bit) {
            case "-l":
            sort_func = (: num_sort :)
            break
            case "-g":
            sort_func = (: class_sort :)
            break
            case "-a":
            sort_func = (: age_sort :)
            break
            case "-d":
            sort_func = (: domain_sort :)
            break
            default:
            if(str)
            str += " " + bit
            else
            str = bit



class Pe_ople(MudObject):
