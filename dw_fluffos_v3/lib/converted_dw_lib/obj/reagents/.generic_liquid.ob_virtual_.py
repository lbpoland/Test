# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/reagents/.generic_liquid.ob_virtual_.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def create_virtual_ob(self, ) -> MudObject:
            object clone
            clone = (object)SERVER.create_virtual_object( "/obj/food.c", 1 )
            clone.add_property( VIRTUAL_NAME_PROP, "/obj/reagents/generic_liquid.ob#1" )
             clone.add_adjective("some"  )
             clone.add_alias("liquid"  )
             clone.set_amount_types(([ "drop": [1, "drops"],              "teaspoon": [20, "teaspoons"],              "tablespoon": [60, "tablespoons"],              "ounce": [120, "ounces"],              "cup": [960, "cups"],              "pint": [2400, "pints"],                          "quart": [4800, "quarts"],                          "gallon": [19200, "gallons"] ])  )
             clone.add_adjective(["drop", "drops", "teaspoon", "teaspoons", "tablespoon",                "tablespoons", "ounce", "ounces", "cup", "cups", "pint",                "pints", "quart", "quarts", "gallon", "gallons", "of"]  )
             clone.set_pile_types([50, "small", 100, "medium", "large"]  )
             clone.set_continuous()
             clone.set_liquid()
             clone.add_property("determinate", "" )
            return clone



class .generic_liquid.ob_virtual_(MudObject):
