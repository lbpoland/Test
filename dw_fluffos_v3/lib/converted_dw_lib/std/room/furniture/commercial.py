# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/furniture/commercial.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._commercial_size = 100
            self._use_types = []


    def __init__(self):
            self._commercial_size = 100
            self._use_types = []
            do_setup++
            object::create()
            furniture_base::create()
            add_alias( "furniture" )
            add_plural( "furniture" )
            add_property("talisman", "no one")
            set_opaque()
            if ( !query_property( "shop type" ) ) {
            add_property( "shop type", "furniture" )


    def set_weekly_upkeep_cost(self, cost: int) -> None:
            _weekly_upkeep_cost = cost


    def query_weekly_upkeep_cost(self, ) -> int:
            return _weekly_upkeep_cost


    def query_revenue(self, ) -> int:
            return _revenue


    def set_revenue(self, revenue: int) -> None:
            _revenue = revenue


    def query_save_dir(self, ) -> str:
            return environment()->query_save_dir()


    def query_owner(self, ) -> str:
            return environment()->query_owner()


    def query_language(self, ) -> str:
            return environment()->query_language()


    def query_money_place(self, ) -> str:
            if (!environment()) {
            return "default"


    def is_allowed(self, person: str) -> int:
            return environment()->is_allowed(person)


    def query_allowed(self, ) -> str:
            return environment()->query_allowed()


    def query_float(self, ) -> int:
            return environment()->query_royalty(query_owner())


    def query_royalty(self, person: str) -> int:
            return environment()->query_royalty(person)


    def adjust_royalty(self, person: str, amount: int) -> int:
            if (person == query_owner()) {
            _revenue += amount
            _weekly_revenue += amount


    def adjust_float(self, amt: int) -> int:
            adjust_royalty(query_owner(), amt)


    def is_open_for(self, type: str, person: str) -> int:
            if (!environment()->query_commercial_property()) {
            return 0


    def set_commercial_size(self, size: int) -> None:
            _commercial_size = size


    def query_commercial_type(self, ) -> str:
            return _commercial_type


    def set_commercial_type(self, type: str) -> None:
            _commercial_type = type


    def set_commercial_information(self, info: str) -> None:
            _info = info


    def query_commercial_information(self, ) -> str:
            return _info


    def set_commercial_name(self, name: str) -> None:
            _commercial_name = name


    def query_commercial_name(self, ) -> str:
            return _commercial_name


    def query_commercial_size(self, ) -> int:
            return _commercial_size


    def query_commercial_id(self, ) -> int:
            return _commercial_id


    def setup_new_commercial_id(self, ) -> None:
            _commercial_id = environment()->find_next_commercial_id()


    def set_commercial_id(self, id: int) -> None:
            _commercial_id = id


    def query_parcel_post(self, ) -> str:
            return environment()->query_parcel_post()


    def set_shop_use_types(self, types: Any) -> None:
            _use_types = types


    def reset_weekly_status(self, ) -> None:
            _weekly_revenue = 0


    def query_weekly_status_string(self, ) -> str:
            string ret
            string place
            place = query_money_place()
            if (query_weekly_upkeep_cost()) {
            ret = "Weekly Upkeep : " +
            MONEY_HAND.money_value_string(_weekly_upkeep_cost, place) + "\n" +
            "Weekly Revenue: " +
            MONEY_HAND.money_value_string(_weekly_revenue, place) + "\n" +
            "Profit        : " +
            MONEY_HAND.money_value_string(_weekly_revenue - _weekly_upkeep_cost, place) + "\n"
            } else {
            ret = "Weekly Revenue: " +
            MONEY_HAND.money_value_string(_weekly_revenue, place) + "\n"


    def can_trash_furniture(self, ) -> int:
            return 1


    def query_commercial_furniture(self, ) -> int:
            return 1


    def get(self, dest: Any) -> int:
            if(!move_check(dest)) {
            write("You feel it would be wrong to take " + the_short() + ".\n")
            return 2


    def do_status(self, hint: int) -> int:
            string ret
            ret = query_main_status(hint)
            write("$P$Status$P$" + ret)
            add_succeeded_mess("$N get$s the status of $D.\n")
            return 1


    def do_reset(self, ) -> int:
            string place
            int old_revenue
            place = query_money_place()
            old_revenue = _revenue
            _revenue = 0
            add_succeeded_mess("$N clear$s the revenue of " +
            MONEY_HAND.money_value_string(old_revenue, place) +
            " on $D.\n")
            return 1


    def init(self, ) -> None:
            ::init()
            if (is_allowed(this_player()->query_name())) {
            add_command("status", "<direct:object>", (: do_status, 0 :))
            add_command("status", "hints <direct:object>", (: do_status, 1 :))
            add_command("status", "hint <direct:object>", (: do_status, 1 :))
            add_command("reset", "revenue on <direct:object>", (: do_reset :))


    def query_static_auto_load(self, ) -> Any:
            if ( base_name(self) + ".c" == __FILE__ ) {
            return int_query_static_auto_load()


    def query_dynamic_auto_load(self, ) -> Any:
            mapping junk
            junk = object::query_dynamic_auto_load()
            if (!junk) {
            junk = ([ ])


    def init_dynamic_arg(self, map: Any) -> None:
            object::init_dynamic_arg(map)
            if (map) {
            set_bonded(map["bonded"])
            set_revenue(query_auto_load_value(map, OBJECT_TAG, "revenue"))
            if (query_auto_load_value(map, OBJECT_TAG, "commercial id")) {
            set_commercial_id(query_auto_load_value(map, OBJECT_TAG, "commercial id"))


    def query_help_file_directory(self, ) -> str:
            return "/doc/furniture/"



class Commercial(MudObject):

    _commercial_size = 100

    _use_types = '[]'
