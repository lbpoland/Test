# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/group_cmds/assist.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def do_assist_list(self, group: str) -> int:
            object *assisting
            assisting = this_player()->query_assisting()
            if( sizeof( assisting ) )
            {
            tell_object( this_player(), "You are currently "
            "assisting " + query_multiple_short( assisting ) +
            ".\n" )
            return 1


    def do_assist(self, member: MudObject, group: str) -> int:
            object *assisting
            assisting = this_player()->query_assisting()
            if( member == this_player() ) {
            return notify_fail( "Don't be stupid.\n" )


    def do_unassist(self, member: MudObject, group: str) -> int:
            if( member == this_player() ) {
            return notify_fail( "Don't be stupid.\n" )


    def query_help_string_for(self, sub: str) -> str:
            return "With this command you can guard a party member.  If the "
            "person you're guarding gets attacked, you will automatically "
            "join the fight after a delay.  The length of the delay depends "
            "on how many people you're guarding at the moment.  Use "
            "\"list\" to see who you are currently assisting.  To stop "
            "assisting someone, use \"party assist <someone>\" again "
            "on that person.\n"



class Assist(MudObject):
