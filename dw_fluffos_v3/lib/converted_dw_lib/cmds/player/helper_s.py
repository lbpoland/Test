# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/helper_s.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, ) -> int:
            object *helpers
            string mess
            helpers = filter( users(), (: !$1.query_creator() &&
            $1.query_property( "newbie helper" ) &&
            !$1.query_login_ob() :) )
            switch( sizeof( helpers ) ) {
            case 0:
            add_failed_mess("There are no newbie helpers logged on at the "
            "moment.\n")
            return 0
            case 1:
            if ( helpers[ 0 ] == this_player() ) {
            mess = "You are the only newbie helper logged on at the "
            "moment.\n"


    def test_helper(self, player_name: str) -> int:
            player_name = lower_case( player_name )
            if ( PLAYER_HANDLER.test_property( player_name, "newbie helper" ) ) {
            this_player()->add_succeeded_mess(self, ({
            capitalize( player_name ) + " is a newbie helper.\n",
            ""}), [}))
            return 1



class Helper_s(MudObject):
