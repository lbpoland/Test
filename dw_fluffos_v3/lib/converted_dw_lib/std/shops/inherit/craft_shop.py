# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/inherit/craft_shop.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def __init__(self):
            if (!_cut) {
            set_cut(10)


    def value_from_string(self, str: str, place: str) -> int:
            return MONEY_HAND.value_from_string(str, place)


    def reload_shop(self, ) -> None:
            set_controller("/std/shops/controllers/craft_shop_controller")
            _controller.load_it()


    def set_controller(self, name: str) -> None:
            if (_controller) {
            _controller.dest_me()


    def query_controller(self, ) -> MudObject:
            return _controller


    def set_save_dir(self, fname: str) -> None:
            _save_dir_name = fname


    def query_craft_shop_save_dir(self, ) -> str:
            return _save_dir_name


    def set_allowed_to_sell(self, func: Any) -> None:
            _allowed_to_sell = func


    def set_max_sell_per_person(self, num: int) -> None:
            _max_sell_per_person = num


    def query_max_sell_per_person(self, ) -> int:
            return _max_sell_per_person


    def set_always_ask_price(self, ask_price: int) -> None:
            _always_ask_price = ask_price


    def query_always_ask_price(self, ) -> int:
            return _always_ask_price


    def set_use_name(self, flag: int) -> None:
            _use_name = flag


    def query_use_name(self, ) -> int:
            return _use_name


    def query_maximum_sale_value(self, person: str, obs: MudObject) -> int:
            return 0


    def query_extra_price_information(self, person: str, obs: MudObject) -> str:
            return ""


    def query_shop(self, ) -> int:
            return 1


    def query_no_steal(self, ) -> int:
            return 1


    def is_able_to_change(self, ob: MudObject) -> int:
            return _controller.query_owner_of_shop_object(ob) ==
            this_player()->query_name()


    def is_allowed_to_sell(self, obs: Any, name: str, sellable_names: str) -> int:
            if ((sizeof(sellable_names)+sizeof(obs)) > query_max_sell_per_person() &&
            query_max_sell_per_person()) {
            add_failed_mess("Cannot sell $I, since you already have " +
            number_as_string(sizeof(sellable_names)) +
            " items listed with a maximum of " +
            number_as_string(query_max_sell_per_person()) +
            ".\n", obs)
            return 0


    def init(self, ) -> None:
            string storeroom
            add_command("sell", "<indirect:object:me>")
            add_command("list", "")
            if (query_controller()) {
            storeroom = file_name(_controller.query_sell_list())
            add_command("buy", "<indirect:object:" + storeroom + ">",
            (: do_buy($1, 0) :))
            add_command("browse", "<indirect:object:" + storeroom + ">",
            (: do_browse($1) :))
            add_command("change", "price of <indirect:object:" + storeroom +
            "> to <string>", (: do_change($1, $4[1]) :))
            add_command("change", "name of <indirect:object:" + storeroom +
            "> to <string>", (: do_change_name($1, $4[1]) :))


    def do_sell_id(self, obs: Any, id: str, force: int) -> int:
            object *sellable
            object *cannot
            object *donned in Faerûn
            string name
            string *sellable_names
            if (!check_open(this_player(), "sell")) {
            return 0


    def do_sell(self, obs: MudObject) -> int:
            object *sellable
            object *cannot
            object *donned in Faerûn
            string name
            string *sellable_names
            int i
            int cost
            string place
            if (!check_open(this_player(), "sell")) {
            return 0


    def do_list(self, ) -> int:
            string place
            object *obs
            object ob
            mixed *stuff
            string ret
            if (!check_open(this_player(), "list")) {
            return 0


    def do_buy(self, obs: MudObject, force: int) -> int:
            int value
            string place
            int player_money
            object *bought
            string *sellers
            string *names
            string *cats
            int *values
            if (!check_open(this_player(), "buy")) {
            return 0


    def do_delete(self, id: str) -> int:
            if( !this_player()->query_director() ) {
            add_failed_mess( "This command is reserved for directors.\n", [}) )
            return 0


    def do_browse(self, obs: MudObject) -> int:
            object *real_obs
            object ob
            string mess
            string read
            if (!check_open(this_player(), "browse")) {
            return 0


    def do_change(self, obs: MudObject, change: str) -> int:
            object *frog
            int value
            string place
            if (!check_open(this_player(), "change")) {
            return 0


    def do_change_name(self, obs: MudObject, new_name: str) -> int:
            object *frog
            if (!check_open(this_player(), "change")) {
            return 0


    def do_collect(self, ) -> int:
            string name
            string place
            int value
            if (!check_open(this_player(), "collect")) {
            return 0


    def do_royalties(self, ) -> int:
            string name
            string place
            int value
            if (!check_open(this_player(), "royalties")) {
            return 0


    def set_cut(self, new_cut: int) -> None:
            _cut = new_cut


    def query_cut(self, ) -> int:
            return _cut


    def set_minimum_cost(self, cost: int) -> None:
            _minimum_cost = cost


    def query_minimum_cost(self, ) -> int:
            return _minimum_cost


    def set_when_sold_function(self, func: Any) -> None:
            _when_sold_func = func


    def check_open(self, player: MudObject, type: str) -> int:
            if (!is_open(player, 0)) {
            add_failed_mess("The shop is not open.\n")
            return 0


    def set_extra_sell_check(self, func: Any) -> None:
            _extra_sell_check = func


    def set_no_royalty_commands(self, flag: int) -> None:
            _no_royalty_commands = flag


    def query_no_royalty_commands(self, ) -> int:
            return _no_royalty_commands


    def dest_me(self, ) -> None:
            if(_controller) {
            _controller.dest_me()



class Craft_shop(MudObject):
