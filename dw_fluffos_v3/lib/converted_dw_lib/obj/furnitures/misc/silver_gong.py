# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/misc/silver_gong.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("gong")
            set_short("silver gong")
            add_adjective( "silver" )
            set_long("This is a smallish silver gong, hanging from a silver "
            "frame.  Tiny goldfish swim around each other on the "
            "surface of the disc, nipping each others' tails as they "
            "go.  The gong can be hit to make a loud ringing "
            "sound and annoy everyone in the room.\n")
            set_weight( 40 )
            set_value( 22000 )
            set_material( "silver" )
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
            "deafening ringing sound.\n", [}))
            return 1



class Silver_gong(MudObject):
