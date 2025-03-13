# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/house/fourbedhouse/Nlanding1.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_light(50)
            set_theft_handler( HOSPITAL )
            set_save_file("%savedir%/%N%landing1")
            set_orientation(%orientation%)
            set_quit_handler(%out%)
            set_short("landing")
            set_base_desc( "a landing at the top of the stairs" )
            add_surface( "floor", "finished pine board" )
            add_surface( "ceiling", "plain plaster" )
            add_surface( "%0% wall", "plain plaster" )
            add_surface( "%4% wall", "plain plaster" )
            add_surface( "%6% wall", "plain plaster" )
            add_exit( "%0%", PATH +"%N%masterbed", "door" )
            modify_exit("%0%", ["door short", "bedroom door"])
            add_exit( "%4%", PATH +"%N%bed2", "door" )
            modify_exit("%4%", ["door short", "bedroom door"])
            add_exit("%2%", PATH+"%N%landing2", "corridor")
            add_exit("down", PATH+"%N%livingroom", "corridor")
            modify_exit("down", ({"downgrade", 9])



class Nlanding1(MudObject):
