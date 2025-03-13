# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/house/fourbedhouse/Ngarden.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_light(50)
            set_theft_handler( HOSPITAL )
            set_save_file("%savedir%/%N%garden")
            set_orientation(%orientation%)
            set_quit_handler(%out%)
            set_short("small garden")
            set_base_desc("a quiet and secluded garden")
            add_surface("floor", "grass")
            add_surface("%0% wall", "red brick" )
            add_surface( "%2% wall", "red brick" )
            add_surface( "%6% wall", "red brick" )
            add_exit("%4%", PATH+"%N%familyroom", "door")
            modify_exit("%4%", ["door short", "garden door"])
            add_exit("window", PATH+"%N%diningroom", "window")



class Ngarden(MudObject):
