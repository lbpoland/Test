# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/inherit/craft_shop_category.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._default_category = "General"


    def __init__(self):
            self._default_category = "General"
            ::create()


    def init(self, ) -> None:
            string storeroom
            ::init()
            if (query_controller()) {
            storeroom = file_name(query_controller()->query_sell_list())
            add_command("change", "category of <indirect:object:" + storeroom +
            "> to <string'category'>",
            (: do_change_category($1, $4[1]) :))


    def add_shop_category(self, category: str) -> None:
            query_controller()->add_category_accepted(category)


    def set_category_description(self, category: str, description: str) -> None:
            query_controller()->set_category_description(category, description)


    def set_category_information(self, category: str, information: str) -> None:
            query_controller()->set_category_information(category, information)


    def remove_shop_category(self, category: str) -> None:
            query_controller()->remove_category_accepted(category)


    def query_default_category(self, ) -> str:
            return _default_category


    def set_controller(self, name: str) -> None:
            ::set_controller(name)
            setup_default_category()


    def update_categories(self, ) -> None:
            object *obs
            object ob
            obs = query_controller()->query_sell_list_obs()
            foreach (ob in obs) {
            if (!query_controller()->query_category_of_shop_object(ob)) {
            query_controller()->change_category_of_shop_object(ob, _default_category)


    def query_real_category_name(self, in_cat: str) -> str:
            string* categories
            string cat
            categories = query_controller()->query_categories()
            foreach (cat in categories) {
            if (lower_case(cat)[0..strlen(in_cat)-1] == lower_case(in_cat)) {
            return cat


    def do_list_category(self, category: str) -> int:
            string place
            string info
            object *obs
            object ob
            mixed *morestuff
            string ret
            string list
            if (!check_open(this_player(), "list")) {
            return 0


    def do_list(self, ) -> int:
            string place
            object *obs
            mixed *stuff
            mixed *morestuff
            string ret
            string* categories
            string cat
            string desc
            object ob
            if (!check_open(this_player(), "list")) {
            return 0


    def do_change_category(self, obs: MudObject, new_category: str) -> int:
            object *frog
            if (!check_open(this_player(), "change")) {
            return 0


    def set_extra_sell_check(self, func: Any) -> None:
            _cat_extra_sell_check = func


    def set_default_category(self, category: str) -> None:
            _default_category = category



class Craft_shop_category(MudObject):

    _default_category = '"General"'
