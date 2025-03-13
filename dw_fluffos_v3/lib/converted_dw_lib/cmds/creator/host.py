# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/host.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, w: str) -> int:
            string ip = lower_case( this_player()->expand_nickname( w ) )
            string ip2
            if ( find_player( ip ) ) {
            ip2 = query_ip_number( find_player( ip ) )
            lookups[ resolve( ip2, "lookup_callback" ) ] = this_player()
            tell_object( this_player(), "Starting lookup for " + ip +
            " (" + ip2 + ").\n" )
            } else {
            lookups[ resolve( ip, "lookup_callback" ) ] = this_player()
            await  this_player().send("Starting lookup for " + ip + ".\n" )


    def lookup_callback(self, address: str, resolved: str, key: int) -> None:
            if ( lookups[ key ] ) {
            tell_object( lookups[ key ], "Resolved " +
            ( address ? address : "?unknown" ) +
            " to " +
            ( resolved ? resolved : "?unknown" ) + ".\n" )



class Host(MudObject):
