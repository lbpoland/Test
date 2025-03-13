# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/misc/huge_gong.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("gong")
            set_short("huge brass gong")
            add_adjective( ["huge", "brass"] )
            set_long("This is a huge brass gong, which hangs from an equally "
            "huge frame.  Prancing peacocks strut around each other on the "
            "surface of the disc, ruffling their tails as they "
            "stretch.  The gong can be hit to make a loud ringing "
            "sound and annoy everyone in the room.\n")
            set_weight( 100 )
            set_value( 42000 )
            set_material( "brass" )
            set_allowed_positions( ({"hanging"}) )
            set_allowed_room_verbs((["hanging" : "hangs",
            "sitting" : "sits",
            "dangling" : "dangles",
            "standing" : "stands" ]))


    def init(self, ) -> None:
            this_player()->add_command( "hit", self, "<direct:object:me>" )


    def do_hit(self, ) -> int:
            this_player()->add_succeeded_mess(self, "$N $V $p "
            +self.short()+" loudly, filling the room with a "
            "deafening crashing ring which reverberates for a few "
            "moments before finally fading away.\n", [}));    return 1



class Huge_gong(MudObject):
