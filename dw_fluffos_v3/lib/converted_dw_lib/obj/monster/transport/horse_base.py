# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/monster/transport/horse_base.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def set_quiet(self, quiet: int) -> None:
            _quiet = quiet


    def query_quiet(self, ) -> int:
            return _quiet


    def hear_name(self, player: MudObject, mess: str) -> None:
            string *bits
            string str
            int allowed
            if ( !player ) {
            return


    def setup_responses(self, ) -> None:
            add_respond_to_with( explode(
            lower_case( query_transport_base_name() ), " " ),
            (: hear_name :) )
            BROADCASTER.npc_hear_shouts( self )


    def init_dynamic_arg(self, map: Any, ob: MudObject) -> None:
            ::init_dynamic_arg( map["::"] )
            if ( map["quiet"] ) {
            set_quiet( map["quiet"] )


    def do_name(self, name: str) -> int:
            if ( ::do_name( name ) ) {
            setup_responses()
            return 1



class Horse_base(MudObject):
