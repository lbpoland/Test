# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/lord/playera_ddproperty.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, player: str, name: str, value: Any) -> Any:
            mixed *args
            string file
            string *bits
            mapping map_prop
            int i, found
            seteuid("Root")
            fname = "/save/players/" + player[0..0] + "/" + player
            map_prop = ([ ])
            if (!PLAYER_HANDLER.test_user(player))
            return notify_fail("Unable to find player "+player+".\n")
            uncompress_file (fname+".o.gz")
            file = unguarded( (: read_file(fname+".o") :))
            if(!file)
            return notify_fail("Error reading player file " + fname + ".\n")
            bits = explode(file, "\n")
            map_prop = ([ ])
            for (i = 0; i < sizeof(bits); i++) {
            if (bits[i][0..strlen(var_name)-1] == var_name) {
            map_prop = restore_variable(bits[i][strlen(var_name) + 0..])
            found = 1
            break



class Playera_ddproperty(MudObject):
