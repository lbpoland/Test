# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/trace.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, arg: str) -> Any:
            string *args
            int     i, j, trace_arg
            notify_fail( "Usage: trace <" + implode(OPTIONS, "|") + ">\n" )
            if( !arg ) return 0
            args = explode( arg, " " )
            if( !sizeof( args ) )
            return 0
            for( i = 0; i < sizeof( args ); i++ )
            if( (j = OPTIONS .index( args[ i ]) if  args[ i ] in OPTIONS  else -1) != -1 )
            {
            if( !j )
            {
            trace( 0 )
            write( "Trace off.\n" )
            return 1



class Trace(MudObject):
