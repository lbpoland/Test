# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/playerinfo.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def do_report(self, player: str, event: str, lastn: int, interleaved: int) -> int:
            string who = this_player()->expand_nickname( lower_case(player) )
            string ret
            if( !PLAYER_HANDLER.test_user(who) ) {
            tell_object( this_player(), "%^RED%^%^BOLD%^NOTE: %^RESET%^"
            "This is a player that either "
            "never existed or no longer exists.  Some deleted players' "
            "dossiers remain, while others do not.\n" )


    def list_events(self, ) -> int:
            string * list
            string event, myself, result
            list = sort_array( PLAYERINFO_HANDLER.query_events(), 1 )
            myself = base_name(self)
            result = ""
            foreach( event in list )
            result += ( event == list[0] ) ? event : ( ", " + event )
            write( "The following events exist: " + result + ". \n" )
            list = filter( list,
            (: PLAYERINFO_HANDLER.query_source_ok( $1, $(myself) ) :) )
            write( "You can manually add the following events: "
            + query_multiple_short(list) + ". \n" )
            return 1


    def update_database(self, comment: str, : str) -> None:
            if( !comment )
            return
            if( PLAYERINFO_HANDLER.add_entry( this_player(), data[0], data[1],
            comment + "\n" ) ) {
            write( capitalize( data[0] ) + "'s dossier updated.\n" )
            } else {
            write( "Cannot update " + capitalize( data[0] ) + "'s dossier.\n" )


    def do_acknowledge(self, player: str, event: str, idx: int, update: str) -> int:
            if( !(PLAYERINFO_HANDLER.is_alert( player, idx ) ) ) {
            add_failed_mess( "That event is not an alert, so cannot be "
            "acknowledged.\n" )
            return -1


    def list_alerts(self, foo: int) -> int:
            string * names
            if( foo )
            names = PLAYERINFO_HANDLER.query_online_alerts()
            else
            names = keys( PLAYERINFO_HANDLER.query_alerts() )
            if( !sizeof( names ) )
            write( "There are no players with unacknowledged alerts.\n" )
            else
            write( "The following players have unacknowledged alerts: "
            + query_multiple_short( names ) + ". (" + sizeof( names ) +
            ")\n" )
            return 1


    def add_event(self, player: str, event: str, comment: str) -> int:
            string *events
            string myself
            player = this_player()->expand_nickname( lower_case(player) )
            event = lower_case(event)
            if( !PLAYER_HANDLER.test_user(player) ) {
            add_failed_mess( "No such player: " + player + ".\n" )
            return 0


    def add_alts(self, s1: str, s2: str, deleting: int) -> int:
            string who, result
            string * alts
            who = this_player()->expand_nickname( lower_case(s1) )
            alts = explode( lower_case(s2), " " )
            alts = explode( implode( alts, "," ), "," ) - [""] - [0]
            if( deleting ) {
            result = PLAYERINFO_HANDLER.delete_alts( this_player(), who, alts )
            } else {
            result = PLAYERINFO_HANDLER.add_alts( this_player(), who, alts )



class Playerinfo(MudObject):
