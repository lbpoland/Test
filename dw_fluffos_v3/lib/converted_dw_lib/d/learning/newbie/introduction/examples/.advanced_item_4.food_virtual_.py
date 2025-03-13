# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/learning/newbie/introduction/examples/.advanced_item_4.food_virtual_.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def create_virtual_ob(self, ) -> MudObject:
            object clone
            clone = (object)SERVER.create_virtual_object( "/obj/food.c", 1 )
            clone.add_property( "virtual name", "/d/learning/newbie/introduction/examples/advanced_item_4.food#1" )
             clone.set_name("sandwich"  )
             clone.set_short("monkey sandwich"  )
             clone.add_adjective(["monkey"]  )
             clone.set_value(0  )
             clone.set_weight(1  )
             clone.set_long("This is a monkey sandwich.  Made from real monkey.  Mmm!\n"  )
             clone.add_eat_effect("/std/effects/ingested/poison", 600 )
            return clone



class .advanced_item_4.food_virtual_(MudObject):
