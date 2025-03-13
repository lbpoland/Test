# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/rings/high_gp_ring.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "ring" )
            set_short( "pink crystal ring" )
            add_adjective( ["pink", "crystal"] )
            set_main_plural( "pink crystal rings" )
            set_long( "The ring is a single piece of $material$, cut and polished "+
            "until its facets sparkle in the light.\n" )
            set_material( "rosy-quartz" )
            set_value( 750 )
            set_value_info( "artifact", 15000 )
            set_weight( 1 )
            set_enchant( 5 )
            add_property( "artifact form", ([
            "ring of power" : 6
            ]) )
            adjust_charges( 1 + random( 11 ) )
            set_level( 75 )
            set_zapper( file_name( self ) )


    def zap(self, dummy: MudObject, person: MudObject, ring: MudObject) -> None:
            await  person.send("You feel slightly more powerful.\n" )
            if ( ( (string)person.query_gp() + GP_AWARD ) >
            (string)person.query_max_gp() ) {
            person.set_gp( person->query_max_gp() )
            return


    def failed_zap(self, dummy: MudObject, person: MudObject, ring: MudObject) -> int:
            await  person.send("You feel slightly less powerful.\n" )
            person.add_succeeded_mess( ring, "$N $V $D.\n", [}) )
            if ( person.query_gp() < ( GP_AWARD / 3 ) ) {
            person.set_gp( 0 )
            return 1



class High_gp_ring(MudObject):
