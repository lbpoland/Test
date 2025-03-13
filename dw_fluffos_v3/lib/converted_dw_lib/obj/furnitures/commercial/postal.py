# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/commercial/postal.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "counter" )
            set_short( "postal counter" )
            add_adjective("postal")
            set_long( "A wooden counter that looks like a place you could write "
            "and read mail.\n")
            set_allowed_positions(({"sitting", "lying", "kneeling", "meditating"}))
            set_allowed_room_verbs((["sitting" : "sits" ]))
            set_weight(2000)
            set_value(6400000)
            add_help_file("postal")
            set_commercial_size(25)
            set_commercial_type("utility")
            set_shop_use_types(["pickler"])


    def do_mail(self, to: str) -> int:
            if (MAIL_TRACK.mail(to)) {
            _num_uses++
            return 1


    def query_main_status(self, hint: int) -> str:
            string place
            place = query_money_place()
            return the_short() + " status:\n"
            "\n$I$6=   Number of  uses : " + _num_uses + "\n"


    def init(self, ) -> None:
            commercial::init()
            add_command("mail", "<string'to'>",
            (: do_mail($4[0]) :))
            add_command("mail", "[handle] [on] <direct:object> with <indirect:object>",
            (: do_mail(0) :))


    def init_dynamic_arg(self, map: Any, player: MudObject) -> None:
            commercial::init_dynamic_arg(map, player)
            _num_uses = query_auto_load_value(map, BOARD_TAG, "uses")



class Postal(MudObject):
