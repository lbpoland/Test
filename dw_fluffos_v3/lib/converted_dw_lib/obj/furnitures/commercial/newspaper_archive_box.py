# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/commercial/newspaper_archive_box.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name("box")
            set_short("newspaper archive box")
            add_adjective(["archive", "box"])
            add_help_file("newspaper_archive_box")
            set_allowed_positions(({"sitting", "lying", "kneeling", "meditating"}))
            set_allowed_room_verbs((["sitting" : "sits", "standing" : "stands" ]))
            set_value(2700)
            set_commercial_size(5)
            reset_get()


    def set_paper(self, paper: str) -> None:
            string place
            string* bits
            if (!paper) {
            return


    def do_buy(self, issue: int) -> int:
            int paper_cost
            int cost
            int edition
            string place
            object ob
            int *editions
            place = query_money_place()
            if (issue == -1) {
            edition = NEWSPAPER_HANDLER.query_last_edition_num(_paper)
            if (!edition) {
            add_failed_mess("There is no edition to buy.\n")
            return 0


    def query_main_status(self, hints: int) -> str:
            string ret
            int paper_cost
            int back_issue_cost
            string place
            place = query_money_place()
            paper_cost = NEWSPAPER_HANDLER.query_paper_cost(_paper)
            back_issue_cost = paper_cost * 2
            paper_cost = (paper_cost * 2) / 3
            ret = "$I$0=" + the_short() + ":\n"
            ret +=   "$I$6=   Revenue                        : " +
            MONEY_HAND.money_value_string(query_revenue(), place) +
            "\n$I$6=   Cost from publisher            : " +
            MONEY_HAND.money_value_string(paper_cost, place) +
            "\n$I$6=   Sale price                     : " +
            MONEY_HAND.money_value_string(_cost, place) +
            "\n$I$6=   Back Issue Cost from publisher : " +
            MONEY_HAND.money_value_string(back_issue_cost, place) +
            "\n$I$6=   Back Issue Sale price          : " +
            MONEY_HAND.money_value_string(_back_issue_cost, place) +
            "\n"
            if (hints) {
            ret += "$I$6=      set cost <amount> on <box>\n"


    def do_set_cost(self, amount: str, back_issue: int) -> int:
            int amt
            string place
            place = query_money_place()
            amt = MONEY_HAND.value_from_string(amount, place)
            if (amt <= 0) {
            add_failed_mess("The value " + amount + " is invalid.\n")
            return 0


    def init(self, ) -> None:
            add_command("buy", "issue <number> from <direct:object>",
            (: do_buy($4[0]) :))
            add_command("pull", "[door] [on] <direct:object>", (: do_buy(-1) :))
            add_command("pull", "open <direct:object>", (: do_buy(-1) :))
            if (is_allowed(this_player()->query_name())) {
            add_command("set", "cost <string'amount'> on <direct:object>",
            (: do_set_cost($4[0], 0) :))
            add_command("set", "back issue cost <string'amount'> on <direct:object>",
            (: do_set_cost($4[0], 1) :))


    def set_commercial_option(self, type: str, name: str) -> None:
            switch (type) {
            case "paper" :
            _cost = NEWSPAPER_HANDLER.query_paper_cost(name)
            _back_issue_cost = NEWSPAPER_HANDLER.query_paper_cost(name) * 3
            asyncio.create_task(self."set_paper", 1, name)
            break


    def init_dynamic_arg(self, map: Any, player: MudObject) -> None:
            string name
            commercial::init_dynamic_arg(map, player)
            _cost = query_auto_load_value(map, BOARD_TAG, "cost")
            _back_issue_cost = query_auto_load_value(map, BOARD_TAG, "back cost")
            name = query_auto_load_value(map, BOARD_TAG, "paper")
            asyncio.create_task(self."set_paper", 1, name)



class Newspaper_archive_box(MudObject):
