# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/outsides/basic.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def do_get_rock(self, verb: str, dest: MudObject) -> Any:
            int rock_size
            string rock_type
            object rock
            if ( query_property( "rock object" ) )
            return ( rock = clone_object( (string)query_property( "rock object" ) ) )
            if ( undefinedp( rock_size = (int)query_property( "rock size" ) ) )
            rock_size = 3
            if ( !rock_size ) return 0
            rock = clone_object( "/obj/mineral" )
            if ( undefinedp( rock_type = (string)query_property( "rock type" ) ) )
            rock_type = ["cinnabar", "coal", "rosy-quartz", "chalk", "flint",
            "slate"][ random( 6 ) ]
            rock.make_mineral( rock_type, 1 + random( rock_size ) )
            if ( !( rock.move( this_player() ) ) ) return 1
            rock.dest_me()
            return 0



class Basic(MudObject):
