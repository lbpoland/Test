# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/admin/room/we_care/main_club_room.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short("main club room")
            set_long("The main club room.\n")
            set_club_controller(CONTROLLER)
            set_light(70)
            set_leave_exit("south")
            add_exit("south", "/d/admin/room/meeting", "door")



class Main_club_room(MudObject):
