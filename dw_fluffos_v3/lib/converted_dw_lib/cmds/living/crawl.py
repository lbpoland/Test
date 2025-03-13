# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/living/crawl.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def is_in_water(self, room: MudObject) -> int:
            varargs int cmd( string str ) {
            if( str == "stop" ) {
            if( !this_player()->query_crawling() ) {
            this_player()->add_failed_mess( self,
            "You should be crawling first in order"
            " to stop doing it, don't you "
            "think?\n",
            [}) )
            return 0
            this_player()->stop_crawling()
            return 1
            if( !str ) {
            if( this_player()->query_property( "dead" ) ) {
            this_player()->add_failed_mess( self,
            "You appear to be dead.  There is no "
            "necessity to torture your morphogenic"
            " arms, you know?\n",
            [}) )
            return 0
            } else if( this_player()->query_crawling() ) {
            this_player()->add_failed_mess( self,
            "You are already crawling.\n",
            [}) )
            return 0
            } else if( is_in_water( environment( this_player() ) ) ) {
            this_player()->add_failed_mess( self,
            "You are in water at the moment, so "
            "crawling is impossible.\n",
            [}) )
            return 0
            } else {
            this_player()->add_effect( EFFECTPATH + "crawling" )
            return 1


    def is_in_water(self, room: MudObject) -> int:
            if( inherits( "/std/water_inside.c", room ) ||
            inherits("/std/water_outside.c", room ) ||
            inherits("/std/uwater.c", room ) ) {
            return 1
            } else
            return 0



class Crawl(MudObject):
