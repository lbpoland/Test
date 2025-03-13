# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/player_shop/office_code/admin.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def adjust_takings(self, amt: int) -> None:
            {
            if (previous_object() && previous_object() != find_object(_counter))
            {
            LOG_ERROR("office.c", "adjust_bought("+amt+")")
            return


    def calc_bonus(self, ) -> None:
            {
            int bonus_val, bonus_divisor = 0
            foreach (string str in m_indices(_employees))
            {
            if (_employees[str][EMP_NOBONUS]) continue
            if (_employees[str][EMP_POINTS] & MANAGER)
            {
            bonus_divisor += 4


    def calc_pay(self, ) -> int:
            {
            int amount = 0
            foreach(string word in m_indices(_employees))
            amount += _employees[word][EMP_PAY]
            return amount


    def check_manager(self, action: str) -> int:
            {
            object tp = this_player()
            string tp_name = tp.query_name()
            if (tp.query_creator() || (_employees[tp_name][EMP_POINTS] & MANAGER) ||
            (_retired.index(tp_name) if tp_name in _retired else -1 != -1)) return 1
            return notify_fail( "You are not a manager here!\n" )


    def directions_to(self, place: str) -> str:
            {
            if (place == _counter) return copy(_counter_dir)
            if (place == _storeroom) return copy(_store_dir)
            if (place == _shop_front) return copy(_shop_dir)
            return "here"


    def do_set(self, args: Any, pattern: str) -> int:
            {
            int value, best
            object money
            switch(pattern)
            {
            case SET_EMPS :
            if (args[0] < MIN_EMP || args[0] > MAX_EMP)
            {
            tell_object(this_player(), "Must be between "+ MIN_EMP+
            " and "+ MAX_EMP+ ".\n")
            return 1


    def do_transfer(self, args: Any) -> int:
            {
            int value, best
            object money
            string tp
            if (args[2] == args[3] || !args[0])
            {
            await this_player().send("The point being?\n")
            return 1


    def set_employee(self, word: str, bit: int) -> None:
            {
            if (!_employees[word]) return
            _employees[word][EMP_POINTS] |= bit
            if (bit != CLOCKED_IN) save_emps()


    def summon_shopkeeper(self, ) -> None:
            {
            object shopkeeper = find_object(_shopkeeper)
            if (shopkeeper && environment(shopkeeper)) return
            if (num_employees_in()) return
            _shopkeeper.start_shift()



class Admin(MudObject):
