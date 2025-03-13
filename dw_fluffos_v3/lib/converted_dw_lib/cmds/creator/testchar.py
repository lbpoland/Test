# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/testchar.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, player: MudObject, status: str) -> int:
            foreach( string property, mixed value in properties ) {
            if ( status == "on" ) {
            if ( functionp( value ) ) {
            player->add_property( property, evaluate( value,
            this_player() ) )



class Testchar(MudObject):
