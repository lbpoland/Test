# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/dist/pumpkin/crumpt/club_office.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_light(70)
            set_club_control_type(CLUB_ROOM_CLUB_ONLY)
            set_short("Club control room")
            set_long("This is a small cosy room with a nice comradely atmosphere "
            "about it.  There is a nice sofa and a desk with little club "
            "ornaments all over it.\n")
            add_item("sofa", ["long",
            "The sofa looks nice and comfortable, just the spot "
            "after a hard days hacking people into small bits.\n",
            "position", "the comfy sofa"])
            add_item("desk",
            ["long",
            "The brown leather covered desk looks really nice "
            "and comforable sitting in the middle of the room like "
            "that.  It is covered in small club shaped ornaments.\n",
            "position", "the large black desk"])
            add_item("club ordanment",
            "The desk is covered in them, 'Real genuine minature babarian "
            "clubs'.  Looks like someone has a club fetish.\n")
            set_not_replaceable(1)
            clone_object("/obj/misc/top_clubs")->move(self)
            add_exit("south", PATH + "crumpt6", "door")
            add_property("place", "Pumpkin")



class Club_office(MudObject):
