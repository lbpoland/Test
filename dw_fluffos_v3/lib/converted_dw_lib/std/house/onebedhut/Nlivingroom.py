# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/house/onebedhut/Nlivingroom.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_light(50)
            set_theft_handler( HOSPITAL )
            set_save_file("%savedir%/%N%livingroom")
            set_orientation(%orientation%)
            set_quit_handler(%out%)
            set_short("livingroom")
            set_base_desc("a small cramped livingroom")
            add_surface("floor", "stone paving" )
            add_surface("ceiling", "roughly finished wood" )
            add_surface("%0% wall", "roughly finished wood" )
            add_surface("%2% wall", "roughly finished wood" )
            add_surface("%4% wall", "roughly finished wood" )
            add_surface("%6% wall", "roughly finished wood" )
            add_exit("out", %out%, "door")
            modify_exit("out", ({"door short", "front door",
            "exit mess", "$N leaves the hut.",
            "closed", 1,
            "enter mess",
            [1,
            "$N enters from a hut.",
            "$N enter from a hut."
            }),
            }) )
            add_exit("%0%", PATH+"%N%bed", "door")
            modify_exit("%0%", ({"door short", "bedroom door"}))



class Nlivingroom(MudObject):
