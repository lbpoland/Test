# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/general_shop.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from .combat import combat_handler
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.buy_mess = []
            self.sell_mess = []
            self.list_mess = "$extra$"
            self.value_mess = "$ob$ is valued at $money$.\n"
            self.too_costly_mess = "$ob$ is worth too much to be sold here.\n"
            self.not_worthy_mess = "$ob$ is not worth enough to be sold here.\n"
            self.browse_mess = "$ob$ costs $money$, it looks like:\n$extra$"
            self.other_shops = []
            self.max_inventory = MAX_INVENTORY
            self.min_amount = 50
            self._strict_currency = 1


    def reset(self, ) -> None:
            if(!random(3)) {
            remove_property("inventory_loss")


    def set_buy_function(self, func: Any) -> None:
            if (stringp(func) || functionp(func)) {
            buy_func = func


    def set_sell_function(self, func: Any) -> None:
            if (stringp(func) || functionp(func)) {
            sell_func = func


    def set_value_function(self, func: Any) -> None:
            if (stringp(func) || functionp(func)) {
            value_func = func


    def set_too_costly_function(self, func: Any) -> None:
            if (stringp(func) || functionp(func)) {
            too_costly_func = func


    def set_cannot_sell_function(self, func: Any) -> None:
            if (stringp(func) || functionp(func)) {
            cannot_sell_func = func


    def set_browse_function(self, func: Any) -> None:
            if (stringp(func) || functionp(func)) {
            browse_func = func


    def set_list_function(self, func: Any) -> None:
            if (stringp(func) || functionp(func)) {
            list_func = func


    def set_sell_message(self, str: Any) -> None:
            sell_mess = str


    def set_buy_message(self, str: Any) -> None:
            buy_mess = str


    def set_value_message(self, str: Any) -> None:
            value_mess = str


    def set_too_costly_message(self, str: Any) -> None:
            too_costly_mess = str


    def set_not_worthy_message(self, str: Any) -> None:
            not_worthy_mess = str


    def set_browse_message(self, str: Any) -> None:
            browse_mess = str


    def set_list_message(self, str: Any) -> None:
            list_mess = str


    def set_open_condition(self, str: Any) -> None:
            if (functionp(str)) {
            ::set_open_function(str)
            } else if (intp(str)) {
            ::set_open_function( (: $(str) :) )
            } else if (pointerp(str)) {
            ::set_open_function( (: call_other($(str[0]), $(str[1]), $1) :) )
            } if ( stringp(str) ) {
            ::set_open_function( (: call_other( self, $(str), $1 ) :) )


    def set_no_steal(self, i: int) -> None:
            no_steal = i


    def set_steal_difficulty(self, i: int) -> None:
            steal_difficulty = i


    def set_sell_stolen(self, i: int) -> None:
            sell_stolen = i
            no_steal = 1


    def query_sell_mess(self, ) -> Any:
            return sell_mess


    def query_list_mess(self, ) -> Any:
            return list_mess


    def query_value_mess(self, ) -> Any:
            return value_mess


    def query_too_costly_mess(self, ) -> Any:
            return too_costly_mess


    def query_not_worthy_mess(self, ) -> Any:
            return not_worthy_mess


    def query_buy_mess(self, ) -> Any:
            return buy_mess


    def query_browse_mess(self, ) -> Any:
            return browse_mess


    def query_no_steal(self, ) -> int:
            return no_steal


    def query_steal_difficulty(self, i: int) -> int:
            return steal_difficulty


    def query_shoplift_response_handler(self, ) -> str:
            return shoplift_handler


    def query_shop(self, ) -> int:
            return 1


    def shoplift_success(self, ob: MudObject) -> MudObject:
            return ob


    def set_shoplift_response_handler(self, word: str) -> None:
            shoplift_handler = word


    def init(self, ) -> None:
            string room
            ::init()
            if(stringp(our_storeroom)) {
            room = our_storeroom
            } else if(our_storeroom) {
            room = file_name(our_storeroom)
            } else {
            tell_room(self,
            "Oh dear, we don't seem to have a storeroom.\n")


    def query_max_amount(self, ) -> int:
            return MAX_AMOUNT


    def query_min_amount(self, ) -> int:
            return min_amount


    def scaled_value(self, n: int) -> int:
            int i, tot, *fish
            fish = PAY_RATES
            if(n < fish[0]) {
            return n
            } else {
            tot = fish[0]
            n -= fish[0]


    def do_sell(self, in_obs: MudObject) -> int:
            int i, amt, total_amt
            string place, filename, *text = [})
            object money, *obs, *selling, *cannot, *stolen, storeob, one_item, *cre
            object thing
            mixed *m_array
            if(!is_open(this_player(), 0)) {
            return 0


    def creator_object(self, ob: MudObject) -> int:
            string path
            if ( file_name( ob )[0..2] == "/w/" ) {
            return 1


    def do_buy(self, obs: MudObject) -> int:
            int i, amt, ob_amt, total_cost
            string place
            object money, *to_buy, *cannot, *too_much
            object *creator_obs
            if(!is_open(this_player(), 0)) {
            return 0


    def do_buy_things(self, obs: MudObject, cost: int, pl: MudObject) -> None:
            int i, j
            string place
            object money, change
            mixed m_array, p_array
            place = query_property("place")
            if(!place || (place == "")) {
            place = "default"


    def do_list(self, ) -> int:
            object ob
            if(!is_open(this_player(), 0)) {
            return 0


    def do_list_these(self, obs: MudObject) -> int:
            if(!is_open(this_player(), 0)) {
            return 0


    def do_browse(self, obs: MudObject) -> int:
            int i, value
            string place
            if (!is_open(this_player(), 0)) {
            return 0


    def do_value(self, obs: MudObject) -> int:
            int i
            int val
            int total
            string place
            int obnum
            if(!is_open(this_player(), 0)) {
            return 0


    def shop_list(self, arr: Any, detail: int) -> str:
            int i, j, value, num
            string s, mon, place, *shorts, *vals
            object *list
            mapping inv, costs
            mixed ind
            if(pointerp(arr)) {
            list = arr
            } else {
            list = all_inventory(self)


    def set_store_room(self, ob: Any) -> None:
            if(stringp(ob)) {
            original_storeroom = ob
            our_storeroom = find_object(ob)
            if(!our_storeroom) {
            our_storeroom = load_object(ob)


    def guards(self, tp: MudObject) -> None:
            object ob
            if(environment(tp) != self && environment(tp) != our_storeroom) {
            return


    def query_store_room(self, ) -> MudObject:
            return our_storeroom


    def add_other_shop(self, shop: Any) -> None:
            other_shops += ({shop})


    def query_shop_type(self, ) -> str:
            return shop_type


    def set_shop_type(self, ty: str) -> None:
            shop_type = ty


    def set_strict_shop(self, i: int) -> None:
            strict_shop = i


    def query_strict_shop(self, ) -> int:
            return strict_shop


    def create_rep(self, ) -> MudObject:
            object ob
            ob = clone_object("/obj/monster")
            ob.set_name("rep")
            ob.set_short("sales rep")
            ob.add_adjective("sales")
            ob->set_long("This is tall strong looking sales rep.  He "
            "stares at you with bright piercing eyes.\n")
            ob.add_alias("Sales rep alias")
            ob.set_class("fighter")
            ob.set_race("human")
            ob.adjust_bon_str(15)
            ob.set_level(60)
            ARMOURY.request_weapon("dagger", 100)->move(ob)
            ARMOURY.request_armour("cloth robe", 100)->move(ob)
            ob.init_equip()
            ob.add_property("rep type", shop_type)
            all_inventory(ob)->add_property("mine", 1)
            return ob


    def send_out_reps(self, ) -> None:
            int i
            object ob
            for(i = 0; i < sizeof(other_shops); i++) {
            ob = (object)self.create_rep()
            ob.add_property("goto destination", other_shops[i])
            ob.add_property("goto property", "shop")
            ob->move(self,
            "$N stride$s determinedly into the room.")
            ob->add_triggered_action("froggy", "goto_destination",
            file_name(self), "rep_made_it")


    def rep_made_it(self, bing: int) -> None:
            object *obs, rep
            int i, cost
            if(!bing) {
            previous_object()->init_command("'Oh no!  I am utterly lost!")
            previous_object()->init_command("sigh")
            asyncio.create_task(self."set_up_return", 5, previous_object())
            return


    def create_mercenary(self, rep: MudObject) -> MudObject:
            object ob
            string nam
            if(rep) {
            nam = implode(rep.query_adjectives(), " ")+" "+rep.query_name()


    def do_rep_buy(self, bing: Any) -> None:
            object rep, *obs
            int cost
            rep = bing[0]
            obs = bing[1]
            cost = bing[2]
            rep.adjust_money(cost, "brass")
            rep.query_current_room()->do_buy(obs, cost, rep)
            obs.move(present("Sales rep alias", rep->query_current_room()))
            asyncio.create_task(self."set_up_return", 5, rep)


    def set_up_return(self, rep: MudObject) -> None:
            rep.add_property("goto destination", file_name(self))
            rep->add_triggered_action("froggy", "goto_destination",
            self, "rep_came_back")


    def rep_came_back(self, ) -> None:
            int i
            object *obs, *obs2, rep
            obs = previous_object()->find_inv_match("all", previous_object())
            obs2 = [})
            for(i = 0; i < sizeof(obs); i++) {
            if(obs[i]->query_property("mine")) {
            continue


    def summon_guards(self, tp: MudObject) -> None:
            object ob
            int i
            if(environment(tp) != self) {
            return


    def set_strict_currency(self, new_strict: int) -> None:
            _strict_currency = new_strict


    def query_strict_currency(self, ) -> int:
            return _strict_currency


    def event_shoplift(self, command_ob: MudObject, thief: MudObject, victim: MudObject) -> None:
            if(stringp(shoplift_handler)) {
            if(shoplift_handler != "none") {
            shoplift_handler.handle_shoplift(thief, victim)


    def tidy_inventory(self, ) -> None:
            object storeob
            object *inventory
            int i, inv_to_leave
            int count
            inv_to_leave = max_inventory - (max_inventory / 4)
            if(objectp(our_storeroom)) {
            storeob = our_storeroom
            } else {
            our_storeroom.rabbit_away()
            storeob = find_object(our_storeroom)


    def dest_me(self, ) -> None:
            if(our_storeroom)
            our_storeroom.dest_me()
            ::dest_me()



class General_shop(MudObject):

    buy_mess = '[]'

    sell_mess = '[]'

    list_mess = '"$extra$"'

    value_mess = '"$ob$ is valued at $money$.\\n"'

    too_costly_mess = '"$ob$ is worth too much to be sold here.\\n"'

    not_worthy_mess = '"$ob$ is not worth enough to be sold here.\\n"'

    browse_mess = '"$ob$ costs $money$, it looks like:\\n$extra$"'

    other_shops = '[]'

    max_inventory = 'MAX_INVENTORY'

    min_amount = 50

    _strict_currency = 1
