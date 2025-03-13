# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/rings/recall.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "ring" )
            set_short( "blue crystal ring" )
            add_adjective( ["blue", "crystal"] )
            set_main_plural( "blue crystal rings" )
            set_long( "The ring is a single piece of $material$, cut and polished "+
            "until its facets sparkle in the light.\n" )
            set_material( "sapphire" )
            set_value( 500 )
            set_value_info( "artifact", 10000 )
            set_weight( 1 )
            set_enchant( 3 )
            add_property( "artifact form", ([
            "ring of recall" : 3
            ]) )
            adjust_charges( 1 + random( 11 ) )
            set_level( 30 )
            set_zapper( file_name( self ) )


    def find_start_location(self, person: MudObject) -> str:
            string pos
            if ( file_name( environment( person ) )[0..19] == "/d/cwc/Bes_Pelargic/" ) {
            return CWC_START_LOCATION


    def zap(self, dummy: MudObject, person: MudObject, ring: MudObject) -> None:
            string place
            place = query_property( "destination" )
            if ( !place ) {
            asyncio.create_task(self. "move_person", 0, person, find_start_location( person ) )


    def failed_zap(self, dummy: MudObject, person: MudObject, ring: MudObject) -> int:
            person.add_succeeded_mess( ring, "$N $V $D, but nothing happens.\n", [}) )
            return 1


    def move_person(self, person: MudObject, place: str) -> None:
            tell_creator( "taffyd", "%O, %s\n", person, place )
            if ( !find_object( place ) )
            place.force_load()
            if ( !find_object( place ) ) {
            tell_object( person, "Please contact a creator and ask that \""+ place +
            "\" be checked.  You are also owed a charge on this ring.\n" )
            return



class Recall(MudObject):
