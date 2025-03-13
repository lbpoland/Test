# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/commercial/money_changer.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "counter" )
            set_short( "money changer counter" )
            add_adjective( ["money", "changer" } ))
            add_alias("changer")
            set_long( "A box with a bunch of holes in it, it looks like it will "
            "change coins into other types of coins.\n")
            set_allowed_positions(({"sitting", "lying", "kneeling", "meditating"}))
            set_allowed_room_verbs((["sitting" : "sits" ]))
            set_weight(2000)
            set_value(240000)
            add_help_file("money_changer")
            set_commercial_size(5)
            _cut = 10
            _cost = 400
            _money = ([ ])


    def change(self, words: str, type: str) -> int:
            int val_index
            int value
            int value_type
            int value_unit
            int value_change
            int value_num
            int i
            string place
            mixed money
            object changed
            object *monies
            mixed *change
            mixed *values
            mixed *money_bits
            place = query_money_place()
            if ( !place || ( place == "" ) ) {
            place = "default"


    def query_main_status(self, hint: int) -> str:
            string type
            string place
            int num
            string str
            place = query_money_place()
            str = "$I$0=Money Changer:\n"
            str += "$I$6=   Percentage cut " + _cut + "%\n"
            foreach (type, num in _money) {
            str += "$I$6=   " + num + " " + type + "\n"


    def do_set_cost(self, str: str) -> int:
            string place
            int value
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to change the paramaters of "
            "$D.\n")
            return 0


    def do_set_cut(self, number: int) -> int:
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to change the paramaters of "
            "$D.\n")
            return 0


    def do_deposit(self, num: int, str: str) -> int:
            mixed* values
            int i
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to change the paramaters of "
            "$D.\n")
            return 0


    def do_withdraw(self, num: int, str: str) -> int:
            string tmp
            int bing
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to change the paramaters of "
            "$D.\n")
            return 0


    def init(self, ) -> None:
            commercial::init()
            add_command("change", "<string'money'> into <string'type'> on <direct:object>",
            (: change($4[0], $4[1]) :))
            if (environment()->is_allowed(this_player()->query_name())) {
            add_command("set", "cut <number'percentage'> on <direct:object>",
            (: do_set_cut($4[0]) :))
            add_command("deposit", "<number> of <string'type'> on <direct:object>",
            (: do_deposit($4[0], $4[1]) :))
            add_command("withdraw", "<number> of <string'type'> on <direct:object>",
            (: do_withdraw($4[0], $4[1]) :))


    def init_dynamic_arg(self, map: Any, player: MudObject) -> None:
            commercial::init_dynamic_arg(map, player)
            _cut = query_auto_load_value(map, BOARD_TAG, "cut")
            _money = query_auto_load_value(map, BOARD_TAG, "money")
            _cost = query_auto_load_value(map, BOARD_TAG, "cost")



class Money_changer(MudObject):
