# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/global/command.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.current_verb = ""
            self.SearchPath = ['DIR_LIVING_CMDS']


    def query_current_cmd(self, ) -> str:
            protected int cmdAll(string args) {
            class command verb
            mixed tmp
            verb = new(class command)
            verb->args = args
            current_cmd = args
            if( !((int)CMD_D.GetCommand(verb, SearchPath)) ) {
            return 0


    def eventForce(self, cmd: str) -> int:
            string err
            int res
            if(member_array(call_stack(0)[1],
            [ "/cmds/creator/show_help.c",
            "/d/am/broad_way/cryer_order.c",
            "/obj/handlers/new_soul.c",
            "/std/living/force.c"
            })) == -1)
            error("illegal force")
            Forced = 1
            err = catch(res = command(cmd))
            Forced = 0
            if(err) error(err)
            return res



class Command(MudObject):

    current_verb = '""'

    SearchPath = "['DIR_LIVING_CMDS']"
