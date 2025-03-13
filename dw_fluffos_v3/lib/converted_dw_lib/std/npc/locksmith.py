# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/npc/locksmith.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from .combat import combat_handler
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def init(self, ) -> None:
            ::init()
            if(interactive(this_player())) {
            this_player()->add_command("hire", self, "<direct>",
            (: do_hire( 0 ) :) )
            this_player()->add_command("hire", self,
            "<direct> to unlock an entire house",
            (: do_hire( 1 ) :) )
            this_player()->add_command("pay", self, "<direct>")
            this_player()->add_command("ask", self,
            "<direct> to {open|unlock} [the] "
            "<word'exit'> door",
            (: do_ask($4[2]) :))
            this_player()->add_command("confirm", self, "")


    def reset(self, ) -> None:
            clear_false_client()


    def event_enter(self, ob: MudObject, message: str, from: MudObject) -> None:
            if(from && environment(ob) == self) {
            if(ob.query_name() == "coin") {
            do_command("sayto " + file_name(from) + " You have to pay me.")
            do_command("give coins to " + file_name(from))
            return


    def finish_opening(self, path: str, env: str) -> None:
            unlock_all( path )
            #ifdef LOGGING
            log_file(LOG,
            "%s: %s successfully got %s to unlock all doors in %s.\n",
            ctime(time()), _client, query_short(), path )
            #endif
            move( env, "$N leaves the house, rubbing " + query_objective() +
            " hands.\n", "" )
            free_for_hire()
            go_back()



class Locksmith(MudObject):
