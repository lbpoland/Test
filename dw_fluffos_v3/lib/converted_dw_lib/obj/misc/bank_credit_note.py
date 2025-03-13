# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/bank_credit_note.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("note")
            set_short("bank credit note")
            add_adjective( ["bank", "credit"] )
            set_long("A small piece of paper which looks like some sort of "
            "bank transaction slip.\n")
            set_value(0)
            set_weight(1)


    def setup_read_messages(self, ) -> None:
            string extra
            string place
            place = query_property("place")
            if (_amount < 0) {
            extra = "Agrees to pay " +
            MONEY_HAND.money_value_string(-_amount, place) +
            " to the master bank.\n"
            } else {
            extra = "Slip for a withdrawl of " +
            MONEY_HAND.money_value_string(-_amount, place) +
            " from the master bank.\n"


    def set_credit_num(self, num: int) -> None:
            _id = num


    def query_credit_num(self, ) -> int:
            return _id


    def set_bank_name(self, bank: str) -> None:
            _bank = bank


    def query_bank_name(self, ) -> str:
            return _bank


    def set_franchise(self, franchise: str) -> None:
            _franchise = franchise


    def query_franchise(self, ) -> str:
            return _franchise


    def set_amount(self, amount: int) -> None:
            _amount = amount


    def query_amount(self, ) -> int:
            return _amount


    def is_valid_note(self, ) -> int:
            object bank
            object* obs
            object ob
            int ret
            bank = load_object(query_franchise())
            obs = bank.find_commercial_items("bank")
            if (sizeof(obs)) {
            foreach (ob in obs) {
            ret = ob.is_valid_note(query_credit_num())
            if (ret) {
            return 1


    def do_process(self, ) -> int:
            object bank
            object* obs
            object ob
            int ret
            bank = load_object(query_franchise())
            obs = bank.find_commercial_items("bank")
            if (sizeof(obs)) {
            foreach (ob in obs) {
            ret = ob.process_note(query_credit_num())
            if (ret) {
            return 1


    def init_dynamic_arg(self, map: Any) -> None:
            ::init_dynamic_arg(map)
            set_amount(query_auto_load_value(map, OBJECT_TAG, "amount"))
            set_franchise(query_auto_load_value(map, OBJECT_TAG, "franchise"))
            set_credit_num(query_auto_load_value(map, OBJECT_TAG, "id"))
            set_bank_name(query_auto_load_value(map, OBJECT_TAG, "bank"))



class Bank_credit_note(MudObject):
