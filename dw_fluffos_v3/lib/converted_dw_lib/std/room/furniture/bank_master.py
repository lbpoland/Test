# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/furniture/bank_master.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def event_save(self, ob: MudObject) -> None:
            environment()->event_save(ob)


    def find_bank_object(self, franchise: str) -> MudObject:
            object* obs
            object room
            room = load_object(franchise)
            if (room.query_bank()) {
            return room


    def do_list_franchises(self, ) -> int:
            string franchise
            int pos
            object bank_ob
            string ret
            string place
            if (!sizeof(BANK_HANDLER.query_franchises(query_bank_name()))) {
            add_failed_mess("This bank has no franchises.\n")
            return 0


    def do_set_franchise_cost(self, cost: str) -> int:
            int amount
            string place
            place = query_money_place()
            amount = MONEY_HAND.value_from_string(cost, place)
            if (amount <= 0) {
            add_failed_mess("Unknown amount " + cost + ".\n")
            return 0


    def do_set_default_monthly_cost(self, cost: str) -> int:
            int amount
            string place
            place = query_money_place()
            amount = MONEY_HAND.value_from_string(cost, place)
            if (amount <= 0) {
            add_failed_mess("Unknown amount " + cost + ".\n")
            return 0


    def do_set_main_bank_name(self, new_name: str) -> int:
            string* names
            string name
            if (query_bank_name()) {
            add_failed_mess("This bank already has a name.\n")
            return 0


    def check_bank_name(self, response: str, new_name: str) -> None:
            if (!strlen(response) || lower_case(response)[0] != 'y') {
            write("Ok, aborting.\n")
            return


    def do_set_cut(self, percent: int) -> int:
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to change the paramaters of "
            "$D.\n")
            return 0


    def do_set_open_cost(self, str: str) -> int:
            string place
            int value
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to change the paramaters of "
            "$D.\n")
            return 0


    def do_set_franchise_cost_per_month(self, id: str, amount: str) -> int:
            string *franchises
            int id_num
            int amt
            id = lower_case(id)
            if (strlen(id) != 1) {
            add_failed_mess("Must be one letter.\n")
            return 0


    def query_main_status(self, hints: int) -> str:
            string ret
            string place
            place = query_money_place()
            ret = "$I$0=" + the_short() + ":\n"
            ret += "$I$6=   Bank Name             : " +
            query_bank_name() + "\n"
            ret += "$I$6=   Revenue               : " +
            MONEY_HAND.money_value_string(query_revenue(), place) + "\n"
            ret += "$I$6=   Cost to buy franchise : " +
            MONEY_HAND.money_value_string(BANK_HANDLER->query_bank_default_cost_to_open(query_bank_name()), place) + "\n"
            if (hints) {
            ret += "$I$9=      Hint: set buy franchise cost <amount> on <object>\n"


    def init_dynamic_arg(self, map: Any, player: MudObject) -> None:
            commercial::init_dynamic_arg(map, player)
            set_bank_name(query_auto_load_value(map, OBJECT_TAG, "bank"))
            set_account_cost(query_auto_load_value(map, OBJECT_TAG, "open"))
            set_percentage(query_auto_load_value(map, OBJECT_TAG, "percentage"))
            set_total_difference(query_auto_load_value(map, OBJECT_TAG, "difference"))


    def init(self, ) -> None:
            commercial::init()
            bank_master::init()
            if (is_allowed(this_player()->query_name())) {
            add_command("set", "bank name <string'name'> on <direct:object>",
            (: do_set_main_bank_name($4[0]) :))
            add_command("set", "buy franchise cost <string'cost'> on <direct:object>",
            (: do_set_franchise_cost($4[0]) :))
            add_command("set", "franchise monthly cost <string'cost'> on <direct:object>",
            (: do_set_default_monthly_cost($4[0]) :))
            add_command("set", "percentage <number> on <direct:object>",
            (: do_set_cut($4[0]) :))
            add_command("set", "account cost <string'open cost'> on <direct:object>",
            (: do_set_open_cost($4[0]) :))
            add_command("set", "franchise monthly cost <string'cost'> for <string'franchise id'> on <direct:object>",
            (: do_set_franchise_cost_per_month($4[1], $4[0]) :))
            add_command("list", "franchises on <direct:object>",
            (: do_list_franchises :))



class Bank_master(MudObject):
