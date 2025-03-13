# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/learning/help_topics/rooms/crowd/crowdroom.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            add_property( "commented functions",
            [] )
            add_property( "keywords",
            ["crowd"] )
            set_short("crowd demonstration room")
            set_light(100)
            set_long("This is a room to contain a crowd of NPC's.  "
            "It is intend to be a venue to test and try out "
            "the crowd NPC object and related files:\n"
            "%^YELLOW%^/d/am/learning/help_topics/crowd/crowd.c\n"
            "/d/am/learning/help_topics/crowd/crowd_merge_effect.c\n"
            "/d/am/learning/help_topics/crowd/crowd_merge_shadow.c"
            "%^RESET%^\n"
            "You can %^CYAN%^inv here%^RESET%^ to see objects present.  "
            "You can also attack the beggars as NPCs may not use the exits.\n")
            add_exit( "back", LEARNING +"search", "path" )
            add_exit( "exit", ENTRANCE, "path" )
            modify_exit( "back", ["function", (: interactive($2) :)] )
            modify_exit( "exit", ["function", (: interactive($2) :)] )


    def reset(self, ) -> None:
            if (!crowd) {
            crowd=clone_object( CROWD+"crowd" )
            crowd.move( self )



class Crowdroom(Room):
