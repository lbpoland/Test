# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/peddler.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from .combat import combat_handler
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._none_left_mess = "I'm afraid I don't have any of those."
            self._out_of_item_mess = "We are right out of $item$."
            self._show_item_mess = "$item$ is priced at $cost$.  Let me show it to "
            self._missing_punter_mess = "Hey... Where'd the fellow go?  Anyway..."
            self._dont_sell_mess = "I'm afraid I don't have any $item$."
            self._all_out_mess = "I'm afraid I have no $item$ left."
            self._list_mess = "I have the following items for sale:"
            self._list_item_mess = "I have $num_left$ $display$ for $cost$."
            self._no_stock_mess = "I am afraid I have nothing for sale."
            self._too_poor_mess = "I'm afraid you can't afford to buy $item$."
            self._too_heavy_mess = "Well, here's $item$, but you can't carry it at "
            self._in_combat_mess = "Can't you see I'm a bit preoccupied right "
            self._busy_mess = "Sorry, I can only handle one purchase at a "


    def init(self, ) -> None:
            object cont = query_cont()
            ::init()
            if( cont ) {
            this_player()->add_command( "browse", self,
            "<indirect:object:" + file_name(cont) +
            "> {from|of} <direct:living:here>" )
            this_player()->add_command( "buy", self,
            "<indirect:object:" + file_name(cont) +
            "> from <direct:living:here>" )
            this_player()->add_command( "list", self,
            "goods {from|of} <direct:living:here>" )


    def check_cont(self, ) -> None:
            object cont
            ::check_cont()
            cont = query_cont()
            cont.set_name( "peddler_store" )


    def query_cost(self, thing: MudObject, buyer: MudObject) -> int:
            if( thing.query_property("cost here") ) {
            return (int)thing.query_property("cost here")


    def cost_string(self, thing: MudObject, place: str, buyer: MudObject) -> str:
            return (string)MONEY_HAND->money_value_string(
            query_cost( thing, buyer ), place )


    def do_list(self, ) -> int:
            int num_left
            string place
            object thing
            int first
            object cont
            string display
            string custom_string
            if( self.query_fighting() ) {
            queue_command( "sayto " + file_name(this_player()) + " " +
            _in_combat_mess, 2 )
            this_player()->add_succeeded_mess( self, "" )
            return 1


    def sell_thing(self, player: MudObject, thing: MudObject) -> None:
            int value
            string item_name, place
            object copy
            string custom_string
            if ( !player ) {
            busy = 0
            return


    def event_enter(self, ob: MudObject, mess: str, from: MudObject) -> None:
            if (ob.query_food_object()) { ob.set_decay_speed(0); }


    def event_exit(self, ob: MudObject, message: str, to: MudObject) -> None:
            if (ob.query_food_object()) { ob.set_decay_speed(8000); }


    def dest_me(self, ) -> None:
            if(query_cont())
            log_file("PEDDLER", "Cont: %s\n", file_name(query_cont()))
            clone_on_demand::dest_me()
            monster::dest_me()


    def set_none_left_mess(self, s: str) -> None:
            _none_left_mess = s


    def set_out_of_item_mess(self, s: str) -> None:
            _out_of_item_mess = s


    def set_show_item_mess(self, s: str) -> None:
            _show_item_mess = s


    def set_missing_punter_mess(self, s: str) -> None:
            _missing_punter_mess = s


    def set_dont_sell_mess(self, s: str) -> None:
            _dont_sell_mess = s


    def set_all_out_mess(self, s: str) -> None:
            _all_out_mess = s


    def set_list_mess(self, s: str) -> None:
            _list_mess = s


    def set_list_item_mess(self, s: str) -> None:
            _list_item_mess = s


    def set_no_stock_mess(self, s: str) -> None:
            _no_stock_mess = s


    def set_too_poor_mess(self, s: str) -> None:
            _too_poor_mess = s


    def set_too_heavy_mess(self, s: str) -> None:
            _too_heavy_mess = s


    def set_in_combat_mess(self, s: str) -> None:
            _in_combat_mess = s


    def set_busy_mess(self, s: str) -> None:
            _busy_mess = s



class Peddler(MudObject):

    _none_left_mess = '"I\'m afraid I don\'t have any of those."'

    _out_of_item_mess = '"We are right out of $item$."'

    _show_item_mess = '"$item$ is priced at $cost$.  Let me show it to "'

    _missing_punter_mess = '"Hey... Where\'d the fellow go?  Anyway..."'

    _dont_sell_mess = '"I\'m afraid I don\'t have any $item$."'

    _all_out_mess = '"I\'m afraid I have no $item$ left."'

    _list_mess = '"I have the following items for sale:"'

    _list_item_mess = '"I have $num_left$ $display$ for $cost$."'

    _no_stock_mess = '"I am afraid I have nothing for sale."'

    _too_poor_mess = '"I\'m afraid you can\'t afford to buy $item$."'

    _too_heavy_mess = '"Well, here\'s $item$, but you can\'t carry it at "'

    _in_combat_mess = '"Can\'t you see I\'m a bit preoccupied right "'

    _busy_mess = '"Sorry, I can only handle one purchase at a "'
