# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/misc/lava_lamp.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("lamp")
            set_short("lava lamp")
            set_light(25)
            add_adjective( ["lava", "red"] )
            add_alias( ["lamp"] )
            set_long( "This is an odd looking lamp, roughly the shape of an "
            "hourglass, with a brass base.  It is filled with murky pink "
            "liquid and large blobs of red goo that ooze this way and that.  "
            "The exact nature of the red goo is a mystery.  Some say it is "
            "a primitive type of troll that is still in its magma stage.  "
            "Others reckon it is something that got away from the Alchemists' "
            "Guild.  It gives off a faint light.\n" )
            item_chat( [120, 360, ({
            "A rather disgusting wet popping noise comes from the lava lamp.",
            "A strange sucking noise seems to be coming from the lava lamp."
            })] )
            set_allowed_positions(({"sitting","standing"}))
            set_allowed_room_verbs((["sitting" : "sits", "standing" : "stands" ]))
            set_weight(82)
            set_value(20500)


    def init(self, ) -> None:
            ::init()
            add_command( "stare", "at <direct:object'lamp'>" )


    def do_stare(self, ) -> int:
            asyncio.create_task(self. (: $(this_player())->add_effect( MEDITATION ) :), 1 )
            add_succeeded_mess( "$N $V dreamily at $D and zone$s out.\n")
            return 1



class Lava_lamp(MudObject):
