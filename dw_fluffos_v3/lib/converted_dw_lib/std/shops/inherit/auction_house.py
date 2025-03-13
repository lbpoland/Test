# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/inherit/auction_house.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._auctions = []
            self._finished_auctions = []
            self._cut = 10
            self._max_auctions = 20
            self._auction_obs = []
            self._royalties = ([ ])
            self._auction_times = ([
            self._retrieval_time = DEFAULT_RETRIEVAL_TIME
            self._max_retries = 5
            self._minimum_bid_increase = 10
            self._allow_add = 1


    def load_me(self, ) -> None:
            unguarded( (: restore_object(_save_file, 1) :))
            _auction_obs = allocate(sizeof(_auctions))
            if (!_royalties) {
            _royalties = ([ ])


    def save_me(self, ) -> None:
            unguarded( (: save_object(_save_file) :))


    def set_save_file(self, fname: str) -> None:
            _save_file = fname
            load_me()


    def query_save_file(self, ) -> str:
            return _save_file


    def set_check_can_bid(self, f: Any) -> None:
            _can_bid = f


    def set_allowed_add(self, flag: int) -> None:
            _allow_add = flag


    def set_auction_time(self, index: str, i: int) -> None:
            if (!i) {
            map_delete(_auction_times, index)
            } else {
            if (!_auction_times[index]) {
            _bid_type_names = 0


    def set_min_bid_increase(self, i: int) -> None:
            int add_item_to_auction(object* obs, string name, int reserve,
            string seller, int length,
            string end_function, mixed extra) {
            class auction new_auct
            if (sizeof(_auctions) + sizeof(_finished_auctions) >= _max_auctions) {
            return 0


    def query_auction_objects(self, auction: Any) -> List[MudObject]:
            int i
            for (i = 0; i < sizeof(_auctions); i++) {
            if (_auctions[i] == auct) {
            if (!_auction_obs[i]) {
            _auction_obs[i] = AUTO_LOAD_OB.load_auto_load_to_array(auct->save_stuff)


    def reset_bid(self, id: str, bid: int, person: str) -> int:
            class auction auct
            if(!(this_player()->query_lord()))
            return 0
            auct = query_auction_item(id)
            if(!auct)
            return 0
            auct->bid = bid
            auct->current_bidder = person
            return 1


    def remove_finished_auction_item(self, auction: Any) -> None:
            int i
            for (i = 0; i < sizeof(_finished_auctions); i++) {
            if (_finished_auctions[i] == auction) {
            _finished_auctions = _finished_auctions[0..i-1] + _finished_auctions[i+1..]


    def remove_auction_item(self, auction: Any) -> None:
            int i
            for (i = 0; i < sizeof(_auctions); i++) {
            if (_auctions[i] == auction) {
            if (i < sizeof(_auction_obs) && _auction_obs[i]) {
            ((_auction_obs[i]) - [0])->move("/room/rubbish")


    def finish_auction(self, auction: Any) -> None:
            string place
            if (auction->end_function) {
            call_other(self, auction->end_function,
            AUCTION_FINISH_PHASE, auction, auction->extra,
            auction->current_bidder, auction->bid)


    def force_finish_auction(self, id: str) -> None:
            string place
            class auction auction
            auction = query_auction_item(id)
            if (auction->end_function) {
            call_other(self, auction->end_function,
            AUCTION_FINISH_PHASE, auction, auction->extra,
            auction->current_bidder, auction->bid)


    def retry_auction(self, auction: Any) -> None:
            string place
            if (auction->end_function) {
            call_other(self, auction->end_function,
            AUCTION_RETRY_PHASE, auction, auction->extra)


    def query_time_end_string(self, left: int) -> str:
            string str
            string extra
            if (left >= AM_SECONDS_PER_DAY) {
            str = (left / AM_SECONDS_PER_DAY) + " day"
            if ((left / AM_SECONDS_PER_DAY) > 1) {
            str += "s"


    def query_auction_end_string(self, auction: Any) -> str:
            return query_time_end_string(auction->time_started +
            auction->auction_length - time())


    def query_last_auction_finish_time(self, ) -> int:
            int tim
            class auction auction
            foreach (auction in _auctions) {
            if (tim < auction->time_started + auction->auction_length) {
            tim = auction->time_started + auction->auction_length


    def next_auction_finish(self, ) -> None:
            class auction auct
            int next
            int tmp
            next = 0
            foreach (auct in _auctions) {
            tmp = auct->time_started + auct->auction_length - time()
            if (tmp <= 0) {
            finish_auction(auct)
            } else if (tmp < next || !next) {
            next = tmp


    def do_list(self, ) -> int:
            string str
            class auction bing
            int pos
            string place
            if (!is_open(this_player(), 0)) {
            add_failed_mess(self.the_short() + " is not open.\n")
            return 0


    def do_browse(self, id: str) -> int:
            class auction bing
            string place
            string str
            object* obs
            object ob
            if (!is_open(this_player(), 0)) {
            add_failed_mess(self.the_short() + " is not open.\n")
            return 0


    def do_bid(self, id: str, bid: str) -> int:
            class auction auct
            string place
            int value
            int inc
            if (!is_open(this_player(), 0)) {
            add_failed_mess(self.the_short() + " is not open.\n")
            return 0


    def do_withdraw(self, id: str) -> int:
            class auction auct
            string place
            int value
            object* obs
            object ob
            if (!is_open(this_player(), 0)) {
            add_failed_mess(self.the_short() + " is not open.\n")
            return 0


    def do_claim(self, ) -> int:
            class auction auction
            int num
            string place
            object* obs
            object ob
            int i
            int value
            if (!is_open(this_player(), 0)) {
            add_failed_mess(self.the_short() + " is not open.\n")
            return 0


    def do_add(self, name: str, obs: Any, res_str: str, length: str) -> int:
            int reserve
            string ret
            string place
            int len
            if (!is_open(this_player(), 0)) {
            add_failed_mess(self.the_short() + " is not open.\n")
            return 0


    def confirm_auction(self, check: str, name: str, obs: Any, reserve: int, len: int) -> None:
            string place
            string ret
            place = query_property("place")
            check = lower_case(check)
            if (!strlen(check) || check[0] != 'y') {
            if (!broadcast_shop_event(AUCTION_EVENT_ADD_ABORT,
            this_player(), name, obs, reserve, len)) {
            write("Ok, Aborting.\n")


    def do_info(self, ) -> int:
            string ret
            string name
            int len
            if (!is_open(this_player(), 0)) {
            add_failed_mess(self.the_short() + " is not open.\n")
            return 0


    def init(self, ) -> None:
            add_command("list", "", (: do_list() :))
            add_command("browse", "<string'auction id'>", (: do_browse($4[0]) :))
            add_command("bid", "<string'auction id'> for <string'money'>",
            (: do_bid($4[0], $4[1]) :))
            add_command("bid", "<string'money'> on <string'auction id'>",
            (: do_bid($4[1], $4[0]) :))
            add_command("claim", "", (: do_claim() :))
            add_command("withdraw", "<string'auction id'> [from auction]",
            (: do_withdraw($4[0]) :))
            if (_allow_add) {
            if (!_bid_type_names) {
            _bid_type_names = implode(keys(_auction_times), "|")



class Auction_house(MudObject):

    _auctions = '[]'

    _finished_auctions = '[]'

    _cut = 10

    _max_auctions = 20

    _auction_obs = '[]'

    _royalties = '([ ])'

    _auction_times = '(['

    _retrieval_time = 'DEFAULT_RETRIEVAL_TIME'

    _max_retries = 5

    _minimum_bid_increase = 10

    _allow_add = 1
