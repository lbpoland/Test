# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/controllers/craft_shop_controller.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._sell_list = clone_object("/std/container")
            self._current_save_num = 1
            self._current_ids = []
            self._categories = ([ ])


    def set_dont_use_name(self, flag: int) -> None:
            _category_dont_use_name = flag


    def query_dont_use_name(self, ) -> int:
            return _category_dont_use_name


    def remove_list_object(self, name: str, owner: str, craft_object: Any) -> None:
            int i
            object us
            class craft_object *data
            if (_sellables[name] &&
            ((class craft_sellable)_sellables[name])->objects[owner]) {
            data = ((class craft_sellable)_sellables[name])->objects[owner]
            for (i = 0; i < sizeof(data); i++) {
            if (data[i] == ob) {
            break


    def create_real_object(self, player: MudObject, craft_object: Any) -> MudObject:
            return create_real_auto_load_object(craft->ob_num, player)


    def query_owner_of_shop_object(self, ob: MudObject) -> str:
            return ob.query_property(SELL_OBJECT_OWNER_PROP)


    def query_name_of_shop_object(self, ob: MudObject) -> str:
            return ob.query_property(SELL_OBJECT_NAME_PROP)


    def query_id_of_shop_object(self, ob: MudObject) -> str:
            return ob.query_property(SELL_OBJECT_ID_PROP)


    def set_id_of_shop_objects(self, obs: MudObject, id: str) -> None:
            obs.add_property(SELL_OBJECT_ID_PROP, id)
            obs.add_alias(id)


    def query_category_of_shop_object(self, ob: MudObject) -> str:
            class craft_object craft
            craft = query_class_of_shop_object(ob)
            if (craft) {
            return craft->category


    def query_short_of_shop_object(self, ob: MudObject) -> str:
            class craft_object craft
            craft = query_class_of_shop_object(ob)
            if (craft) {
            if (sizeof(craft) == 5) {
            return craft->short


    def update_craft_object(self, craft_ob: MudObject, replacement_ob: MudObject) -> None:
            class craft_object craft
            craft = query_class_of_shop_object(craft_ob)
            if (craft) {
            create_auto_load_file(replacement_ob, craft->ob_num)


    def query_next_shop_id(self, ) -> str:
            int num
            num = 0
            while (_current_ids.index(num) if num in _current_ids else -1 != -1) {
            num++


    def remove_shop_id(self, id: str) -> None:
            int real_id
            real_id = (id[0] * 26) - 'a' + id[1] - 'a'
            _current_ids -= [real_id]


    def find_shop_object(self, craft_object: Any) -> MudObject:
            object ob
            foreach (ob in query_sell_list_obs()) {
            if (query_class_of_shop_object(ob) == frog) {
            return ob


    def change_value_of_shop_object(self, ob: MudObject, value: int) -> None:
            string owner
            string name
            class craft_object wombat
            object* obs
            obs = query_items_with_shop_id(query_id_of_shop_object(ob))
            foreach (ob in obs) {
            owner = query_owner_of_shop_object(ob)
            name = query_name_of_shop_object(ob)
            wombat = query_class_of_shop_object(ob)
            wombat->cost = value
            ob.set_value(value)


    def change_category_of_shop_object(self, ob: MudObject, new_category: str) -> int:
            string owner
            string name
            class craft_object bing
            object* obs
            int do_save
            obs = query_items_with_shop_id(query_id_of_shop_object(ob))
            foreach (ob in obs) {
            owner = query_owner_of_shop_object(ob)
            name = query_name_of_shop_object(ob)
            if (!_sellables[name] ||
            !((class craft_sellable)_sellables[name])->objects[owner]) {
            return 0


    def remove_shop_object(self, ob: MudObject) -> None:
            string name
            string owner
            owner = query_owner_of_shop_object(ob)
            name = query_name_of_shop_object(ob)
            remove_list_object(name, owner, query_class_of_shop_object(ob))


    def value_of_objects(self, obs: MudObject) -> int:
            object ob
            class craft_object craft
            int value
            foreach (ob in obs) {
            craft = query_class_of_shop_object(ob)
            if (craft) {
            value += craft->cost


    def delete_objects(self, id: str) -> None:
            object ob, *obs
            obs = all_inventory( _sell_list )
            obs = filter( obs,
            (: $1.query_property( SELL_OBJECT_ID_PROP ) == $(id) :) )
            foreach( ob in obs ) {
            remove_shop_object( ob )


    def query_sell_list(self, ) -> MudObject:
            return _sell_list


    def query_items_with_shop_id(self, id: str) -> List[MudObject]:
            return filter(query_sell_list_obs(), (: query_id_of_shop_object($1) == $2 :),
            id)


    def query_list_object_cost(self, name: str, owner: str) -> int:
            class craft_sellable sell
            class craft_object wombat
            owner = lower_case(owner)
            if (_sellables[name]) {
            sell = _sellables[name]
            if (sell->objects[owner]) {
            wombat = sell->objects[owner][0]
            return wombat->cost


    def set_save_function(self, func: Any) -> None:
            _save_function = func


    def set_load_function(self, func: Any) -> None:
            _load_function = func


    def set_category_function(self, func: Any) -> None:
            _category_function = func


    def save_it(self, ) -> None:
            if (_has_loaded) {
            evaluate(_save_function, CRAFT_SHOP_MAIN_SAVE_FILE,
            [_sellables, _royalties, _current_save_num, _categories] )


    def load_it(self, ) -> None:
            mixed *map
            string name
            _has_loaded = 1
            map = evaluate(_load_function, CRAFT_SHOP_MAIN_SAVE_FILE)
            if (pointerp(map) && sizeof(map) == 3) {
            _sellables = map[0]
            _royalties = map[1]
            _current_save_num = map[2]
            foreach (name in keys(_sellables)) {
            reset_eval_cost()
            update_sellable(name)


    def adjust_royalty(self, player: str, amt: int) -> None:
            _royalties[player] += amt
            save_it()


    def query_royalty(self, player: str) -> int:
            return _royalties[player]


    def pay_out_royalty(self, player: str, place: str, amount: int) -> None:
            object pl
            pl = find_player(player)
            if (pl && _royalties[player]) {
            if (!amount) {
            amount = _royalties[player]


    def is_valid_category(self, category: str) -> int:
            if (_categories[category] &&
            (_categories[category]->state == CRAFT_CATEGORY_STATE_ACCEPTED ||
            _categories[category]->state == CRAFT_CATEGORY_STATE_DELETEING)) {
            return 1


    def remove_category_accepted(self, category: str) -> int:
            if (_categories[category]) {
            map_delete(_categories, category)
            save_it()
            return 1


    def add_category_accepted(self, name: str) -> int:
            if (!_categories[name]) {
            _categories[name] = new(class craft_category)
            _categories[name]->state = CRAFT_CATEGORY_STATE_ACCEPTED
            _categories[name]->voted = [})
            _categories[name]->description = 0
            _categories[name]->yes = 0
            _categories[name]->no = 0
            _categories[name]->timeout = 0
            save_it()
            return 1


    def set_category_description(self, cat: str, desc: str) -> None:
            if (_categories[cat]) {
            _categories[cat]->description = desc
            save_it()


    def query_category_description(self, cat: str) -> str:
            if (_categories[cat]) {
            if (stringp(_categories[cat]->description)) {
            return _categories[cat]->description


    def set_category_information(self, cat: str, info: str) -> None:
            if (_categories[cat]) {
            _categories[cat]->information = info
            save_it()


    def query_category_information(self, cat: str) -> str:
            if (_categories[cat]) {
            if (stringp(_categories[cat]->information)) {
            return _categories[cat]->information


    def query_category_of(self, name: str, owner: str) -> str:
            if (_sellables[name] &&
            sizeof( ((class craft_sellable)_sellables[name])->objects[owner])) {
            return ((class craft_sellable)_sellables[name])->objects[owner][0]->category


    def query_category_timeout(self, name: str) -> int:
            if (_categories[name]) {
            return _categories[name]->timeout


    def dest_me(self, ) -> None:
            if(_sell_list) {
            all_inventory(_sell_list)->move("/room/rubbish")
            _sell_list.dest_me()



class Craft_shop_controller(MudObject):

    _sell_list = 'clone_object("/std/container")'

    _current_save_num = 1

    _current_ids = '[]'

    _categories = '([ ])'
