# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/room/transport_start.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_long("A room with bunches of horses and camels milling around in "
            "chunks.  You think you have never seen quite so many "
            "transport animals ever before.\n")
            set_short("transport start")


    def player_quitting(self, player: MudObject, place: MudObject) -> None:
            tell_creator( "goldenthread", "adding property with player %O and place "
            "%O with environment %O\n", player, place,
            environment( place ) )
            player->add_property( TRANSPORT_LOCATION,
            find_start_pos( player, environment( place ) ), 180 )


    def event_enter(self, ob: MudObject) -> None:
            string location
            location = ob.query_property( TRANSPORT_LOCATION )
            tell_creator("goldenthread", "location: %s\n", location )
            if ( !location ) {
            location = ob.query_start_pos()



class Transport_start(MudObject):
