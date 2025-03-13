# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/player_shop/counter.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def __init__(self):
            add_item("calculator", "A standard shop's calculator used to total "
            "up all those difficult prices.  To use, see \"syntax calc\".")
            add_help_file("player_shop_counter")


    def init(self, ) -> None:
            {
            ::init()
            if (!_office || _office == "") return
            this_player()->command_override((: action :))
            add_command("calc", "<number> {+|-|*|/} <number>",
            (: do_calc($4[0],$4[1],$4[2]) :))
            if (_office.query_employee(this_player()->query_name()) ||
            this_player()->query_creator())
            {
            add_command("log",
            "shop {bought|sold} <number> <string'item(s)'> for <word'amount'>",
            (: do_log($4) :))
            add_command("correction",
            "shop {bought|sold} <number> <string'item(s)'> for <word'amount'>",
            (: do_correction($4) :))


    def action(self, str: str) -> int:
            {
            string st1
            if (_office.query_employee(this_player()->query_name()) ||
            this_player()->query_creator())
            return 0
            sscanf(str,"%s %s",str,st1)
            if(str == "get" || str == "take")
            if (strsrch(st1, "register") != -1)
            {
            await this_player().send("You are not an active employee here!\n")
            return 1


    def add_money_ob(self, money: MudObject) -> None:
            {
            if (previous_object() && previous_object() != find_object(_office))
            {
            LOG_ERROR("counter.c", "add_money_ob()")
            return


    def adjust_register(self, player: str, amount: int) -> int:
            {
            int value
            object cash, change
            if (previous_object() && previous_object() != find_object(_office))
            {
            LOG_ERROR("counter.c", "adjust_register(" + player+","+amount+")")
            return 0


    def directions_to(self, place: str) -> str:
            {
            if (place == _storeroom) return _store_dir
            if (place == _office) return _office_dir
            if (place == _shop_front) return _shop_dir
            return "here"


    def event_death(self, k: MudObject, o: MudObject, k2: MudObject, r: str, k3: str) -> None:
            {
            _office.event_death(k, o, k2, r, k3)


    def event_enter(self, ob: MudObject, message: str, from: MudObject) -> None:
            {
            _office.event_enter(ob, message, from)


    def query_register(self, ) -> int:
            {
            object cash = present(MONEY_ALIAS, _register)
            if (!cash) return 0
            _money = cash.query_money_array() + ({})
            return MONEY_HAND.query_total_value(_money, _place)


    def save_register(self, no_player: int) -> None:
            {
            remove_asyncio.create_task(self._call_save)
            _call_save = asyncio.create_task(self.(: save_me($((!no_player)?
            this_player()->query_name():"shop")) :), 1)



class Counter(MudObject):
