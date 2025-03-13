# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/perm_it.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, player: MudObject) -> int:
            object *corpses, corpse
            int i
            corpses = filter( children( "/obj/corpse" ),
            (: $1 && $1.query_property("player" ) :) )
            corpses = filter( corpses,
            (: $1 && $1.query_ownership() ==
            $(this_player()->query_name()) :) )
            if( sizeof( corpses ) ) {
            foreach( corpse in corpses ){
            if(corpse.query_permitted(.index(player.query_name()) if player.query_name() in corpse.query_permitted( else -1) != -1) {
            i++
            } else {
            corpse.give_permission( player->query_name() )



class Perm_it(MudObject):
