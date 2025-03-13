# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/player_shop/office_code/personnel.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def do_commend(self, emp: str) -> int:
            {
            string commender
            if (!_employees[emp])
            {
            await this_player().send(cap_name(emp)+
            " is not an active employee!\n")
            return 1


    def do_demote(self, emp: str) -> int:
            {
            object tp = this_player()
            emp = lower_case(emp)
            if (!_employees[emp])
            {
            await tp.send(cap_name(emp)+ " is not an active employee!\n")
            return 1


    def do_fire(self, args: Any) -> int:
            {
            args[0] = lower_case(args[0])
            if (!_employees[args[0]])
            {
            await this_player().send(cap_name(args[0])+
            " doesn't work at the shop!\n")
            return 1


    def do_leave(self, args: Any) -> int:
            {
            object tp = this_player()
            args[0] = lower_case(args[0])
            if (!_employees[args[0]])
            {
            await tp.send(cap_name(args[0])+ " is not an employee!\n")
            return 1


    def do_retire(self, ) -> int:
            {
            string manager = this_player()->query_name()
            if (!(_employees[manager][EMP_POINTS] & MANAGER)) return 0
            remove_employee(manager)
            _retired += ({manager})
            shop_log(PERSONNEL, manager, "retired from management", UNPAID)
            employee_log(manager, "Retired from management")
            save_me()
            add_succeeded_mess("$N retire$s.\n")
            return 1


    def do_suspend(self, args: Any) -> int:
            {
            string suspender
            object tp = this_player()
            args[0] = lower_case(args[0])
            if (!_employees[args[0]])
            {
            await tp.send(cap_name(args[0])+ " is not an active employee!\n")
            return 1


    def do_warn(self, args: Any) -> int:
            {
            string warner
            object tp = this_player()
            int points
            args[0] = lower_case(args[0])
            if (!_employees[args[0]])
            {
            await tp.send(cap_name(args[0])+ " is not an active employee!\n")
            return 1


    def view_record(self, person: str, pattern: str) -> None:
            {
            if (pattern == VIEW_EMP)
            {
            string text = sprintf("Employment history of %s:\n\n", cap_name(person))
            load_history()
            if (!sizeof(_history) || !_history[person])
            {
            await this_player().send("There is no history for that person.\n")
            return



class Personnel(MudObject):
