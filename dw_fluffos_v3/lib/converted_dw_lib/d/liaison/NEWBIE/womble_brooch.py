# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/liaison/NEWBIE/womble_brooch.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            {
            set_name("brooch")
            add_adjective( ["womble", "brass"] )
            set_short("womble brooch")
            set_long("A brass brooch with a womble engraved "
            "upon it.\n")
            add_alias("jewellery")
            add_plural("jewellery")
            set_type("badge")
            setup_armour(1000)
            set_percentage(100)
            set_damage_chance(0)
            set_weight(2)
            add_property("wombles brooch", 1)
            add_property( "shop type", "jewellers" )



class Womble_brooch(MudObject):
