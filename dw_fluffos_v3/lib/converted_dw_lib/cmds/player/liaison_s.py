# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/liaison_s.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, ) -> Any:
            int i, j
            string *members, *member_alias, *aliases
            object person
            members = (string *)"/d/liaison/master"->query_members()
            aliases = [})
            i = sizeof( members )
            while ( i-- ) {
            person = find_player( members[ i ] )
            if ( ! person ) {
            member_alias = "/d/liaison/master"->member_alias( members[ i ] )
            j = sizeof( member_alias )
            while ( j-- ) {
            if ( find_player( member_alias[ j ] ) ) {
            aliases += [capitalize( member_alias[ j ] ) +"("+
            capitalize( members[ i ] ) +")"]



class Liaison_s(MudObject):
