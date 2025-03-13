# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/rings/invisibility.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "ring" )
            set_short( "clear crystal ring" )
            add_adjective( ["clear", "crystal"] )
            set_main_plural( "clear crystal rings" )
            set_long( "The ring is made from a colourless stone that seems to refract "+
            "light in a strange way.  The outer edge has eight sides.\n" )
            set_material( "calcite" )
            set_value( 200 )
            set_value_info( "artifact", 5000 )
            set_weight( 1 )
            set_enchant( 2 )
            add_property( "no recycling", 1 )
            add_property( "fluff'n'stuff", 1 )
            add_property( "artifact form", ([
            "ring of invisibility" : 2
            ]) )
            adjust_charges( 1 + random( 7 ) )
            set_level( 60 )
            set_zapper( file_name( self ) )


    def zap(self, dummy: MudObject, person: MudObject, ring: MudObject) -> None:
            person->add_effect( "/std/effects/magic/invisibility",
            roll_MdN( 7, (int)ring.query_level() ) )



class Invisibility(MudObject):
