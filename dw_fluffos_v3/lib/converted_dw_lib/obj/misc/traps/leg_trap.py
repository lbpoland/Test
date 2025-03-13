# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/traps/leg_trap.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("trap")
            set_weight(1)
            set_short("leg trap")
            add_adjective("leg")
            set_long("This trap has a trigger suitable for rigging inside "
            "the lock of a door. It uses a small portion of the floor "
            "in front of the door to conceal a blunt leg trap that will "
            "shatter the femurs of any clumsy thief that attempt to "
            "pass through.\n")
            make_trap(350, "pick",
            "Hidden inside the lock is a trigger that leads down to a "
            "concealed panel on the floor. Carefully lifting the panel "
            "you see a vicious blunt man trap, designed to break any "
            "unskilled questionable entrant.\n",
            ({"A small click is heard, and the floor beneath your feet "
            "snaps away to reveal a leg trap which snaps together "
            "violently, shattering both your legs at once!\n",
            "A small click is heard and the jaws of a man trap burst out "
            "of the ground below " + this_player()->query_short() + "'s "
            "feet and shatters both of their legs!\n"],
            ["/std/effects/disease/broken_leg", ["left", "right"})])
            set_value(1000000)



class Leg_trap(MudObject):
