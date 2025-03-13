# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/wallpaper_glue.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("glue")
            set_short("pot of wallpapering glue")
            add_adjective( ["pot", "of", "wallpapering", "wallpaper"] )
            add_alias("pot")
            add_plural("pots")
            set_max_volume(VOLUME)
            set_long("This is a small pot of wallpapering glue, essential "
            "for anybody who's going to be doing anything involving "
            "sticking paper to walls or playing mean tricks on their "
            "friends.\n")
            set_value(480)
            set_closed()


    def add_glue(self, ) -> MudObject:
            object glue
            glue = clone_object( "/obj/reagents/generic_liquid.ob" )
            glue.set_name( "glue" )
            glue.set_short( "sticky white wallpapering glue" )
            glue->add_adjective( ["sticky", "white", "wallpapering",
            "wallpaper" ])
            glue.set_amount( VOLUME )
            glue.set_continuous()
            glue->set_long( "This is some thick and gloopy wallpapering glue.  "
            "Along with some wallpaper and a brush, you could probably "
            "do some fine home decorating.\n")
            glue.set_pile_name( "puddle" )
            glue.add_eat_effect( "/std/effects/ingested/poison", 10 )
            glue.move( self )
            return glue



class Wallpaper_glue(MudObject):
