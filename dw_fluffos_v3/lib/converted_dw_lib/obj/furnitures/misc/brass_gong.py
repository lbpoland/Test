# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/misc/brass_gong.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("gong")
            set_short("brass gong")
            add_adjective( "brass" )
            set_long("This is a medium-sized brass gong, hanging from a brass "
            "frame.  Lazy pandas roll around the surface of the gong, "
            "the occasional one actually doing something other than "
            "eating or chewing on a stalk of bamboo.  The gong can be hit "
            "to make a loud ringing sound and annoy everyone in the room.\n")
            set_weight( 60 )
            set_value( 10000 )
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
            "deafening ringing sound.\n", [}))
            return 1



class Brass_gong(MudObject):
