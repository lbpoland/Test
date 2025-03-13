# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/fungi/fire_mushroom.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_adjs( "red stalked" )
            set_type( "mushroom" )
            set_extra( "It seems to be gently smoking." )
            set_messages( ({
            "A small $type$ pushes up through the soil.\n",
            "The $type$ seems to be a bit larger now.\n",
            "The $type$ looks nice and large now.\n",
            "The $type$ swells and suddenly releases a cloud of smoke.\n",
            "There is a flash at the base of the $type$ and with a small roar, it "+
            "rockets into the sky.\n"
            }) )


    def next_stage(self, ) -> None:
            if ( stage == 8 )
            add_eat_effect( "/std/effects/ingested/basic_charging", 20 +
            random( 11 ) )
            ::next_stage()


    def query_charging_power(self, ) -> int:
            int denominator, numerator, wholes
            mapping eat_effects
            eat_effects = query_eat_effects()
            if ( !query_continuous() )
            return eat_effects[ "/std/effects/ingested/basic_charging" ] *
            (int)self.query_weight()
            denominator = query_weight_unit()[ 1 ]
            numerator = eat_effects[ "/std/effects/ingested/basic_charging" ] *
            query_amount() * query_weight_unit()[ 0 ]
            wholes = numerator / denominator
            numerator %= denominator
            if ( random( denominator ) < numerator )
            wholes++
            return wholes



class Fire_mushroom(MudObject):
