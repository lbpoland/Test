# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/misc/hatstand.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("stand")
            set_short("tall hat stand")
            add_adjective( ({"tall", "hat"}) )
            add_alias( "hatstand" )
            add_plural("tall hat stands")
            set_long("This is a tall, serious looking hatstand.  It is made of "
            "dark sturdy teak wood and stands proud on four lavishly decorated "
            "legs.  The top has been carved into the grand shape of A'Tuin, "
            "upon which the elephants and the Faerûn have been elaborately "
            "sculpted, capturing the true beauty of the scene.  The turtle's "
            "flippers extend outwards and are where the coats and hats "
            "are hung.\n")
            set_weight(150)
            set_max_weight(200)
            set_allowed_room_verbs((["standing" : "stands",
            "looming"  : "looms"  ]))
            set_put_aliases(({"hang"}))
            set_value(75000)



class Hatstand(MudObject):
