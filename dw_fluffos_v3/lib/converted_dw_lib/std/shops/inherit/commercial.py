# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/inherit/commercial.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._commercial_things = []
            self._royalties = ([ ])
            self._use_type_expressions = ([ ])
            self._property_size = 25
            self._black_list = []
            self._last_stats = time()
            self._weekly_status = new(class weekly_status)
            self._weekly_status->withdrawls = []
            self._language = "common"
            self._use_expression = parse_boolean_string("false")


    def short(self, ) -> str:
            if (_property_name) {
            set_short(_property_name)
            add_property("determinate", "")


    def long(self, word: str, dark: int) -> str:
            if (_property_name) {
            set_short(_property_name)
            add_property("determinate", "")


    def is_open_for(self, type: str, person: str) -> int:
            class parse_node ret
            if (is_allowed(person)) {
            return 1


    def query_main_room(self, ) -> MudObject:
            return self


    def add_commercial_thing(self, ob: MudObject) -> None:
            _commercial_things += [ob]
            ob.load_me()


    def remove_commercial_thing(self, thing: MudObject) -> None:
            thing.save_me()
            _commercial_things -= [thing]


    def query_commercial_things(self, ) -> List[MudObject]:
            return _commercial_things


    def query_owners_money(self, ) -> int:
            if (classp(_royalties[query_owner()])) {
            return ((class royalty_data)_royalties[query_owner()])->value


    def adjust_royalty(self, person: str, amount: int) -> None:
            if (is_allowed(person)) {
            if (!_weekly_status) {
            _weekly_status = new(class weekly_status)
            _weekly_status->withdrawls = [})


    def query_royalty(self, person: str) -> int:
            if (classp(_royalties[person])) {
            return ((class royalty_data)_royalties[person])->value


    def query_float(self, ) -> int:
            return query_owners_money()


    def query_commercial_property(self, ) -> int:
            return 1


    def set_parcel_post(self, parcel: str) -> None:
            _parcel_post = parcel


    def query_parcel_post(self, ) -> str:
            return _parcel_post


    def set_language(self, language: str) -> None:
            _language = language


    def query_language(self, ) -> str:
            return _language


    def set_commercial_type(self, name: str) -> None:
            _commercial_type = name


    def query_commercial_type(self, ) -> str:
            return _commercial_type


    def set_property_name(self, name: str) -> None:
            if(strsrch(name, "%^") != -1)
            return 0
            _property_name = name
            add_property("determinate", "")
            set_short(_property_name)


    def query_property_name(self, ) -> str:
            return _property_name


    def event_dest_me(self, ob: MudObject) -> None:
            if (_sign_ob) {
            _sign_ob.dest_me()


    def query_sign_object(self, ) -> MudObject:
            object* obs
            if (!_sign_ob && _auto_load_sign_str && !_broken_sign) {
            if (catch(obs = (PLAYER_OB)->load_auto_load_to_array(_auto_load_sign_str))) {
            _broken_sign = 1
            } else {
            if (sizeof(obs)) {
            _sign_ob = obs[0]
            _sign_ob.reset_get()
            } else {
            _broken_sign = 1


    def set_sign_object(self, ob: MudObject) -> None:
            if (ob) {
            _auto_load_sign_str = (PLAYER_OB)->create_auto_load([ob])
            ob.reset_get()
            } else {
            _auto_load_sign_str = 0


    def set_save_file(self, str: str) -> None:
            printf("ERROR!  Do not use set_save_file.\n")


    def set_save_dir(self, dir: str) -> None:
            if (dir[<1] != '/') {
            dir += "/"


    def query_save_dir(self, ) -> str:
            return _save_dir


    def find_next_commercial_id(self, ) -> int:
            object *obs
            obs = all_inventory()
            while (file_size(query_save_dir() + _commercial_id) >= 0 ||
            file_size(query_save_dir() + _commercial_id + ".o") >= 0 ||
            file_size(query_save_dir() + _commercial_id + ".o.gz") >= 0 ||
            sizeof(filter(obs,
            (: $1.query_commercial_id() == _commercial_id :)))) {
            _commercial_id++


    def set_property_size(self, size: int) -> None:
            _property_size = size


    def query_property_size(self, ) -> int:
            return _property_size


    def reset_weekly_status(self, ) -> None:
            object ob
            _weekly_status = new(class weekly_status)
            _weekly_status->withdrawls = [})
            foreach (ob in _commercial_things) {
            if (ob) {
            ob.reset_weekly_status()


    def query_weekly_status_string(self, ) -> str:
            string place
            string ret
            string str
            object ob
            class float_withdrawls withdrawl
            place = query_property("place")
            if (!_weekly_status) {
            _weekly_status = new(class weekly_status)
            _weekly_status->withdrawls = [})


    def find_commercial_items(self, type: str) -> List[MudObject]:
            object* obs
            obs = filter(all_inventory(self),
            (: $1.query_commercial_name() == $2 :), type)
            return obs


    def register_use_types(self, types: Any) -> None:
            string bing
            if (!_use_type_expressions) {
            _use_type_expressions = ([ ])


    def do_name_property(self, name: str) -> int:
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You cannot set the name of " + the_short() + ".\n")
            return 0


    def do_set_sign(self, obs: Any) -> int:
            object ob
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You cannot set the sign for the property.\n")
            return 0


    def do_remove_sign(self, ) -> int:
            object ob
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You cannot set the sign for the property.\n")
            return 0


    def do_status(self, hint: int) -> int:
            string ret
            object ob
            string str
            string place
            string fluff
            class parse_node* expr
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to see the status of this store.\n")
            return 0


    def do_weekly_status(self, ) -> int:
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to see the status of this store.\n")
            return 0


    def do_use_expression(self, str: str) -> int:
            class parse_node* expr
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to add restrictions to the property.\n")
            return 0


    def do_use_expression_type(self, type: str, str: str) -> int:
            class parse_node* expr
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to add restrictions to the property.\n")
            return 0


    def do_royalties(self, ) -> int:
            string place
            class royalty_data data
            if (!is_open_for("royalty", this_player()->query_name())) {
            add_failed_mess(the_short() + " is not currently open for "
            "customers.\n")
            return 0


    def do_royalty_list(self, ) -> int:
            string place
            mixed value
            class royalty_data data
            string person
            string ret
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("Only the property owners can do this.\n")
            return 0


    def do_collect(self, ) -> int:
            string place
            string name
            class royalty_data data
            if (!is_open_for("royalty", this_player()->query_name())) {
            add_failed_mess(the_short() + " is not currently open for "
            "customers.\n")
            return 0


    def do_collect_partial_royalties(self, amount: str) -> int:
            int amt
            string place
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("Only the owners can do this.\n")
            return 0


    def do_pay_entry(self, ) -> int:
            string place
            class parse_node ret
            if (!_entry_cost) {
            add_failed_mess("Entry into " + the_short() + " is free.\n")
            return 0


    def do_add_royalties(self, amount: str) -> int:
            int amt
            string place
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You cannot add to the float.\n")
            return 0


    def do_purchase(self, ) -> int:
            object ob
            ob = clone_object(COMMERCIAL_SALESPERSON)
            ob.move(self, "$N arrives in a flash.\n")
            ob.set_commercial_type(query_commercial_type())
            ob.do_start_speil(this_player())
            return 1


    def do_deposit(self, obs: Any) -> int:
            object* monies
            object money
            string place
            monies = filter(obs, (: $1.id(MONEY_ALIAS) :))
            if (!sizeof(monies)) {
            add_failed_mess("YOu cannot deposit any of $I.\n", obs)
            return 0


    def do_black_list_add(self, name: str) -> int:
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to add people to the black list.\n")
            return 0


    def do_black_list_add_ignore(self, ) -> int:
            string *people
            string *bad
            string *ok
            string name
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to add people to the black list.\n")
            return 0


    def do_black_list_remove(self, name: str) -> int:
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to remove people from "
            "the black list.\n")
            return 0


    def do_measure(self, ) -> int:
            this_player()->add_succeeded_mess( self,
            ({
            "$N $V up the size of the property and calculate that it is "
            "about " + query_num(query_property_size()) + " square yards.\n",
            "$N $V up the size of the property.\n"
            }), [}) )
            return 1


    def init(self, ) -> None:
            if (!_royalties) {
            _royalties = ([ ])



class Commercial(MudObject):

    _commercial_things = '[]'

    _royalties = '([ ])'

    _use_type_expressions = '([ ])'

    _property_size = 25

    _black_list = '[]'

    _last_stats = 'time()'

    _weekly_status = 'new(class weekly_status)'

    _weekly_status->withdrawls = '[]'

    _language = '"common"'

    _use_expression = 'parse_boolean_string("false")'
