# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/buckets/.bucket_small.ob_virtual_.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def create_virtual_ob(self, ) -> MudObject:
            object clone
            clone = (object)SERVER.create_virtual_object( "/obj/vessel.c", 1 )
            clone.add_property( VIRTUAL_NAME_PROP, "/obj/misc/buckets/bucket_small.ob#1" )
             clone.set_name("bucket"  )
             clone.set_short("small bucket"  )
             clone.set_long("This is a small metal bucket.  It is not very shiny.\n"  )
             clone.set_main_plural("small buckets"  )
             clone.add_adjective("small"  )
             clone.add_plural("buckets"  )
             clone.set_stuck(1  )
             clone.set_leak_rate(0  )
             clone.set_max_volume(3000  )
             clone.set_max_weight(30  )
             clone.set_full_weight(30  )
             clone.set_value(85  )
             clone.set_weight(10  )
             clone.set_material("metal" )
            return clone



class .bucket_small.ob_virtual_(MudObject):
