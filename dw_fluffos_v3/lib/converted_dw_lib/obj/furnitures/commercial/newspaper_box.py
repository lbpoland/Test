# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/commercial/newspaper_box.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("box")
            set_short("newspaper box")
            add_adjective("box")
            add_help_file("newspaper_box")
            set_allowed_positions(({"sitting", "lying", "kneeling", "meditating"}))
            set_allowed_room_verbs((["sitting" : "sits", "standing" : "stands" ]))
            set_value(900)
            set_commercial_size(1)
            reset_get()


    def set_paper(self, paper: str) -> None:
            string place
            string* bits
            if (!paper) {
            return


    def do_buy(self, ) -> int:
            int paper_cost
            int cost
            int edition
            string place
            object ob
            int *editions
            place = query_money_place()
            cost = _cost
            paper_cost = (NEWSPAPER_HANDLER.query_paper_cost(_paper) * 2) / 3
            edition = NEWSPAPER_HANDLER.query_last_edition_num(_paper)
            if (!edition) {
            add_failed_mess("There is no edition to buy.\n")
            return 0


    def query_main_status(self, hints: int) -> str:
            string ret
            int paper_cost
            string place
            place = query_money_place()
            paper_cost = (NEWSPAPER_HANDLER.query_paper_cost(_paper) * 2) / 3
            ret = the_short() + ":\n"
            ret +=   "$I$6=   Revenue             : " +
            MONEY_HAND.money_value_string(query_revenue(), place) +
            "\n$I$6=   Cost from publisher : " +
            MONEY_HAND.money_value_string(paper_cost, place) +
            "\n$I$6=   Sale price          : " +
            MONEY_HAND.money_value_string(_cost, place) +
            "\n"
            if (hints) {
            ret += "$I$6=      set cost <amount> on <box>\n"


    def do_set_cost(self, amount: str) -> int:
            int amt
            string place
            place = query_money_place()
            amt = MONEY_HAND.value_from_string(amount, place)
            if (amt <= 0) {
            add_failed_mess("The value " + amount + " is invalid.\n")
            return 0


    def init(self, ) -> None:
            add_command("buy", "paper from <direct:object>", (: do_buy() :))
            add_command("pull", "[door] [on] <direct:object>", (: do_buy() :))
            add_command("pull", "open <direct:object>", (: do_buy() :))
            if (is_allowed(this_player()->query_name())) {
            add_command("set", "cost <string'amount'> on <direct:object>",
            (: do_set_cost($4[0]) :))


    def set_commercial_option(self, type: str, name: str) -> None:
            switch (type) {
            case "paper" :
            _cost = NEWSPAPER_HANDLER.query_paper_cost(name)
            asyncio.create_task(self."set_paper", 1, name)
            break


    def init_dynamic_arg(self, map: Any, player: MudObject) -> None:
            string name
            commercial::init_dynamic_arg(map, player)
            _cost = query_auto_load_value(map, BOARD_TAG, "cost")
            name = query_auto_load_value(map, BOARD_TAG, "paper")
            asyncio.create_task(self."set_paper", 1, name)



class Newspaper_box(MudObject):
