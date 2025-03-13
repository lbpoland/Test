# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/countries.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, ) -> int:
            int left, right, size
            float percentage
            object person, *users
            string suffix, message, country
            mixed *unsorted, *sorted, *data
            mapping countries
            countries = copy( common_countries )
            users = filter( users(), (: $1.query_visible( this_player() ) &&
            !$1.query_property( COUNTRIES_NO_SHOW_PROP ) :) )
            if( !size = sizeof( users ) ) {
            return notify_fail( "No visible players.\n" )


    def resolve_domain_suffix(self, player: MudObject) -> str:
            string addy, *host
            addy = query_ip_name( player )
            if( !addy ) {
            return 0


    def handle_no_show(self, hide: int) -> int:
            switch( hide ) {
            case 1:
            if( this_player()->query_property( COUNTRIES_NO_SHOW_PROP ) ) {
            tell_object( this_player(), "You are already hidden on the "
            "countries list.\n" )
            return 1



class Countries(MudObject):
