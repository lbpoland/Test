# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/global/nickname.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def nickname_commands(self, ) -> None:


    def expand_nickname(self, phrase: str) -> str:
            int i
            string new_n, *words
            if ( stringp( phrase ) )
            words = explode( phrase, " " )
            else
            return phrase
            if ( !map_nicknames )
            map_nicknames = ([ ])
            for ( i = 0; i < sizeof( words ); i++ ) {
            new_n = map_nicknames[ lower_case( words[ i ] ) ]
            if ( new_n )
            words[ i ] = new_n



class Nickname(MudObject):
