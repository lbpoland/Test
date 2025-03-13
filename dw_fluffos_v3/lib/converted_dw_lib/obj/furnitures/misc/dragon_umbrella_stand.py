# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/misc/dragon_umbrella_stand.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("stand")
            set_short("enamelled umbrella stand")
            add_adjective( ["enamelled", "umbrella"] )
            set_long("To keep the floors clean on rainy days, this hexagonal "
            "decorative umbrella stand suits that purpose perfectly.  A "
            "tin liner sits inside its base to catch inevitable drips and to "
            "protect its wood.  Handpainted with in blacks, golds and reds with "
            "a ferocious looking dragon design, it boasts a brass handle on "
            "each side for ease of lifting.\n")
            add_read_mess("\nMade in Sum Dim.", "tiny golden lettering around the "
            "base", "agatean")
            set_open()
            set_stuck(1)
            set_weight(90)
            set_max_weight(55)
            set_value(44000)
            set_allowed_room_verbs( ([ "squatting" : "squats",
            "resting" : "rests",
            "sitting" : "sits",
            "standing" : "stands" ]) )



class Dragon_umbrella_stand(MudObject):
