# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/monster/cockroach.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("cockroach")
            set_short("cockroach")
            set_race("cockroach")
            set_level( random( 1 + random( 3 ) ) )
            set_main_plural("cockroaches")
            add_alias( "roach" )
            add_plural( "roaches" )
            add_adjective("dirty")
            set_long("This is a huge dirty great big cockroach, the size of your "
            "hand at least.  It waves it feelers at you and looks "
            "horrible and black.  Not only can cockroaches survive "
            "a nuclear blast, they can survive in Waterdeep!\n")
            load_chat( 5, ({
            10, ":scuttles around a bit.",
            10, ":cleans its feelers.",
            10, ":rushes around in circles.",
            1,  ":jerks off in a strange direction.",
            }) )
            set_wimpy( 30 )
            load_a_chat( 50, ({
            1, ":oozes horrible white stuff.",
            1, ":makes a sort of scraping noise."
            }) )



class Cockroach(MudObject):
