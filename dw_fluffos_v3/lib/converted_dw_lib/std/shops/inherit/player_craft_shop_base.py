# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/inherit/player_craft_shop_base.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._round_value = 1
            self._waiting_for_approval = []


    def __init__(self):
            self._round_value = 1
            self._waiting_for_approval = []
            if (!_approved) {
            _approved = [})


    def is_helper(self, person: str) -> int:
            if (!_helpers) {
            _helpers = [})


    def set_maximum_waiting_queue_size(self, size: int) -> None:
            _max_items_in_queue = size


    def query_maximum_waiting_queue_size(self, ) -> int:
            return _max_items_in_queue


    def set_maximum_inventory_size(self, size: int) -> None:
            _maximum_inventory = size


    def query_maximum_inventory_size(self, ) -> int:
            return _maximum_inventory


    def set_parcel_post(self, parcel: str) -> None:
            _parcel_post = parcel


    def query_parcel_post(self, ) -> str:
            return _parcel_post


    def query_royalty(self, person: str) -> int:
            return query_controller()->query_royalty(person)


    def query_owners_money(self, ) -> int:
            return query_royalty(query_owner())


    def adjust_royalty(self, person: str, amount: int) -> None:
            query_controller()->adjust_royalty(person, amount)


    def adjust_owners_money(self, amount: int) -> int:
            return adjust_royalty(query_owner(), amount)


    def set_round_price(self, round: int) -> None:
            _round_value = round


    def query_round_prices(self, ) -> int:
            return _round_value


    def query_number_of_items_listed(self, name: str) -> int:
            int num
            class approval_obs bing
            name = lower_case(name)
            num = sizeof(query_controller()->query_owner_sellables(name))
            foreach (bing in _waiting_for_approval) {
            if (lower_case(bing->seller) == name) {
            num += sizeof(bing->saved)


    def is_allowed_to_use_shop(self, person: str) -> int:
            return (is_allowed(person) || is_helper(person) ||
            is_open_for("use", person))


    def check_open(self, player: MudObject, type: str) -> int:
            if (!::check_open(player)) {
            return 0


    def set_controller(self, name: str) -> None:
            ::set_controller(name)
            query_controller()->set_dont_use_name(1)


    def is_allowed_to_sell(self, obs: MudObject, name: str, sellable_names: str) -> int:
            int num
            int max
            if (_automatic_approval->num_allowed ||
            _sellers[name]) {
            num = query_number_of_items_listed(name) + sizeof(obs)
            if (_sellers[name] && _sellers[name]->max_sellable) {
            max = _sellers[name]->max_sellable
            } else {
            max = _automatic_approval->num_allowed


    def query_maximum_sale_value_both(self, person: str, item: MudObject) -> List[int]:
            int max_deny
            int max_accept
            string short
            class expression_type stuff
            mixed app_item
            if (_sellers[person]) {
            if (_sellers[person]->value_limit) {
            max_accept = _sellers[person]->value_limit


    def query_maximum_sale_value(self, person: str, obs: Any) -> int:
            int* stuff
            object ob
            int cur_deny
            foreach (ob in obs) {
            stuff = query_maximum_sale_value_both(person, ob)
            if (!cur_deny && stuff[1]) {
            cur_deny = stuff[1]
            } else if (cur_deny && cur_deny > stuff[1]) {
            cur_deny = stuff[1]


    def query_extra_price_information(self, seller: str, obs: MudObject) -> str:
            int* max
            int* max_tmp
            string ret
            string place
            object ob
            max = [0, 0]
            foreach (ob in obs) {
            max_tmp = query_maximum_sale_value_both(seller, ob)
            if (max_tmp[0] && max[0] > max_tmp[0]) {
            max[0] = max_tmp[0]


    def destroy_checkout_object(self, ob: MudObject) -> int:
            int id
            int *ids
            int i
            class approval_obs approve
            if (!ob) {
            return 0


    def is_checkout_object(self, ob: MudObject) -> int:
            return ob.query_property(PLAYER_CRAFT_SHOP_CHECK_PROP)


    def remove_from_approval_list(self, approval_obs: Any) -> None:
            int i
            int pos
            for (i = 0; i < sizeof(_approved); i++) {
            if (_approved[i] == approve) {
            foreach (pos in approve->saved) {
            do_save_file(CRAFT_SHOP_REMOVE_DATA_SAVE_FILE,
            0,
            "app_" + pos)


    def query_transaction_string(self, shop_transaction: Any) -> str:
            string ret
            string amt
            string place
            place = query_property("place")
            if (!place) {
            place = "default"


    def query_letter_value(self, pos: int) -> str:
            return sprintf("%c%c", 'A' + (pos / 26), 'A' + (pos % 26))


    def query_number_value(self, letter: str) -> int:
            if (!strlen(letter)) {
            return -1


    def ownership_change(self, old_owner: str, new_owner: str) -> int:
            class parse_node* expr
            if (old_owner == new_owner) {
            return 0


    def check_for_checkout(self, ob: MudObject) -> List[MudObject]:
            object* obs = [})
            if (_something_checkedout && ob) {
            if (living(ob)) {
            obs = filter(deep_inventory(ob), (: is_checkout_object($1) :))
            if (sizeof(obs)) {
            foreach (ob in obs) {
            if (!destroy_checkout_object(ob)) {
            obs -= [ob]


    def verify_destroy_checkout_object(self, ob: MudObject) -> None:
            if (destroy_checkout_object(ob)) {
            tell_room(environment(), ob.the_short() +
            " magically checks itself back in.\n")


    def event_exit(self, ob: MudObject, message: str, to: MudObject) -> None:
            object *obs
            if (ob.query_property("destroy checkout object")) {
            return


    def event_dest_me(self, ob: MudObject) -> None:
            check_for_checkout(ob)


    def return_all_checkedout_objects(self, ) -> None:
            object ob
            object* obs
            if (_something_checkedout) {
            obs = filter(deep_inventory(self), (: is_checkout_object($1) :))
            if (sizeof(obs)) {
            foreach (ob in obs) {
            destroy_checkout_object(ob)


    def dest_me(self, ) -> None:
            ::dest_me()


    def is_able_to_change(self, ob: MudObject) -> int:
            return is_allowed(this_player()->query_name()) ||
            is_helper(this_player()->query_name())


    def do_buy(self, obs: MudObject, force: int) -> int:
            if (!is_open_for("buy", this_player()->query_name()) ||
            !is_open_for("use", this_player()->query_name())) {
            add_failed_mess("You cannot buy anything at this shop.\n")
            return 0


    def do_check_sell(self, obs: MudObject) -> int:
            int *stuff
            object ob
            string ret
            string place
            place = query_property("place")
            if (!place) {
            place = "default"


    def do_list_approval(self, approved: int) -> int:
            class approval_obs approve
            int pos
            int shown
            int allowed
            int checkout
            string place
            string ret
            object* obs
            object *current
            object* result
            string *possible_names
            string start
            mapping result_type
            int i
            int fluff
            place = query_property("place")
            if (!place) {
            place = "default"


    def do_return(self, name: str) -> int:
            object *obs
            object *ok
            object *here
            object *fail
            object *checkout
            object money
            class approval_obs approve
            object ob
            int pos
            int i
            int value
            string place
            approve = query_approval_class(name)
            if (!approve) {
            return 0


    def do_approve_item(self, name: str, money_str: str) -> int:
            int cost
            object *obs
            class approval_obs approve
            string place
            int final_cost
            int num
            if (!is_allowed(this_player()->query_name()) &&
            !is_helper(this_player()->query_name())) {
            add_failed_mess("You are not allowed to approve items.\n")
            return 0


    def reset_weekly_status(self, ) -> None:
            _weekly_stats = new(class weekly_stats)
            _weekly_stats->num_sold = 0
            _weekly_stats->total_cost = 0
            _weekly_stats->total_made = 0
            _weekly_stats->num_bought = 0
            _weekly_stats->helper = ([ ])


    def query_weekly_status_string(self, ) -> str:
            string ret
            string place
            string player
            class helper_stats helpers
            class item_stats items
            string* item_bits
            string item
            int num
            place = query_property("place")
            ret = "$I$0=Total Outgoing  : " +
            MONEY_HAND.money_value_string(_weekly_stats->total_cost, place) + "\n"
            ret += "$I$0=Total Incoming : " +
            MONEY_HAND.money_value_string(_weekly_stats->total_made, place) + "\n"
            if (_weekly_stats->total_made > _weekly_stats->total_cost) {
            ret += "$I$0=Profit of      : " +
            MONEY_HAND.money_value_string(_weekly_stats->total_made - _weekly_stats->total_cost, place) + "\n"
            } else {
            ret += "$I$0=Loss of        : " +
            MONEY_HAND.money_value_string(-(_weekly_stats->total_made - _weekly_stats->total_cost), place) + "\n"


    def do_approve_reject(self, name: str, mess: str, reject_pos: int) -> int:
            object *obs
            object *ok
            object *here
            object *checkout
            object ob
            object play
            class approval_obs approve
            int pos
            int i
            int ret
            string ob_mess
            approve = query_approval_class(name)
            if (!approve) {
            return 0


    def check_reject_note(self, str: str, ob_str: str, name: str) -> None:
            str = lower_case(str)
            if (!strlen(str) ||
            (str[0] != 'y' &&
            str[0] != 'n')) {
            write("Please answer yes or no.\nWould you like to send them "
            "a note about it as well?")
            input_to("check_reject_note", 0, ob_str, name)
            return


    def send_reject_note(self, mess: str, name: str) -> None:
            if (!mess) {
            write("Aborted.\n")
            return


    def do_approve_browse(self, name: str) -> int:
            object *obs
            object ob
            string read
            string ret
            string bits
            class approval_obs approve
            int pos
            string place
            approve = query_approval_class(name)
            if (!approve) {
            return 0


    def do_approve_checkout(self, name: str) -> int:
            object *obs
            object *bad
            object *checkout
            object ob
            class approval_obs approve
            int pos
            int i
            approve = query_approval_class(name)
            if (!approve) {
            return 0


    def do_approve_checkin(self, obs: Any) -> int:
            object ob
            object* ok
            ok = [})
            foreach (ob in obs) {
            if (is_checkout_object(ob)) {
            destroy_checkout_object(ob)
            ok += [ob]


    def do_approve_name_change(self, name: str, new_name: str) -> int:
            class approval_obs approve
            if (!is_allowed(this_player()->query_name()) &&
            !is_helper(this_player()->query_name())) {
            add_failed_mess("You are not allowed to approve items.\n")
            return 0


    def do_approve_category_change(self, name: str, new_category: str) -> int:
            class approval_obs approve
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to approve items.\n")
            return 0


    def do_approve_auto_low(self, cost: str) -> int:
            string place
            int value
            place = query_property("place")
            if (!place) {
            place = "default"


    def do_approve_auto_high(self, cost: str) -> int:
            string place
            int value
            place = query_property("place")
            if (!place) {
            place = "default"


    def do_approve_auto_high_deny(self, cost: str) -> int:
            string place
            int value
            place = query_property("place")
            if (!place) {
            place = "default"


    def do_approve_auto_item_test(self, obs: Any) -> int:
            object ob
            string place
            mixed cost
            int found
            int allowed
            class expression_type stuff
            class parse_node frog
            allowed = is_allowed(this_player()->query_name()) ||
            is_helper(this_player()->query_name())
            place = query_property("place")
            if (!place) {
            place = "default"


    def do_approve_auto_item_remove(self, item: str) -> int:
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to set automatic approval items.\n")
            return 0


    def do_approve_auto_item_remove_object(self, obs: MudObject) -> int:
            object ob
            object *bad
            object *ok
            string name
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to set automatic approval items.\n")
            return 0


    def do_approve_auto_expression_remove(self, idstr: str) -> int:
            class expression_type expr
            int id
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to set automatic approval items.\n")
            return 0


    def do_approve_percentage(self, num: Any) -> int:
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to set automatic approval items.\n")
            return 0


    def do_approve_limit(self, limit: str) -> int:
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to set any limits on selling "
            "items.\n")
            return 0


    def do_approve_limit_person_items(self, name: str, value: str) -> int:
            int amt
            class seller_information info
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to set any limits on selling "
            "items.\n")
            return 0


    def do_approve_limit_person_value(self, name: str, money: str) -> int:
            class seller_information info
            int value
            string place
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to set any limits on selling "
            "items.\n")
            return 0


    def do_approve_limit_person_value_deny(self, name: str, money: str) -> int:
            class seller_information info
            int value
            string place
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to set any limits on selling "
            "items.\n")
            return 0


    def do_approve_limit_person_remove(self, name: str) -> int:
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to remove limits "
            "off someone.\n")
            return 0


    def query_main_status(self, hint: int) -> str:
            string ret
            string place
            string name
            class seller_information stuff
            string *bits
            if (!is_allowed(this_player()->query_name()) &&
            !is_helper(this_player()->query_name())) {
            add_failed_mess("You are not allowed to see the status of this store.\n")
            return 0


    def query_expression_status(self, hint: int) -> str:
            string ret
            string place
            mixed expr
            string str
            int pos
            class expression_type bing
            class expression_type binger
            class approval_item approval
            place = query_property("place")
            if (!place) {
            place = "default"


    def do_main_status(self, hint: int) -> int:
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("Cannot do that!\n")
            return 0


    def do_expression_status(self, hint: int) -> int:
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("Cannot do that!\n")
            return 0


    def do_approve_pay_deficit(self, ) -> int:
            int cost
            string place
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to pay off the deficit for " +
            the_short() + ".\n")
            return 0


    def do_category_description(self, category: str, desc: str) -> int:
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to add categories.\n")
            return 0


    def do_category_information(self, category: str, desc: str) -> int:
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to add categories.\n")
            return 0


    def do_add_new_category(self, category: str) -> int:
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to add categories.\n")
            return 0


    def do_remove_category(self, category: str) -> int:
            object* obs
            string old_cat
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to remove categories.\n")
            return 0


    def do_rename_category(self, category: str, new_category: str) -> int:
            object* obs
            object ob
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to rename categories.\n")
            return 0


    def do_set_default_category(self, default_cat: str) -> int:
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to set the default category.\n")
            return 0


    def do_list_categories(self, ) -> int:
            string cat
            string ret
            ret = ""
            foreach (cat in query_controller()->query_categories()) {
            if (cat == query_default_category()) {
            ret += cat + " (default)\n"
            } else {
            ret += cat + "\n"


    def do_stats_items(self, type: int) -> int:
            class shop_stats stat
            string ret
            string *bits
            string place
            string name
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You cannot read " + the_short() + "'s ledger.\n")
            return 0


    def do_stats_transactions(self, ) -> int:
            class shop_transaction bing
            string ret
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You cannot read " + the_short() + "'s ledger.\n")
            return 0


    def do_stats_money(self, ) -> int:
            string ret
            int stock_value
            string place
            object ob
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You cannot read " + the_short() + "'s ledger.\n")
            return 0


    def do_helper_list(self, ) -> int:
            write("$I$3=The current helpers are: " +
            query_multiple_short(_helpers) + ".\n")
            return 1


    def do_helper_add(self, helper: str) -> int:
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to mess with the helpers.\n")
            return 0


    def do_helper_remove(self, helper: str) -> int:
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to mess with the helpers.\n")
            return 0


    def init(self, ) -> None:
            expression_util::init()
            craft_shop_category::init()
            add_command("waiting", "", (: do_list_approval(1) :))
            add_command("waiting", "unapproved", (: do_list_approval(0) :))
            add_command("reject", "<string'id'>",
            (: do_approve_reject($4[0], 0, -1) :))
            add_command("retrieve", "<string'id'>", (: do_return($4[0]) :) )
            add_command("return", "<string'id'>", (: do_return($4[0]) :) )
            add_command("value", "<indirect:object>",
            (: do_approve_auto_item_test($1) :))
            if (!is_helper(this_player()->query_name())) {
            return



class Player_craft_shop_base(MudObject):

    _round_value = 1

    _waiting_for_approval = '[]'
