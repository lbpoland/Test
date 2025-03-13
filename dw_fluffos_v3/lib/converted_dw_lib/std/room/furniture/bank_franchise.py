# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/furniture/bank_franchise.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._maximum_total_difference = 4000
            self._last_paid = time()


    def query_player_bank(self, ) -> int:
            return 1


    def set_maximum_total_difference(self, max: int) -> None:
            _maximum_total_difference = max


    def query_maximum_total_difference(self, ) -> int:
            return _maximum_total_difference


    def set_last_paid(self, paid: int) -> None:
            _last_paid = paid


    def query_last_paid(self, ) -> int:
            return _last_paid


    def adjust_account(self, person: str, amount: int) -> None:
            adjust_float(amount)


    def find_main_bank(self, ) -> MudObject:
            object office
            object* obs
            office = load_object(BANK_HANDLER.query_bank_master_office(query_bank_name()))
            if (!office) {
            return 0


    def can_adjust_account(self, person: str, amount: int) -> int:
            int amt
            amt = query_total_difference() + amount
            if (amt < -query_maximum_total_difference()  ||
            amt > query_maximum_total_difference()) {
            if (amt < 0) {
            add_failed_mess("This bank does not have the funds to handle "
            "your request.\n")
            } else {
            add_failed_mess("This bank does not have the vault space to handle "
            "your request.\n")


    def query_commercial_information(self, ) -> str:
            string* bits
            string bank
            string place
            place = previous_object()->query_money_place()
            bits = [})
            foreach (bank in BANK_HANDLER.query_banks()) {
            bits += [bank + " costs " +
            MONEY_HAND.money_value_string(BANK_HANDLER->query_bank_default_cost_per_month(bank), place) +
            " per month and " +
            MONEY_HAND.money_value_string(BANK_HANDLER->query_bank_default_cost_to_open(bank), place) +
            " to open"]


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


    def is_allowed(self, name: str) -> int:
            return commercial::is_allowed(name)


    def init(self, ) -> None:
            bank_franchise::init()
            commercial::init()
            if (is_allowed(this_player()->query_name())) {
            add_command("set", "percentage <number> on <direct:object>",
            (: do_set_cut($4[0]) :))
            add_command("set", "account cost <string'open cost'> on <direct:object>",
            (: do_set_open_cost($4[0]) :))


    def query_franchise(self, ) -> str:
            return file_name(environment())


    def event_save(self, ob: MudObject) -> None:
            environment()->event_save(ob)


    def set_commercial_option(self, type: str, name: str, room: MudObject) -> None:
            switch (type) {
            case "branch" :
            set_bank_name(name)
            BANK_HANDLER->add_new_franchise(name,
            file_name(room.query_main_room()))
            break


    def query_monthly_fee(self, ) -> int:
            return BANK_HANDLER->query_bank_franchise_cost_per_month(
            query_bank_name(), query_franchise())


    def is_open_for(self, type: str, name: str) -> int:
            if (query_monthly_fee() == -1) {
            return 0


    def setup_call_out(self, ) -> None:
            int tim
            if (!_last_paid) {
            _last_paid = time()


    def make_payment(self, ) -> None:
            _last_paid += MONTH_LENGTH
            adjust_float(-query_monthly_fee())
            setup_asyncio.create_task(self.)


    def query_main_status(self, hints: int) -> str:
            string ret
            string place
            add_help_file("bank_franchise")
            place = query_money_place()
            ret = "$I$0=" + the_short() + ":\n"
            "$I$6=   Bank Branch                  : " + query_bank_name() + "\n"
            "$I$6=   Revenue                      : " +
            MONEY_HAND.money_value_string(query_revenue(), place) + "\n"
            "$I$6=   Master Address               : " +
            BANK_HANDLER.query_bank_master_office(query_bank_name())->query_address() +
            "\n$I$6=   Maximum allowed bank balance : " +
            MONEY_HAND.money_value_string(query_maximum_total_difference(), place) +
            " (fixed)\n$I$6=   Bank Balance                 : " +
            MONEY_HAND.money_value_string(query_total_difference(), place) +
            "\n$I$6=   Credit Notes Outstanding     : " +
            MONEY_HAND.money_value_string(query_outstanding_credit_value(), place) + "\n"
            if (hints) {
            ret += "$I$6=     Hint: list credit notes\n"
            ret += "$I$6=     Hint: create credit note\n"
            ret += "$I$6=     Hint: recind credit note <id>\n"


    def init_dynamic_arg(self, map: Any, player: MudObject) -> None:
            commercial::init_dynamic_arg(map, player)
            set_bank_name(query_auto_load_value(map, OBJECT_TAG, "bank"))
            set_account_cost(query_auto_load_value(map, OBJECT_TAG, "open"))
            set_percentage(query_auto_load_value(map, OBJECT_TAG, "percentage"))
            set_total_difference(query_auto_load_value(map, OBJECT_TAG, "difference"))
            set_credit_notes(query_auto_load_value(map, OBJECT_TAG, "notes"))
            set_credit_num(query_auto_load_value(map, OBJECT_TAG, "credit num"))
            set_last_paid(query_auto_load_value(map, OBJECT_TAG, "last paid"))
            setup_asyncio.create_task(self.)



class Bank_franchise(MudObject):

    _maximum_total_difference = 4000

    _last_paid = 'time()'
