# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/commercial/blackjack.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def setup(self, ) -> None:
            set_name( "table" )
            set_short( "blackjack table" )
            add_adjective( ["blackjack" } ))
            add_alias("blackjack")
            set_long( "The green felt of the table looks nice and soft, there is "
            "a single deck of cards sitting in the middle of the table.  "
            "The table looks like it will seat 4 people.\n")
            set_allowed_positions(({"sitting", "lying", "kneeling", "meditating"}))
            set_allowed_room_verbs((["sitting" : "sits" ]))
            set_weight(2000)
            set_value(240000)
            _timeout_length = 5 * 60
            _cost = 400
            _num_decks = 1
            add_player_id_type("green", 0)
            add_player_id_type("red", 0)
            add_player_id_type("blue", 0)
            add_player_id_type("maroon", 0)
            set_minimum_needed(1)
            add_help_file("blackjack")
            set_commercial_size(15)
            set_commercial_type("gambling")
            set_shop_use_types(["blackjack"])


    def query_card_status(self, ) -> str:
            string id_bing
            string ret
            string* not_playing
            class player_data data
            class playing_card card
            string* womble
            string place
            ret = ""
            not_playing = [})
            womble = query_player_ids()
            place = environment()->query_property("place")
            foreach (id_bing in womble) {
            if (is_person_playing(id_bing) ||
            is_game_started()) {
            ret += capitalize(id_bing) + " (" +
            query_player_cap_name(id_bing) + ")"
            data = query_player_data(id_bing)
            if (data) {
            if (data->starting_bet) {
            ret += "  " +
            MONEY_HAND.money_value_string(data->starting_bet, place)
            if (sizeof(data->hand)) {
            foreach (card in data->hand) {
            ret += "  " + query_card_string(card)


    def long(self, str: str, dark: int) -> str:
            if (dark) {
            return ::long() +
            "It is too dark to make out the pieces on the board.\n"


    def deal_cards(self, id: str) -> None:
            class player_data data
            string hands
            if (!sizeof(_dealer_hand)) {
            _dealer_hand = [query_next_card(), query_next_card()]


    def start_game(self, ) -> int:
            class player_data data
            string id
            randomise_player_numbers()
            if (!::start_game()) {
            return 0


    def query_hand_value(self, playing_card: Any) -> int:
            class playing_card bing
            int value
            int no_aces
            foreach (bing in cards) {
            if (bing->number == 1) {
            no_aces++
            } else if (bing->number >= 10) {
            value +=  10
            } else {
            value += bing->number


    def is_soft_result(self, playing_card: Any) -> int:
            class playing_card bing
            int value
            int no_aces
            foreach (bing in cards) {
            if (bing->number == 1) {
            no_aces++
            } else if (bing->number >= 10) {
            value +=  10
            } else {
            value += bing->number


    def finish_bet(self, id: str) -> None:
            class player_data data
            data = query_player_data(id)
            asyncio.create_task(self."deal_cards", 2, id)


    def complete_round(self, ) -> None:
            int value
            string stuff
            object ob
            int new_value
            class playing_card card
            class player_data data
            string id
            string place
            int paid
            string* winners
            string* losers
            remove_asyncio.create_task(self._timeout_call)
            _timeout_call = 0
            place = environment()->query_property("place")
            value = query_hand_value(_dealer_hand)
            while (value < 17 ||
            (value == 17 && _soft_seventeen && is_soft_result(_dealer_hand))) {
            _dealer_hand += [query_next_card()]
            value = query_hand_value(_dealer_hand)


    def force_finish(self, ) -> None:
            if (is_game_started()) {
            complete_round()


    def do_bet(self, str: str) -> int:
            string place
            string id
            int amount
            class player_data data
            if (!is_game_started()) {
            add_failed_mess("The game has not started.\n")
            return 0


    def do_hit(self, ) -> int:
            int value
            int not_done
            string id
            class player_data data
            class playing_card card
            if (!is_game_started()) {
            add_failed_mess("The game has not started.\n")
            return 0


    def do_stand(self, ) -> int:
            int value
            string id
            class player_data data
            int not_done
            if (!is_game_started()) {
            add_failed_mess("The game has not started.\n")
            return 0


    def do_start(self, ) -> int:
            if (!is_open_for("blackjack", this_player()->query_name())) {
            add_failed_mess("The blackjack table is not open.\n")
            return 0


    def do_finish(self, ) -> int:
            string person
            if (!is_game_started()) {
            add_failed_mess("The game has not started.\n")
            return 0


    def query_main_status(self, hint: int) -> str:
            string place
            string ret
            place = query_money_place()
            ret = "$I$0=Blackjack table:\n"
            "$I$6=   Table is " +
            (query_float() >= (_max_bet * 3 * 4) / 2?"open.\n":
            "closed! (Float needed: " +
            MONEY_HAND.money_value_string((_max_bet * 3 * 4) / 2, place) +
            "; current: " +
            MONEY_HAND.money_value_string(query_float(), place) + ")\n") +
            "$I$6=   Timeout length: " + (_timeout_length / 60) + " minutes.\n"
            if (hint) {
            ret += "$I$6=      set timeout <number> on <table>\n"


    def do_set_bet(self, str: str, max_bet: int) -> int:
            string place
            int value
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to change the paramaters of "
            "$D.\n")
            return 0


    def do_set_timeout(self, length: int) -> int:
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to change the paramaters of "
            "$D.\n")
            return 0


    def do_set_soft_seventeen(self, value: int) -> int:
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to change the paramaters of "
            "$D.\n")
            return 0


    def do_set_double_on_doubles(self, value: int) -> int:
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to change the paramaters of "
            "$D.\n")
            return 0


    def do_set_num_decks(self, num_decks: int) -> int:
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to change the paramaters of "
            "$D.\n")
            return 0


    def init(self, ) -> None:
            multiplayer_base::init()
            commercial::init()
            add_command("bet", "<string'amount'> on <direct:object>",
            (: do_bet($4[0]) :))
            add_command("hit", "on <direct:object>",
            (: do_hit() :))
            add_command("stay", "on <direct:object>",
            (: do_stand() :))
            add_command("start", "[new] game on <direct:object>",
            (: do_start() :))
            if (environment()->is_allowed(this_player()->query_name())) {
            add_command("set", "minimum bet <string'amount'> on <direct:object>",
            (: do_set_bet($4[0], 0) :))
            add_command("set", "maximum bet <string'amount'> on <direct:object>",
            (: do_set_bet($4[0], 1) :))
            add_command("set", "timeout <number'minutes'> on <direct:object>",
            (: do_set_timeout($4[0]) :))
            add_command("set", "num decks <number'num decks'> on <direct:object>",
            (: do_set_num_decks($4[0]) :))
            add_command("set", "hit on soft seventeen {on|off} on <direct:object>",
            (: do_set_soft_seventeen($4[0] == "on") :))


    def init_dynamic_arg(self, map: Any, player: MudObject) -> None:
            commercial::init_dynamic_arg(map, player)
            multiplayer_base::init_dynamic_arg(map, player)
            _cost = query_auto_load_value(map, BOARD_TAG, "cost")
            _dealer_hand = query_auto_load_value(map, BOARD_TAG, "dealer hand")
            _deck = query_auto_load_value(map, BOARD_TAG, "deck")
            _discard = query_auto_load_value(map, BOARD_TAG, "discard")
            _finished = query_auto_load_value(map, BOARD_TAG, "finished")
            _min_bet = query_auto_load_value(map, BOARD_TAG, "min bet")
            _max_bet = query_auto_load_value(map, BOARD_TAG, "max bet")
            _timeout_length = query_auto_load_value(map, BOARD_TAG, "timeout")
            _num_decks = query_auto_load_value(map, BOARD_TAG, "num decks")
            _soft_seventeen = query_auto_load_value(map, BOARD_TAG, "soft seventeen")
            _double_on_doubles = query_auto_load_value(map, BOARD_TAG, "double on doublet")
            if (!_num_decks) {
            _num_decks = 1



class Blackjack(MudObject):
