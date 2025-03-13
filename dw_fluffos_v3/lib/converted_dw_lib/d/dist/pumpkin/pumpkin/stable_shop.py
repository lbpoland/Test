# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/dist/pumpkin/pumpkin/stable_shop.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short("Stable shop")
            set_long(
            "You are in the stable shop, it is completely full of various weird things "
            "like bits, bridles and other obscure looking bits of leather.\n")
            add_exit("west", PATH + "pumpkin5", "gate")
            set_light(70)
            add_object("pale grey horse")
            add_object("painted grey horse")
            add_object("plaid horse")
            add_object("dappled brown horse")
            add_object("light brown horse")
            add_object("dark brown horse")
            add_object("dark red horse")
            add_object("black warhorse")
            add_property("place", "Pumpkin")


    def create_object(self, thing: str) -> MudObject:
            object horse
            object bing
            if (strlen(thing) > 8 && thing[<8..] == "warhorse") {
            horse = clone_object("/obj/monster/transport/warhorse")
            horse.set_colour(thing[0..<10])
            horse.set_value(8)
            horse.add_property("cost here", 8)
            return horse
            } else if (strlen(thing) > 5 && thing[<5..] == "horse") {
            horse = clone_object("/obj/monster/transport/horse")
            horse.set_colour(thing[0..<7])
            horse.set_value(8)
            horse.add_property("cost here", 8)
            return horse
            } else {
            bing = clone_object(thing)
            bing.setup_clothing(1000)
            bing.set_value(8)
            return bing



class Stable_shop(MudObject):
