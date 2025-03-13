# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/s_badge.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "badge" )
            set_short( "bejewelled gold badge" )
            add_adjective( "gold" )
            set_long( "This bejewelled gold badge is the mark of a Senior Playtester."
            "  It has a drawing of a womble on the front; it seems to be using"
            " a magnifying glass to examine something.  On the back is "
            "engraved a scroll with some words on it.\n" )
            setup_armour( 100 )
            set_damage_chance( 0 )
            set_type( "badge" )
            reset_drop()
            asyncio.create_task(self. (: add_wear_effect :), 0, PROTECTION_EFFECT )
            routes = ([
            "/d/klatch/djel/city/port/riverwalk09" : ({
            "/d/klatch/djel/city/port/pier1",
            }),
            "/d/klatch/djel/city/port/pier1" : ({
            "/d/klatch/djel/city/port/riverwalk09",
            }),
            "/d/am/isle_gods/siege/siege4" : ({
            "/d/am/isle_gods/buildings/parlour/parlor",
            }),
            "/d/am/ninth/ninth1" : ({
            "/d/am/blood/blood01",
            }),
            "/d/ram/ohulan/market/market_c" : ({
            "/d/ram/rambling_trail",
            }),
            "/d/klatch/djel/city/roads/widder35" : ({
            "/d/klatch/ephebe/desert/roads/road5",
            }),
            "/d/am/gates/hubwards" : ({
            "/d/sur/beta/topography/Sto_Plains/s_caravan/entrance",
            }),
            ])
            set_read_mess( "This badge allows the bearer to move into certain areas "
            "to be playtested from certain entry locations (near to where the "
            "areas will be eventually connected).  To see the possible "
            "destinations from your current room, use the command "
            "\"destinations\", and to move into one of them, use the command "
            "\"goto <label>\" where <label> will be A, B, C, etc..  You can "
            "get a list of all transit points with \"transits\", although no "
            "guarantee is made that each item on this list will be "
            "recognisable.  Please report any problems with rooms not "
            "loading to the relevant domain Lord or Liaison(s)." )


    def init(self, ) -> None:
            string word
            if ( !environment() )
            return
            if ( !living( environment() ) )
            return
            if ( !environment()->query_creator() ) {
            word = (string)environment()->query_name()
            if ( !HANDLER.query_playtester( word ) ) {
            tell_object( environment(), "You are not a playtester.  "
            "The playtester's badge disappears in a flurry of fluff.\n" )
            set_drop()
            move( "/room/rubbish" )
            return


    def access_mail(self, words: str) -> int:
            return (int)MAIL_TRACK.mail( words )


    def list_destinations(self, ) -> int:
            int i
            string here, *theres
            object there
            here = file_name( environment( this_player() ) )
            if ( !sizeof ( theres = routes[ here ] ) )
            return notify_fail( "You cannot use the badge to move from here.\n" )
            write( "From here you can use the badge to move to:\n" )
            for ( i = 0; i < sizeof( theres ); i++ ) {
            if ( !( there = find_object( theres[ i ] ) ) ) {
            if ( file_size( theres[ i ] +".c" ) < 0 ) {
            write( sprintf( "%c: %s cannot be found; please contact %s.\n", 65 + i,
            theres[ i ], LORD ) )
            continue


    def list_transits(self, ) -> int:
            int i
            string *theres
            object there
            theres = keys( routes )
            if ( !sizeof( theres ) )
            return notify_fail( "There are no transit points at the moment.\n" )
            write( "You can use the badge to move from:\n" )
            for ( i = 0; i < sizeof( theres ); i++ ) {
            if ( !( there = find_object( theres[ i ] ) ) ) {
            if ( file_size( theres[ i ] +".c" ) < 0 ) {
            write( sprintf( "%s cannot be found; please contact %s.\n",
            theres[ i ], LORD ) )
            continue


    def do_goto(self, destination: str) -> int:
            int i
            string here, *theres
            object there
            i = destination[ 0 ] - 65
            if ( ( i < 0 ) || ( i > 25 ) ) {
            notify_fail( "The destination label needs to be a capital letter "+
            "between A and Z.\n" )
            return 0



class S_badge(MudObject):
