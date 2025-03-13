# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/dist/pumpkin/gumboot/weapon_shop.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_short("Pointy's Weapon Shop")
            set_long(
            "Racks of weapons line the room, don't touch, they look sharp.\n")
            set_light(70)
            add_exit("east", PATH + "gumboot4", "door")
            add_object("morning star", 1 + random(20))
            add_object("black handled ceremonial bronze knife", 1 + random(20))
            add_object("carving knife", 1 + random(20))
            add_object("chisel", 1 + random(20))
            add_object("copper fighting knife", 1 + random(20))
            add_object("dagger", 1 + random(20))
            add_object("howondalandish throwing knife", 1 + random(20))
            add_object("klatchian steel dirk", 1 + random(20))
            add_object("knife", 1 + random(20))
            add_object("letter opener", 1 + random(20))
            add_object("meat cleaver", 1 + random(20))
            add_object("sharp butter knife", 1 + random(20))
            add_object("silver sickle", 1 + random(20))
            add_object("small copper knife", 1 + random(20))
            add_object("small knife", 1 + random(20))
            add_object("stiletto", 1 + random(20))
            add_object("tanto", 1 + random(20))
            add_object("white handled ceremonial bronze knife", 1 + random(20))
            add_property("place", "Pumpkin")



class Weapon_shop(MudObject):
