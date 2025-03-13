# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/oddsnends/small_keyring.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("keyring")
            set_short("small keyring")
            set_main_plural("small keyrings")
            add_adjective( "small" )
            set_long("This is a small keyring, suitable for holding a few "
            "small keys.\n" )
            set_weight(1)
            set_max_weight( 10 )
            set_value( 200 )



class Small_keyring(MudObject):
