# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/golem_shard.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "shard" )
            set_short( "cracked clay shard" )
            add_adjective( ({"clay"}) )
            set_long( "This is a heavily cracked clay shard." )
            set_main_plural( "cracked clay shards" )
            set_weight( 5 )
            set_value( 0 )
            add_property( "no recycling", 1 )



class Golem_shard(MudObject):
