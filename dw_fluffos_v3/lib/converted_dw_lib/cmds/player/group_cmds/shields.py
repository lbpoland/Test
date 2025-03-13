# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/group_cmds/shields.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def do_shields(self, suggested_members: MudObject, group: str) -> int:
            {
            object cmd_shields, member, *members, *check_for
            string shields, mess, colour
            cmd_shields = load_object( CMD_SHIELDS )
            if( !cmd_shields )
            {
            return notify_fail( "Cannot find the \"shield\" command.  "
            "Please bug report this party command.\n" )


    def query_help_string_for(self, what: str) -> str:
            {
            return "The \"party shields\" command allows you to view "
            "the arcane protection of all or some of your party's "
            "members.  You can either specify no arguments, or "
            "you can include the names of only those members "
            "whose protection you wish to check.\n"



class Shields(MudObject):
