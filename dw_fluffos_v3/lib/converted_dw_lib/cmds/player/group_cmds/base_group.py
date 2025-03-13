# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/group_cmds/base_group.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._commands = ([ ])


    def query_group_sub_command_amount(self, ) -> int:
            return sizeof( _commands )


    def set_membership_required(self, verb: str, pattern: str, flag: int) -> int:
            mixed *dummy
            string key
            if( !_commands[ verb ] ) {
            return 0


    def set_leadership_required(self, verb: str, pattern: str, flag: int) -> int:
            mixed *dummy
            string key
            if( !_commands[ verb ] ) {
            return 0



class Base_group(MudObject):

    _commands = '([ ])'
