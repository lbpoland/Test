# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/t_ell.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, arg: str, thing: Any, silent: int) -> int:
            class message mess
            string words,
            word
            string them_mess,
            extra
            string *ok_string
            string *prop
            object *obs
            object *net_dead
            object *multiple_earmuffed
            object *cannot_see
            object *ok
            object *fail
            object *earmuffed
            object *roleplaying
            mixed busy
            if (pointerp(thing)) {
            words = arg
            thing -= [0]
            if (TP && environment(TP) &&
            function_exists("trap_tell", environment(TP)) &&
            previous_object(-1.index(self) if self in previous_object(-1 else -1) == -1) {
            return (int) environment(TP)->trap_tell(words, thing, 0)


    def reply_cmd(self, mess: str) -> int:
            string *rep
            object *obs
            rep = this_player()->query_tell_reply_list()
            if (!rep) {
            add_failed_mess
            ("No one has told you anything in the last 15 minutes.\n")
            return 0


    def replylock_cmd(self, names: str) -> int:
            string *rest
            string *rep
            rep = uniq_array(explode(names, ","))
            rep = map(rep, (: this_player()->expand_nickname($1) :))
            rest = filter(rep, (: $1 && find_player($1) && interactive(find_player($1)) :))
            if(!sizeof(rest)) {
            add_failed_mess("None of " + query_multiple_short(rep, 0, 1, 0, 0) +
            " are logged in.  You cannot lock onto someone who is "
            "not here.\n")
            return 0


    def replylockremove_cmd(self, ) -> int:
            this_player()->set_tell_reply_list(0)
            add_succeeded_mess(["You remove any possible reply locks.\n", ""])
            return 1



class T_ell(MudObject):
