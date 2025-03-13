# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/furniture/poker.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._ante_house = 400
            self._ante_amount = 400
            self._min_bet = 400
            self._max_bet = 1200
            self._max_draw_rounds = 1
            self._player_stats = ([ ])


    def query_hand_type_string(self, hand_type: Any) -> str:
            string ret
            switch (bing->hand_type) {
            case HAND_TYPE_FULL_HOUSE :
            ret = "Full house"
            break
            case HAND_TYPE_THREE :
            ret = "Three of a kind"
            break
            case HAND_TYPE_FLUSH :
            ret = "Flush"
            break
            case HAND_TYPE_STRAIGHT :
            ret = "Straight"
            break
            case HAND_TYPE_STRAIGHT_FLUSH :
            ret = "Straight flush"
            break
            case HAND_TYPE_PAIR :
            ret = "Pair"
            break
            case HAND_TYPE_FOUR :
            ret = "Four of a kind"
            break
            case HAND_TYPE_TWO_PAIR :
            ret = "Two pairs"
            break
            case HAND_TYPE_HIGH_CARD :
            ret = "High card " + query_card_string(bing->high_card)
            break
            default :
            ret = "Nothing"
            break


    def query_card_status(self, id: str) -> str:
            string id_bing
            string ret
            string* not_playing
            class player_data data
            string* womble
            string place
            int left
            ret = ""
            not_playing = [})
            womble = query_player_ids()
            place = query_money_place()
            foreach (id_bing in womble) {
            if (is_person_playing(id_bing)) {
            ret += capitalize(id_bing) + " (" +
            query_player_cap_name(id_bing) + ")"
            data = query_player_data(id_bing)
            if (data) {
            if (data->state == POKER_STATE_FOLDED) {
            ret += " Folded!\n"
            } else {
            if (data->state == POKER_STATE_PAID_ANTE) {
            ret += " (paid ante) "


    def long(self, str: str, dark: int) -> str:
            if (dark) {
            return ::long() +
            "It is too dark to make out the pieces on the board.\n"


    def check_end_round(self, ) -> int:
            int bet
            string id
            class player_data data
            foreach (id in query_started_player_ids()) {
            data = query_player_data(id)
            if (data->state != POKER_STATE_FOLDED) {
            if (!data->bet) {
            return 0
            } else if (!bet && data->bet) {
            bet = data->bet
            } else if (bet != data->bet) {
            return 0


    def next_person_turn(self, ) -> None:
            class player_data data
            string start_id
            start_id = query_current_player()
            do {
            increment_current_player()
            data = query_player_data(query_current_player())
            } while (data->state == POKER_STATE_FOLDED &&
            query_current_player() != start_id)
            if (query_current_player() == start_id) {
            printf("Force end of game.\n")
            asyncio.create_task(self."complete_round", 2, 1)
            _poker_phase = POKER_STATE_END
            } else {
            asyncio.create_task(self."tell_current_player", 0, "%^BOLD%^Your turn!%^RESET%^\n")


    def deal_cards(self, ) -> None:
            string id
            class player_data data
            _deck = make_deck(1, 0)
            _deck = shuffle_deck(_deck)
            foreach (id in query_currently_playing_ids()) {
            data = query_player_data(id)
            data->hand = sort_cards(_deck[0..4], 3)
            data->bet = 0
            if (data->state != POKER_STATE_FOLDED) {
            if (!_max_draw_rounds) {
            data->state = POKER_STATE_FINAL_BET
            } else {
            data->state = POKER_STATE_BET


    def start_game(self, ) -> int:
            class player_data data
            string id
            randomise_player_numbers()
            if (!::start_game()) {
            return 0


    def check_for_finish_ante(self, ) -> None:
            string id
            class player_data data
            object ob
            foreach (id in query_currently_playing_ids()) {
            data = query_player_data(id)
            ob = query_player_object(id)
            if (ob && !interactive(ob)) {
            data->state = POKER_STATE_FOLDED


    def is_card_higher(self, playing_card: Any, playing_card: Any) -> int:
            if (card_new->number == card_old->number) {
            return 0


    def test_hand_type(self, ) -> None:
            class playing_card* other_tmp_hand
            class playing_card* tmp_hand
            other_tmp_hand = [new(class playing_card, suit: CARD_SUIT_HEARTS, number : 11),
            new(class playing_card, suit: CARD_SUIT_HEARTS, number : 11),
            new(class playing_card, suit: CARD_SUIT_HEARTS, number : 12),
            new(class playing_card, suit: CARD_SUIT_HEARTS, number : 13),
            new(class playing_card, suit: CARD_SUIT_HEARTS, number : 13)]
            tmp_hand = [new(class playing_card, suit: CARD_SUIT_HEARTS, number : 2),
            new(class playing_card, suit: CARD_SUIT_HEARTS, number : 3),
            new(class playing_card, suit: CARD_SUIT_HEARTS, number : 4),
            new(class playing_card, suit: CARD_SUIT_HEARTS, number : 1),
            new(class playing_card, suit: CARD_SUIT_HEARTS, number : 5)]
            write(query_hand_type_string(query_hand_type(tmp_hand)) + " --\n" +
            query_hand_type_string(query_hand_type(other_tmp_hand)))
            printf("%O\n", sizeof(query_hand_type(tmp_hand)->kickers))
            printf("%O\n", sizeof(query_hand_type(other_tmp_hand)->kickers))
            write("Result: " + is_greator_hand(query_hand_type(tmp_hand),
            query_hand_type(other_tmp_hand)) + "\n")


    def complete_round(self, force_end: int) -> None:
            string stuff
            object ob
            class player_data data
            string id
            string place
            string* winner
            class hand_type winning_hand_type
            class playing_card* winning_hand
            int paid
            int discard
            int result
            int num
            if (_finished) {
            return 0


    def finish_discard(self, ) -> None:
            string id
            class player_data data
            foreach (id in query_started_player_ids()) {
            data = query_player_data(id)
            if (data->state != POKER_STATE_AFTER_DISCARD &&
            data->state != POKER_STATE_FOLDED) {
            return 0


    def do_ante(self, ) -> int:
            string place
            string id
            int amount
            class player_data data
            if (!is_game_started()) {
            add_failed_mess("The game has not started.\n")
            return 0


    def do_discard(self, throw_away: str) -> int:
            int i
            string id
            class player_data data
            string* bits
            int* new_bits
            throw_away = lower_case(throw_away)
            if (!is_game_started()) {
            add_failed_mess("The game has not started.\n")
            return 0


    def do_check(self, ) -> int:
            if (!is_game_started()) {
            add_failed_mess("The game has not started.\n")
            return 0


    def do_call(self, ) -> int:
            class player_data data
            int amt
            string place
            if (!is_game_started()) {
            add_failed_mess("The game has not started.\n")
            return 0


    def do_raise(self, amount: str) -> int:
            class player_data data
            string place
            int amt
            int raise_amt
            if (!is_game_started()) {
            add_failed_mess("The game has not started.\n")
            return 0


    def do_bet(self, amount: str) -> int:
            class player_data data
            string place
            int amt
            int raise_amt
            if (!is_game_started()) {
            add_failed_mess("The game has not started.\n")
            return 0


    def do_fold(self, ) -> int:
            class player_data data
            string id
            int not_folded
            if (!is_game_started()) {
            add_failed_mess("The game has not started.\n")
            return 0


    def do_start(self, ) -> int:
            int old_pot
            if (!is_open_for("poker", this_player()->query_name())) {
            add_failed_mess("The poker table is not open.\n")
            return 0


    def do_finish(self, ) -> int:
            string person
            if (!is_game_started()) {
            add_failed_mess("The game has not started.\n")
            return 0


    def query_main_status(self, hint: int) -> str:
            string place
            string ret
            string name
            int amt
            place = query_money_place()
            ret = "$I$0=Poker table:\n"
            "$I$6=   Maximum bet: " +
            MONEY_HAND.money_value_string(_max_bet, place) +
            "\n$I$6=   Minimum bet: " +
            MONEY_HAND.money_value_string(_min_bet, place) +
            "\n$I$6=   Ante       : " +
            MONEY_HAND.money_value_string(_ante_amount, place) +
            "\n$I$6=   House Ante : " +
            MONEY_HAND.money_value_string(_ante_house, place) +
            "\n$I$6=   Draw Rounds: " + _max_draw_rounds +
            "\n$I$6=   Cut        : " + _house_cut + "%"
            "\n$I$6=   Revenue    : " +
            MONEY_HAND.money_value_string(query_revenue(), place) +
            "\n$I$0="
            foreach (name, amt in _player_stats) {
            ret += sprintf(" %-13s: %s\n" , name,
            MONEY_HAND.money_value_string(amt, place))


    def do_set_ante(self, str: str, ante_game: int) -> int:
            string place
            int value
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to change the paramaters of "
            "$D.\n")
            return 0


    def do_set_bet(self, str: str, max_bet: int) -> int:
            string place
            int value
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to change the paramaters of "
            "$D.\n")
            return 0


    def do_set_cut(self, percent: int) -> int:
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to change the paramaters of "
            "$D.\n")
            return 0


    def do_set_draw(self, draw: int) -> int:
            if (!is_allowed(this_player()->query_name())) {
            add_failed_mess("You are not allowed to change the paramaters of "
            "$D.\n")
            return 0


    def do_rules(self, ) -> int:
            string ret
            string place
            place = query_money_place()
            ret = "The rules for this table are:\n"
            ret += "$I$6=   Maximum amount that can be raised " +
            MONEY_HAND.money_value_string(_max_bet, place) +
            "\n$I$6=   Minimum amount that can be raised " +
            MONEY_HAND.money_value_string(_min_bet, place) +
            "\n$I$6=   Total ante " +
            MONEY_HAND.money_value_string(_ante_amount + _ante_house, place) +
            "\n$I$6=   Cut of the pool : " + _house_cut +
            "\n$I$6=   Draw Rounds     : " + _max_draw_rounds +
            "\n$I$6=   House Ante      : " +
            MONEY_HAND.money_value_string(_ante_house, place)
            write("$P$Rules$P$" + ret)


    def do_reset(self, ) -> int:
            if (::do_reset()) {
            _player_stats = ([ ])
            add_succeeded_mess("$N clear$s the player stats.\n")
            return 1


    def init(self, ) -> None:
            multiplayer_base::init()
            commercial::init()
            add_command("discard", "<string'card'> on <direct:object>",
            (: do_discard($4[0]) :))
            add_command("ante", "on <direct:object>",
            (: do_ante() :))
            add_command("check", "on <direct:object>",
            (: do_check() :))
            add_command("call", "on <direct:object>",
            (: do_call() :))
            add_command("bet", "<string'total bet'> on <direct:object>",
            (: do_bet($4[0]) :))
            add_command("raise", "<string'raise'> on <direct:object>",
            (: do_raise($4[0]) :))
            add_command("fold", "on <direct:object>",
            (: do_fold() :))
            add_command("finish", "game on <direct:object>",
            (: do_finish() :))
            add_command("start", "game on <direct:object>",
            (: do_start() :))
            add_command("rules", "<direct:object>",
            (: do_rules() :))
            add_command("rules", "{for|on|of} <direct:object>",
            (: do_rules() :))
            if (environment()->is_allowed(this_player()->query_name())) {
            add_command("set", "draw <number'rounds'> on <direct:object>",
            (: do_set_draw($4[0]) :))
            add_command("set", "cut <number'percentage'> on <direct:object>",
            (: do_set_cut($4[0]) :))
            add_command("set", "ante house <string'amount|none'> on <direct:object>",
            (: do_set_ante($4[0], 0) :))
            add_command("set", "ante game <string'amount'> on <direct:object>",
            (: do_set_ante($4[0], 1) :))
            add_command("set", "minimum bet <string'amount'> on <direct:object>",
            (: do_set_bet($4[0], 0) :))
            add_command("set", "maximum bet <string'amount'> on <direct:object>",
            (: do_set_bet($4[0], 1) :))


    def resign_person(self, id: str) -> None:
            class player_data data
            int not_folded
            data = query_player_data(id)
            if (data && data->state != POKER_STATE_FOLDED) {
            tell_all_players(query_player_cap_name(id) +
            " resigns and folds.\n")
            data->state = POKER_STATE_FOLDED
            foreach (id in query_started_player_ids()) {
            data = query_player_data(id)
            if (data->state != POKER_STATE_FOLDED) {
            not_folded++


    def event_exit(self, ob: MudObject, mess: str, to: MudObject) -> None:
            string id
            if (userp(ob) && to != environment()) {
            id = find_player_id_of_person(ob)
            if (id) {
            resign_person(id)


    def multiplayer_someone_resigns(self, id: str, name: str) -> None:
            resign_person(id)


    def init_dynamic_arg(self, map: Any, player: MudObject) -> None:
            commercial::init_dynamic_arg(map, player)
            multiplayer_base::init_dynamic_arg(map, player)
            _return = query_auto_load_value(map, BOARD_TAG, "return")
            _ante_amount = query_auto_load_value(map, BOARD_TAG, "ante amount")
            _ante_house = query_auto_load_value(map, BOARD_TAG, "ante house")
            _house_cut = query_auto_load_value(map, BOARD_TAG, "house cut")
            _deck = query_auto_load_value(map, BOARD_TAG, "deck")
            _current_bet = query_auto_load_value(map, BOARD_TAG, "current bet")
            _pot = query_auto_load_value(map, BOARD_TAG, "pot")
            _min_bet = query_auto_load_value(map, BOARD_TAG, "min bet")
            _max_bet = query_auto_load_value(map, BOARD_TAG, "max bet")
            _poker_phase = query_auto_load_value(map, BOARD_TAG, "poker phase")
            _draw_round = query_auto_load_value(map, BOARD_TAG, "draw round")
            _max_draw_rounds = query_auto_load_value(map, BOARD_TAG, "max draw rounds")
            _discard = query_auto_load_value(map, BOARD_TAG, "discard")
            _player_stats = query_auto_load_value(map, BOARD_TAG, "player stats")
            if (!_player_stats) {
            _player_stats = ([ ])



class Poker(MudObject):

    _ante_house = 400

    _ante_amount = 400

    _min_bet = 400

    _max_bet = 1200

    _max_draw_rounds = 1

    _player_stats = '([ ])'
