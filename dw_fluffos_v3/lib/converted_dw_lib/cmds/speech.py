# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/speech.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def mangle_tell(self, mess: str, dest: MudObject) -> str:
            int i
            string ret
            if (!TP || !environment(TP))
            return mess
            if (environment(TP)->query_property("reverse_tell") &&
            !dest.query_creator() && !TP.query_creator()) {
            for (i = 0; i < strlen(mess); i++)
            ret = mess[i..i] + ret
            return ret


    def drunk_speech(self, str: str) -> str:
            return replace(str, ["S", "sh", "r", "rr", "ing", "in'", "x", "xsh",
            "S", "SH", "R", "RR"])


    def de_eight(self, arg: str) -> str:
            object g
            string replace_num
            g = (object) TP.query_class_ob()
            if (g && ((string) g.query_name() == "wizards") && !TP.query_creator()) {
            arg = "@ " + arg + "@"
            replace_num = [" seven plus one", " nine minus one",
            " two to the power of three",
            " four times two"][random(4)]
            arg = implode(explode(arg, " eight"), replace_num)
            replace_num = ["(7+1)", "(9-1)", "(2^3)", "(4*2)"][random(4)]
            arg = implode(explode(arg, "8"), replace_num)
            arg = arg[2.. < 2]


    def fix_shorthand(self, mess: str) -> str:
            string *bits, name, value
            mixed *tmp
            int index, i
            bits = explode(mess, " ")
            foreach(name, value in REPLACEMENTS) {
            tmp = regexp(bits, "(^|[^A-Za-z]+)"+name+"($|[^A-Za-z]+)", 1)
            if(sizeof(tmp)) {
            for(i=0; i<sizeof(tmp); i+=2) {
            index = tmp[i+1]-1
            bits[index] = replace(bits[index], name, value)


    def my_mess(self, fish: str, erk: str) -> None:
            int bing
            if (!interactive(TP)) {
            return


    def say_it(self, message: Any) -> int:
            string accent
            if (!environment(TP))
            write("You are in limbo, noone can hear you.\n")
            switch(mess->status) {
            case NO_MESSAGE:
            return notify_fail("Syntax: " + query_verb() + " <something>\n")
            case NOT_SPOKEN:
            return notify_fail(capitalize(mess->language) +
            " is not a spoken language.\n")
            case NOT_KNOWN:
            return notify_fail("You cannot speak " + capitalize(mess->language) + ".\n")


    def say_it_to(self, message: Any, targets: Any, priv: int, event: str) -> int:
            string lstr
            string extra
            string accent
            if (!environment(TP)) {
            write("You are in limbo, noone can hear you.\n")



class Speech(MudObject):
