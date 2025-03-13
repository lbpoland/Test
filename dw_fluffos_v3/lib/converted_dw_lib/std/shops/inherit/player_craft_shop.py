# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/inherit/player_craft_shop.c (2003 FluffOS v3) for Forgotten Realms MUD
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


    def set_shop_name(self, name: str) -> None:
            _shop_name = name
            add_property("determinate", "")
            set_short(_shop_name)


    def query_shop_name(self, ) -> str:
            return _shop_name


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


    def query_royalty(self, name: str) -> int:
            return query_controller()->query_royalty(name)


    def adjust_royalty(self, name: str, amount: int) -> None:
            query_controller()->adjust_royalty(name, amount)


    def is_allowed_to_use_shop(self, person: str) -> int:
            class parse_node frog
            if (is_allowed(person) || !sizeof(_use_expression)) {
            return 1


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
            if (_something_checkedout) {
            if (living(ob)) {
            obs = filter(deep_inventory(ob), (: is_checkout_object($1) :))
            } else {
            if (is_checkout_object(ob)) {
            obs = [ob]


    def event_exit(self, ob: MudObject, message: str, to: MudObject) -> None:
            object *obs
            obs = check_for_checkout(ob)
            if (sizeof(obs)) {
            tell_object(ob, "You suddenly find the uncheckout items " +
            query_multiple_short(obs) + " check themselves "
            "back in.\n")
            obs.move("/room/rubbish")


    def event_dest_me(self, ob: MudObject) -> None:
            check_for_checkout(ob)
            if (_sign_ob) {
            _sign_ob.dest_me()


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
            return is_allowed(this_player()->query_name())


    def query_owners_money(self, ) -> int:
            return query_royalty(query_owner())


    def adjust_owners_money(self, amt: int) -> None:
            adjust_royalty(query_owner(), amt)


    def query_sign_object(self, ) -> MudObject:
            object* obs
            if (!_sign_ob && _auto_load_sign_str && !_broken_sign) {
            if (catch(obs = PLAYER_OB.load_auto_load_to_array(_auto_load_sign_str))) {
            _broken_sign = 1
            } else {
            if (sizeof(obs)) {
            _sign_ob = obs[0]
            _sign_ob.reset_get()
            } else {
            _broken_sign = 1


    def set_sign_object(self, ob: MudObject) -> None:
            if (ob) {
            _auto_load_sign_str = PLAYER_OB.create_auto_load([ob])
            ob.reset_get()
            } else {
            _auto_load_sign_str = 0


    def do_buy(self, obs: MudObject) -> int:
            int status
            if (!evaluate_expression(_buy_expression, this_player()->query_name(), 0, [}), 0, 0)->value &&
            !is_allowed_to_use_shop(this_player()->query_name())) {
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
            int i
            int fluff
            string place
            string ret
            object* obs
            object *current
            object* result
            string *possible_names
            string start
            mapping result_type
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
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to approve items.\n")
            return 0


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
            if (!is_allowed(this_player()->query_name())) {
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
            allowed = is_allowed(this_player()->query_name())
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


    def do_approve_black_list_add(self, name: str) -> int:
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to add people to the black list.\n")
            return 0


    def do_approve_black_list_add_ignore(self, ) -> int:
            string *people
            string *bad
            string *ok
            string name
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to add people to the black list.\n")
            return 0


    def do_approve_black_list_remove(self, name: str) -> int:
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to remove people from "
            "the black list.\n")
            return 0


    def do_user_function_add(self, def: str, expr: str) -> int:
            string name
            if (this_player()->query_name() != "presto")
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to add functions to this store.\n")
            return 0


    def do_user_function_remove(self, name: str) -> int:
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to remove functions from this store.\n")
            return 0


    def do_approve_status_internal_functions(self, ) -> int:
            string* names
            string name
            string ret
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to see the status of this store.\n")
            return 0


    def do_function_help(self, name: str) -> int:
            string nroff_fn
            string str
            string fname
            fname = CRAFT_SHOP_EXPRESSION_HELP_DIR + name
            if (file_size(fname) <= 0) {
            add_failed_mess("There is no help for the function '" + name + "'.\n")
            return 0


    def do_function_help_list(self, ) -> int:
            string *names
            names = get_dir(CRAFT_SHOP_EXPRESSION_HELP_DIR)
            if (!sizeof(names)) {
            add_failed_mess("There is no help on any functions.\n")
            return 0


    def do_approve_status_functions(self, hints: int) -> int:
            string* names
            string name
            string ret
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to see the status of this store.\n")
            return 0


    def do_approve_status(self, status: int) -> int:
            string ret
            string place
            mixed expr
            string str
            string name
            class seller_information stuff
            string *bits
            int pos
            int hint
            int show_expr
            class expression_type bing
            class expression_type binger
            class approval_item approval
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to see the status of this store.\n")
            return 0


    def do_approve_pay_deficit(self, ) -> int:
            int cost
            string place
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to pay off the deficit for " +
            the_short() + ".\n")
            return 0


    def do_approve_buy_expression(self, str: str) -> int:
            class parse_node* expr
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to add restrictions to the shop.\n")
            return 0


    def do_approve_use_expression(self, str: str) -> int:
            class parse_node* expr
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to add restrictions to the shop.\n")
            return 0


    def do_add_new_category(self, category: str) -> int:
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to add categories.\n")
            return 0


    def do_remove_category(self, category: str) -> int:
            object* obs
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


    def do_name_shop(self, name: str) -> int:
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You cannot set the name of " + the_short() + ".\n")
            return 0


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


    def do_set_sign(self, obs: Any) -> int:
            object ob
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You cannot set the sign for the shop.\n")
            return 0


    def do_remove_sign(self, ) -> int:
            object ob
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You cannot set the sign for the shop.\n")
            return 0


    def do_collect_partial_royalties(self, amount: str) -> int:
            int amt
            string place
            if (query_owner() != this_player()->query_name()) {
            add_failed_mess("Only the owner can do this.\n")
            return 0


    def inform_of_royalties(self, player: MudObject) -> None:
            if (player && environment(player) == self) {
            await player.send("You have some royalties to pick up.\n")


    def init(self, ) -> None:
            if (query_controller()->query_royalty(this_player()->query_name())) {
            asyncio.create_task(self."inform_of_royalties", 5)



class Player_craft_shop(MudObject):

    _round_value = 1

    _waiting_for_approval = '[]'
