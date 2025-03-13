# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/beeswax_candle.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "candle" )
            set_short( "beeswax candle" )
            add_adjective( "beeswax" )
            set_long( "This is a small candle, like you'd "
            "see on a birthday cake.  It is quite soft and "
            "squidgy.\n" )
            set_fuel_messages( ({
            "It is almost burnt to a stub.", 10,
            "It is more than halfway burnt.", 50,
            "It is not yet halfway burnt.", 85,
            "It is almost new.", 99,
            "It is new.", 100
            }) )
            set_empty_mess( "is burnt to a stub." )
            set_max_fuel( 900 )
            set_fuel( 900 )
            set_brightness( 60 )
            set_value( 400 )
            set_hold_required( 1 )
            add_property( "no recycling", 1 )
            new_weapon( 10 )
            set_weight( 1 )
            set_hide_cond( 1 )



class Beeswax_candle(MudObject):
