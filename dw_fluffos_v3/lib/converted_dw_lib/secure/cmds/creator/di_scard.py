# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/cmds/creator/di_scard.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> Any:
            string *file_names, err
            object *no_dis, discard_obj
            file_names = this_player()->get_cfiles(str)
            no_dis = [})
            if (!sizeof(file_names)) {
            add_failed_mess("No such object: " + str + "\n")
            return 0


    def ask_discard(self, obs: MudObject) -> None:
            if (!arrayp(obs) || !sizeof(obs)) {
            printf("Nothing left to be discarded.\n")
            return


    def no_discard(self, s: str, obs: MudObject) -> None:
            string err, name
            name = (string)WIZ_PRESENT.desc_object(obs[0])
            if (this_player()->affirmative(s)) {
            err = catch(obs[0]->dwep())
            this_player()->handle_error(err, "DWEP")
            if (obs[0]) {
            printf("%s REALLY doesn't want to be discarded.\n", name)
            catch(destruct(obs[0]))
            if (obs[0]) {
            printf("%s didn't destruct.\n", name)
            return



class Di_scard(MudObject):
