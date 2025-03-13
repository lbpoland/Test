# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/commercial/pickler.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "pickler" )
            set_short( "pickler" )
            set_long( "A small wooden box with a handle on it, it has some words "
            "written on it.\n")
            add_read_mess("Pickler, pull for results", 0, "common")
            set_allowed_positions(({"sitting", "lying", "kneeling", "meditating"}))
            set_allowed_room_verbs((["sitting" : "sits" ]))
            set_weight(2000)
            set_value(240000)
            add_help_file("pickler")
            set_commercial_size(2)
            set_commercial_type("utility")
            set_shop_use_types(["pickler"])
            _cost = 80


    def do_pickle(self, obs: Any) -> int:
            object* pickleable
            string place
            int amt
            int here_amt
            if (!is_open_for("pickler", this_player()->query_name())) {
            add_failed_mess("The pickler is not open.\n")
            return 0


    def do_set_cost(self, amount: str) -> int:
            int amt
            string place
            place = query_money_place()
            amt = MONEY_HAND.value_from_string(amount, place)
            if (amt <= 0) {
            add_failed_mess("The value " + amount + " is invalid.\n")
            return 0


    def query_main_status(self, hint: int) -> str:
            string place
            place = query_money_place()
            return the_short() + " status:\n"
            "\n$I$6=   Fee Per Use : " +
            MONEY_HAND.money_value_string(FEE_PER_USE, place) + " (fixed)"
            "\n$I$6=   Cost Per Use: " +
            MONEY_HAND.money_value_string(_cost, place) +
            "\n$I$6=   Profit      : " +
            MONEY_HAND.money_value_string(_revenue, place) + "\n"


    def do_stats(self, ) -> int:
            string ret
            ret = query_main_status(0)
            write(ret)
            add_succeeded_mess("")
            return 1


    def init(self, ) -> None:
            commercial::init()
            add_command("use", "<direct:object> to [pickle] <indirect:object>",
            (: do_pickle :))
            add_command("use", "<direct:object> with <indirect:object>",
            (: do_pickle :))
            add_command("pickle", "<indirect:object> with <direct:object>",
            (: do_pickle :))
            add_command("pull", "[handle] [on] <direct:object> with <indirect:object>",
            (: do_pickle :))
            if (environment()->is_allowed(this_player()->query_name())) {
            add_command("status", "<direct:object>",
            (: do_stats() :))
            add_command("set", "cost <string'cost'> on <direct:object>",
            (: do_set_cost($4[0]) :))


    def init_dynamic_arg(self, map: Any, player: MudObject) -> None:
            commercial::init_dynamic_arg(map, player)
            _revenue = query_auto_load_value(map, BOARD_TAG, "revenue")
            _cost = query_auto_load_value(map, BOARD_TAG, "cost")



class Pickler(MudObject):
