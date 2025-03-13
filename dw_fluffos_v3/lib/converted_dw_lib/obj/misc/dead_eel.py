# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/dead_eel.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            {
            set_name( "eel" )
            set_short( "dead eel" )
            add_alias( ["corpse", "eel corpse"] )
            add_adjective( "dead" )
            set_main_plural( "dead eels" )
            set_long( function()
            {
            if( skinned )
            return
            "This is the dead body of an unfortunate eel.  "
            "As if being dead wasn't bad enough, it has also "
            "been skinned.\n"
            return
            "This is the dead body of an unfortunate eel.  "
            "Most people skin such a fish before eating it.\n"
            } )
            set_weight( 60 )
            set_value( 200 )
            set_weight_per_bite( 2 )


    def init(self, ) -> None:
            {
            ::init()
            this_player()->add_command( "skin", self,
            "<direct:object:me-here> with <indirect:object:me>" )


    def test_sharp(self, weapon: MudObject) -> int:
            {
            int i
            mixed *pongo
            pongo = weapon.weapon_attacks()
            for( i = 1; i < sizeof( pongo ); i++ )
            {
            if( pongo[i] == "sharp" ) return 1


    def query_dynamic_auto_load(self, ) -> Any:
            return ([ "::" : ::query_dynamic_auto_load(),
            "skinned" : skinned ])


    def init_dynamic_arg(self, arg: Any, object) -> None:
            ::init_dynamic_arg(arg["::"])
            skinned = arg["skinned"]



class Dead_eel(MudObject):
