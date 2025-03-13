# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/make.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._snow_creatures = sort_array( _snow_creatures, 1 )


    def is_snowing(self, player: MudObject, str: str) -> int:
            object env
            int *co_ords
            env = environment(player)
            if ((string)env.query_property("location") == "inside") {
            add_failed_mess("You must be outside to make a " + str + ".\n")
            return 0


    def cmd(self, str: str) -> Any:
            object ob
            object env
            env = environment(TP)
            switch (str) {
            case "snowball" :
            if (is_snowing(TP, str)) {
            ob = clone_object("/std/environ/snowball")
            if (ob.move(TP) != MOVE_OK) {
            add_succeeded_mess(["$N try to make a snowball, but you cannot "
            "pick it up so it disintergrates in "
            "disinterest.\n",
            "$N tries to make a snowball, but they cannot "
            "pick it up.\n"])
            } else {
            add_succeeded_mess(({
            "$N $V a lovely big snowball.  Have fun with it ;)\n",
            "$N $V a lovely big snowball.\n"])



class Make(MudObject):

    _snow_creatures = 'sort_array( _snow_creatures, 1 )'
