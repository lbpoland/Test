# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shadows/npc/vampirebite_shadow.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def vamp_corpse(self, corpse: MudObject) -> MudObject:
            string player_name
            if( corpse && objectp( corpse )
            && !corpse.query_property( "vampire corpse" )
            && corpse.query_race_name() == "human" ) {
            corpse.add_property( "no burial", 1 )
            corpse.add_property( "vampire corpse", 1 )
            if( stringp( player.query_property( "determinate" ) ) )
            player_name = player.query_property( "determinate" ) +
            player.query_short()
            else
            player_name =
            "/global/events"->convert_message( player.a_short() )
            corpse->add_effect( "/std/effects/npc/vampirecorpse_effect",
            [player_name, copy( player.query_gender() ),
            copy( player.query_level() ), 0] )


    def make_corpse(self, ) -> MudObject:
            object corpse
            corpse = player.make_corpse()
            vamp_corpse( corpse )
            return corpse



class Vampirebite_shadow(MudObject):
