# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/house/fourbedhouse/Nlanding2.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_light(50)
            set_theft_handler( HOSPITAL )
            set_save_file("%savedir%/flat%N%bed")
            set_orientation(%orientation%)
            set_quit_handler(%out%)
            set_short("hallway")
            set_base_desc( "a hallway" )
            add_surface( "floor", "finished pine board" )
            add_surface( "ceiling", "plain plaster" )
            add_surface( "%0% wall", "plain plaster" )
            add_surface( "%2% wall", "plain plaster" )
            add_surface( "%4% wall", "plain plaster" )
            add_exit( "%0%", PATH +"%N%bed4", "door" )
            modify_exit("%0%", ["door short", "bedroom door"])
            add_exit( "%4%", PATH +"%N%bed3", "door" )
            modify_exit("%4%", ["door short", "bedroom door"])
            add_exit( "%6%", PATH +"%N%landing1", "corridor" )



class Nlanding2(MudObject):
