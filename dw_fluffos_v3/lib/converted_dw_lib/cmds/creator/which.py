# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/which.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> int:
            int i
            mixed *junk, *coms
            class command cmd
            string file, *files
            files = [})
            junk = actions_defined(this_player(), 0, 12)
            for (i = 0; i < sizeof(junk); i += 2) {
            if (junk[i] == str) {
            file = function_exists((string)junk[i+1][1], (object)junk[i+1][0])
            if (!file) {
            file = base_name((object)junk[i+1][0])


    def command_list(self, ) -> int:
            mapping objects
            mapping data = ([ ])
            string *dkeys
            string command
            int maxlen = 8
            int width = 0
            string txt
            objects = this_player()->query_p_objects()
            foreach( object ob, string *commands in objects ) {
            foreach( command in commands ) {
            if ( data[ command ] ) {
            data[ command ] += [ob]



class Which(MudObject):
