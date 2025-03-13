# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/basic/theft_callback.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def add_theft_callback(self, func_name: str, path: str) -> int:
            class theft_callback temp = new( class theft_callback, func_name: func_name,
            path: path )
            if ( !stringp( func_name ) || !stringp( path ) )
            return -1
            debug_printf( "Added theft callback: %s %s.\n", func_name, path )
            calls += [temp]
            return sizeof( calls ) - 1


    def remove_theft_callback(self, id: int) -> int:
            if ( id >= sizeof( calls ) || id < 0 )
            return -1
            debug_printf( "Deleting callback: %s %s.\n", calls[id]->func_name,
            calls[id]->path )
            calls -= [calls[id]]
            return 1


    def query_theft_callbacks(self, ) -> str:
            string ret = ""
            int count = 0
            if ( !sizeof( calls ) )
            return "No theft callbacks found!\n"
            foreach( class theft_callback temp in calls ) {
            ret += sprintf( "%d. %s: %s.\n", count, temp->func_name, temp->path )
            count++



class Theft_callback(MudObject):
