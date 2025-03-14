#include <room/auction.h>
#include <player.h>
#include <money.h>
#include <move_failures.h>
#include <mail.h>
#include <player_handler.h>
#include <am_time.h>
inherit "/std/shops/inherit/shop_event";
inherit "/std/shops/inherit/open_shop";
#define DEFAULT_QUICK_AUCTION_LENGTH (15 * 60)
#define DEFAULT_SHORT_AUCTION_LENGTH (60 * 60)
#define DEFAULT_MEDIUM_AUCTION_LENGTH (AM_SECONDS_PER_DAY)
#define DEFAULT_LONG_AUCTION_LENGTH (AM_SECONDS_PER_DAY * 3)
#define DEFAULT_VERY_LONG_AUCTION_LENGTH (AM_SECONDS_PER_DAY * 14)
#define DEFAULT_RETRIEVAL_TIME (AM_SECONDS_PER_DAY * 7)
#define DEFAULT_EXTENSION_TIME (20 * 60)
class auction {
   mixed save_stuff;
   int time_started;
   int auction_length;
   string name;
   string seller;
   string current_bidder;
   int bid;
   int reserve;
   int retries;
   string end_function;
   mixed extra;
}
private nosave mixed* _auction_obs;
private nosave int _callout_id;
private nosave string _save_file;
private nosave int _max_auctions;
private nosave mapping _auction_times;
private nosave int _retrieval_time;
private nosave int _max_retries;
private nosave int _cut;
private nosave int _minimum_bid_increase;
private nosave function _can_bid;
private nosave int _allow_add;
private nosave string _bid_type_names;
private class auction* _auctions;
private class auction* _finished_auctions;
private mapping _royalties;
void next_auction_finish();
mixed query_property(string name);
class auction query_auction_item(string id);
void retry_auction(class auction auction);
void create() {
   _auctions = ({ });
   _finished_auctions = ({ });
   _cut = 10;
   _max_auctions = 20;
   _auction_obs = ({ });
   _royalties = ([ ]);
   _auction_times = ([
                      "quick" : DEFAULT_QUICK_AUCTION_LENGTH,
                      "short" : DEFAULT_SHORT_AUCTION_LENGTH,
                      "medium" : DEFAULT_MEDIUM_AUCTION_LENGTH,
                      "long" : DEFAULT_LONG_AUCTION_LENGTH,
                      "very long" : DEFAULT_VERY_LONG_AUCTION_LENGTH
                    ]);
   _retrieval_time = DEFAULT_RETRIEVAL_TIME;
   _max_retries = 5;
   _minimum_bid_increase = 10;
   _allow_add = 1;
   shop_event::create();
}
class auction *query_auctions() { return copy(_auctions); }
class auction *query_finished_auctions() { return copy(_finished_auctions); }
void load_me() {
   unguarded( (: restore_object(_save_file, 1) :));
   _auction_obs = allocate(sizeof(_auctions));
   if (!_royalties) {
      _royalties = ([ ]);
   }
   next_auction_finish();
}
void save_me() {
   unguarded( (: save_object(_save_file) :));
}
void set_save_file(string fname) {
   _save_file = fname;
   load_me();
}
string query_save_file() {
   return _save_file;
}
void set_check_can_bid(function f) {
   _can_bid = f;
}
void set_allowed_add(int flag) {
   _allow_add = flag;
}
void set_max_auctions(int i) { _max_auctions = i; }
void set_auction_time(string index, int i) {
   if (!i) {
      map_delete(_auction_times, index);
   } else {
      if (!_auction_times[index]) {
         _bid_type_names = 0;
      }
      _auction_times[index] = i;
   }
}
mapping query_auction_times() { return _auction_times; }
void set_retrieval_time(int i) { _retrieval_time = i; }
void set_max_retries(int i) { _max_retries = i; }
void set_min_bid_increase(int i) { _minimum_bid_increase = i; }
int add_item_to_auction(object* obs, string name, int reserve,
                        string seller, int length,
                         string end_function, mixed extra) {
   class auction new_auct;
   if (sizeof(_auctions) + sizeof(_finished_auctions) >= _max_auctions) {
      return 0;
   }
   if (!reserve) {
      reserve = 40;
   }
   new_auct = new(class auction);
   new_auct->save_stuff = AUTO_LOAD_OB->create_auto_load(obs);
   new_auct->name = name;
   new_auct->reserve = reserve;
   new_auct->end_function = end_function;
   new_auct->time_started = time();
   if (!length) {
      new_auct->auction_length = _auction_times["very long"];
   } else {
      new_auct->auction_length = length;
   }
   new_auct->seller = seller;
   new_auct->extra = extra;
   _auctions += ({ new_auct });
   _auction_obs += ({ obs });
   save_me();
   next_auction_finish();
   _auction_obs -= ({ obs });
   _auction_obs += ({ 0 });
   return 1;
}
object* query_auction_objects(class auction auct) {
   int i;
   for (i = 0; i < sizeof(_auctions); i++) {
      if (_auctions[i] == auct) {
         if (!_auction_obs[i]) {
            _auction_obs[i] = AUTO_LOAD_OB->load_auto_load_to_array(auct->save_stuff);
         }
         return _auction_obs[i];
      }
   }
   return ({ });
}
void bid_on_item(class auction auct,
                 int bid, string person) {
    if (bid > auct->bid && bid >= auct->reserve) {
        auct->bid = bid;
        auct->current_bidder = person;
        if (auct->auction_length + auct->time_started - time() <
            DEFAULT_EXTENSION_TIME) {
            auct->auction_length = time() - auct->time_started +
                DEFAULT_EXTENSION_TIME;
        }
    }
}
int reset_bid(string id, int bid, string person) {
  class auction auct;
  if(!(this_player()->query_lord()))
    return 0;
  auct = query_auction_item(id);
  if(!auct)
    return 0;
  auct->bid = bid;
  auct->current_bidder = person;
  return 1;
}
void remove_finished_auction_item(class auction auction) {
   int i;
   for (i = 0; i < sizeof(_finished_auctions); i++) {
      if (_finished_auctions[i] == auction) {
         _finished_auctions = _finished_auctions[0..i-1] + _finished_auctions[i+1..];
      }
   }
}
void remove_auction_item(class auction auction) {
   int i;
   for (i = 0; i < sizeof(_auctions); i++) {
      if (_auctions[i] == auction) {
         if (i < sizeof(_auction_obs) && _auction_obs[i]) {
            ((_auction_obs[i]) - ({ 0 }))->move("/room/rubbish");
         }
         _auctions = _auctions[0..i-1] + _auctions[i+1..];
         _auction_obs = _auction_obs[0..i-1] + _auction_obs[i+1..];
      }
   }
}
void finish_auction(class auction auction) {
   string place;
   if (auction->end_function) {
      call_other(this_object(), auction->end_function,
                 AUCTION_FINISH_PHASE, auction, auction->extra,
                 auction->current_bidder, auction->bid);
   }
   place = query_property("place");
   remove_auction_item(auction);
   if (!auction->current_bidder) {
      auction->current_bidder = auction->seller;
      auction->bid = 4000;
   }
   _finished_auctions += ({ auction });
   save_me();
   if (auction->current_bidder &&
       PLAYER_HANDLER->test_user(lower_case(auction->current_bidder))) {
      AUTO_MAILER->auto_mail(lower_case(auction->current_bidder),
                              this_object()->query_short(),
                              "Results of auction for " + auction->name,
                              "",
                              "Your auction for " + auction->name +
                              " has completed.\nPlease pay the " +
                              MONEY_HAND->money_value_string(auction->bid, place) +
                              " as soon as you can.\n", 0, auction->current_bidder);
   } else {
      retry_auction(auction);
   }
   return ;
}
void force_finish_auction(string id) {
   string place;
   class auction auction;
   auction = query_auction_item(id);
   if (auction->end_function) {
      call_other(this_object(), auction->end_function,
                 AUCTION_FINISH_PHASE, auction, auction->extra,
                 auction->current_bidder, auction->bid);
   }
   place = query_property("place");
   remove_auction_item(auction);
   if (!auction->current_bidder) {
      auction->current_bidder = auction->seller;
      auction->bid = 4000;
   }
   _finished_auctions += ({ auction });
   save_me();
   if (auction->current_bidder &&
       PLAYER_HANDLER->test_user(lower_case(auction->current_bidder))) {
      AUTO_MAILER->auto_mail(lower_case(auction->current_bidder),
                              this_object()->query_short(),
                              "Results of auction for " + auction->name,
                              "",
                              "Your auction for " + auction->name +
                              " has completed.\nPlease pay the " +
                              MONEY_HAND->money_value_string(auction->bid, place) +
                              " as soon as you can.\n");
   }
   return ;
}
void retry_auction(class auction auction) {
   string place;
   if (auction->end_function) {
      call_other(this_object(), auction->end_function,
                 AUCTION_RETRY_PHASE, auction, auction->extra);
   }
   place = query_property("place");
   remove_finished_auction_item(auction);
   auction->bid = 0;
   auction->current_bidder = 0;
   auction->retries++;
   auction->time_started = time();
   if (auction->retries > _max_retries) {
   } else {
      _auctions += ({ auction });
      _auction_obs += ({ 0 });
   }
   save_me();
   if (auction->seller &&
       PLAYER_HANDLER->test_user(lower_case(auction->seller))) {
      AUTO_MAILER->auto_mail(lower_case(auction->seller),
                              this_object()->query_short(),
                              "Default on auction of " + auction->name,
                              "",
                              "Your auction for " + auction->name +
                              " has completed and the payee defaulted.\n"
                              "The item has been put up for reauctioning.\n");
   }
   return ;
}
class auction query_auction_item(string id) {
   id = lower_case(id);
   if (strlen(id) == 1 &&
       id[0] >= 'a' && id[0] < 'a' + sizeof(_auctions)) {
      return _auctions[id[0] - 'a'];
   }
   return 0;
}
string query_time_end_string(int left) {
   string str;
   string extra;
   if (left >= AM_SECONDS_PER_DAY) {
      str = (left / AM_SECONDS_PER_DAY) + " day";
      if ((left / AM_SECONDS_PER_DAY) > 1) {
         str += "s";
      }
      left = left % (AM_SECONDS_PER_DAY);
      if (left >= (AM_SECONDS_PER_MINUTE * AM_MINUTES_PER_HOUR)) {
         if ((left / (AM_SECONDS_PER_MINUTE * AM_MINUTES_PER_HOUR)) > 1) {
             extra = "s";
          } else {
             extra = "";
         }
         return str + " and " +
           (left / (AM_SECONDS_PER_MINUTE * AM_MINUTES_PER_HOUR)) + " hour" +
           extra;
      }
      return str;
   } else if (left >= AM_SECONDS_PER_MINUTE * AM_MINUTES_PER_HOUR) {
      if ((left / (AM_SECONDS_PER_MINUTE * AM_MINUTES_PER_HOUR)) > 1) {
          extra = "s";
       } else {
          extra = "";
      }
      str = (left / (AM_SECONDS_PER_MINUTE * AM_MINUTES_PER_HOUR)) + " hour" +
            extra;
      left %= AM_SECONDS_PER_MINUTE * AM_MINUTES_PER_HOUR;
      if ((left / (AM_SECONDS_PER_MINUTE)) > 1) {
          extra = "s";
       } else {
          extra = "";
      }
      if (left > AM_SECONDS_PER_MINUTE) {
         return str + " and " + (left / AM_SECONDS_PER_MINUTE) + " minute" +
                extra;
      }
      return str;
   } else if (left <= 0) {
      return "already finished";
   }
    if( !(left/60) ) {
        return "less than a minute";
    }
    else {
        str = "";
        str += ( left / 60) + " minute";
        if (left / 60 > 1) {
            str += "s";
        }
        return str;
    }
}
string query_auction_end_string(class auction auction) {
   return query_time_end_string(auction->time_started +
                                auction->auction_length - time());
}
int query_last_auction_finish_time() {
   int tim;
   class auction auction;
   foreach (auction in _auctions) {
      if (tim < auction->time_started + auction->auction_length) {
         tim = auction->time_started + auction->auction_length;
      }
   }
   return tim;
}
void next_auction_finish() {
   class auction auct;
   int next;
   int tmp;
   next = 0;
   foreach (auct in _auctions) {
      tmp = auct->time_started + auct->auction_length - time();
      if (tmp <= 0) {
         finish_auction(auct);
      } else if (tmp < next || !next) {
         next = tmp;
      }
   }
   foreach (auct in _finished_auctions) {
      tmp = auct->time_started + auct->auction_length + _retrieval_time -
        time();
      if (tmp <= 0) {
         retry_auction(auct);
         tmp = auct->time_started + auct->auction_length - time();
         if (tmp < next || !next) {
            next = tmp;
         }
      } else if (tmp < next || !next) {
         next = tmp;
      }
   }
   if (_callout_id) {
      remove_call_out(_callout_id);
      _callout_id = 0;
   }
   if (next) {
      _callout_id = call_out("next_auction_finish", next);
   }
}
int do_list() {
   string str;
   class auction bing;
   int pos;
   string place;
   if (!is_open(this_player(), 0)) {
      add_failed_mess(this_object()->the_short() + " is not open.\n");
      return 0;
   }
   if (!sizeof(_auctions)) {
      add_failed_mess("Nothing currently on auction.\n");
      return 0;
   }
   place = query_property("place");
   str = "Items currently up for auction:\n";
   foreach (bing in _auctions) {
      str += sprintf("%c) %s", pos + 'A', bing->name);
      if (bing->current_bidder) {
         str += "; " +
                MONEY_HAND->money_value_string(bing->bid, place) +
                " by " + bing->current_bidder + "; finishes in " +
                query_auction_end_string(bing) + ".\n";
      } else {
         str += "; no current bid; finishes in " +
                query_auction_end_string(bing) + ".\n";
      }
      pos++;
   }
   if (!broadcast_shop_event(AUCTION_EVENT_LIST,
                             this_player(), str)) {
      write("$P$Auctions$P$" + str);
   }
   return 1;
}
int do_browse(string id) {
   class auction bing;
   string place;
   string str;
   object* obs;
   object ob;
   if (!is_open(this_player(), 0)) {
      add_failed_mess(this_object()->the_short() + " is not open.\n");
      return 0;
   }
   bing = query_auction_item(id);
   if (!bing) {
      add_failed_mess("There is no auction item " + id + ".\n");
      return 0;
   }
   place = query_property("place");
   str = "Auction called " + bing->name + " started at " +
        amtime(bing->time_started) + " finishes at " +
        amtime(bing->time_started + bing->auction_length) + " (in " +
        query_auction_end_string(bing) + ".\n";
   str += "Reserve price " +
          MONEY_HAND->money_value_string(bing->reserve, place);
   if (bing->bid) {
      str += "; current bid " +
             MONEY_HAND->money_value_string(bing->bid, place) +
             " by " + bing->current_bidder + ".\n";
   } else {
      str += "; no current bid.\n";
   }
   obs = query_auction_objects(bing);
   foreach (ob in obs) {
      str += "\n$I$0=$C$" + ob->the_short() + ":\n$I$3=   " +
             ob->long();
      if (ob->query_readable_message(this_player())) {
         str += "$I$0=Read message:\n$I$3=   " + ob->query_readable_message(this_player()) + "\n";
      }
   }
   if (!broadcast_shop_event(AUCTION_EVENT_BROWSE,
                             this_player(), bing, obs, str)) {
      write("$P$Browse Auction$P$" + str);
   }
   return 1;
}
int do_bid(string id, string bid) {
   class auction auct;
   string place;
   int value;
   int inc;
   if (!is_open(this_player(), 0)) {
      add_failed_mess(this_object()->the_short() + " is not open.\n");
      return 0;
   }
   auct = query_auction_item(id);
   if (!auct) {
      if (!broadcast_shop_event(AUCTION_EVENT_BAD_ITEM,
                                 this_player(), id)) {
         add_failed_mess("There is no auction item " + id + ".\n");
      }
      return 0;
   }
   place = query_property("place");
   value = MONEY_HAND->value_from_string(bid, place);
   if (_can_bid) {
      if (!evaluate(_can_bid, this_player(), auct, value)) {
         return 0;
      }
   }
   inc = auct->bid + ((auct->bid * _minimum_bid_increase) / 100);
   if (value < inc) {
      if (!broadcast_shop_event(AUCTION_EVENT_BID_TOO_SMALL,
                                 this_player(), auct, value, inc)) {
         add_failed_mess("You must bid " + _minimum_bid_increase + "% more than "
                         "the current bid, current bid is " +
                         MONEY_HAND->money_value_string(auct->bid, place) +
                         " so " + _minimum_bid_increase + "% more is " +
                         MONEY_HAND->money_value_string(inc, place) +
                         ".\n");
      }
      return 0;
   }
   if (value < auct->reserve) {
      if (!broadcast_shop_event(AUCTION_EVENT_BID_BELOW_RESERVE,
                                 this_player(), auct, value, auct->reserve)) {
         add_failed_mess("You must bid more than the reserve bid, it is " +
                      MONEY_HAND->money_value_string(auct->reserve, place) + ".\n");
      }
      return 0;
   }
   bid_on_item(auct, value, this_player()->query_cap_name());
   save_me();
   if (!broadcast_shop_event(AUCTION_EVENT_BID,
                             this_player(), auct, value)) {
      add_succeeded_mess("$N $V " +
                         MONEY_HAND->money_value_string(value, place) +
                         " on " + auct->name + ".\n");
   }
   return 1;
}
int do_withdraw(string id) {
   class auction auct;
   string place;
   int value;
   object* obs;
   object ob;
   if (!is_open(this_player(), 0)) {
      add_failed_mess(this_object()->the_short() + " is not open.\n");
      return 0;
   }
   auct = query_auction_item(id);
   if (!auct) {
      if (!broadcast_shop_event(AUCTION_EVENT_BAD_ITEM,
                                 this_player(), id)) {
         add_failed_mess("There is no auction item " + id + ".\n");
      }
      return 0;
   }
   place = query_property("place");
   if (lower_case(auct->seller) == this_player()->query_name() ||
       this_player()->query_creator()) {
      if (auct->reserve > auct->bid) {
         value = auct->reserve;
      } else {
         value = auct->bid;
      }
      if (this_player()->query_value_in(place) < value) {
         if (!broadcast_shop_event(AUCTION_EVENT_TOO_POOR,
                              this_player(), auct,
                              this_player()->query_value_in(place),
                              auct->bid)) {
            add_failed_mess("You need at least " +
                            MONEY_HAND->money_value_string(value, place) +
                            " to withdraw this item from auction.\n");
         }
         return 0;
      }
      obs = query_auction_objects(auct);
      this_player()->pay_money(MONEY_HAND->create_money_array(value, place),
        place);
      remove_auction_item(auct);
      save_me();
      if (auct->end_function) {
         call_other(this_object(), auct->end_function,
                    AUCTION_WITHDRAW_PHASE, auct, auct->extra);
      }
      foreach (ob in obs) {
         if (ob->move(this_player()) != MOVE_OK) {
             ob->move(this_object());
             write("Unable to move " + ob->the_short() +
                   " into your inventory, put on the floor.\n");
         }
      }
      if (!broadcast_shop_event(AUCTION_EVENT_WITHDRAW,
                                 this_player(), auct)) {
         add_succeeded_mess("$N remove$s " + auct->name + " from auction.\n");
      }
      return 1;
   }
   if (!broadcast_shop_event(AUCTION_EVENT_CANNOT_WITHDRAW,
                              this_player(), auct)) {
      add_failed_mess("You cannot withdraw that item from auction.\n");
   }
   return 0;
}
int do_claim() {
   class auction auction;
   int num;
   string place;
   object* obs;
   object ob;
   int i;
   int value;
   if (!is_open(this_player(), 0)) {
      add_failed_mess(this_object()->the_short() + " is not open.\n");
      return 0;
   }
   place = query_property("place");
   value = this_player()->query_value_in(place);
   foreach (auction in _finished_auctions) {
      if (!auction->current_bidder) {
         remove_finished_auction_item(auction);
      } else if (lower_case(auction->current_bidder) == this_player()->query_name()) {
         if (value < auction->bid) {
            if (!broadcast_shop_event(AUCTION_EVENT_TOO_POOR,
                              this_player(), auction, value, auction->bid)) {
               write("You do not have enough money to pay for " +
                     MONEY_HAND->money_value_string(auction->bid, place) +
                     ".\n");
            }
         } else {
            this_player()->pay_money(
                MONEY_HAND->create_money_array(auction->bid, place), place);
            value -= auction->bid;
            _royalties[lower_case(auction->seller)] += auction->bid -
                                           auction->bid * _cut / 100;
            obs = AUTO_LOAD_OB->load_auto_load_to_array(auction->save_stuff);
            foreach (ob in obs) {
               if (ob->move(this_player()) != MOVE_OK) {
                  ob->move(this_object());
                  write("Unable to move " + ob->the_short() +
                        " into your inventory, put on the floor.\n");
               }
            }
            if (!broadcast_shop_event(AUCTION_EVENT_CLAIM,
                              this_player(), auction, auction->bid, obs)) {
               write("You paid " +
                     MONEY_HAND->money_value_string(auction->bid, place) +
                     " for " +
                     query_multiple_short(obs) + ".\n");
            }
            remove_finished_auction_item(auction);
            save_me();
            if (auction->end_function) {
               call_other(this_object(), auction->end_function,
                          AUCTION_CLAIM_PHASE, auction, auction->extra,
                          auction->current_bidder, auction->bid, obs);
            }
         }
         num++;
      }
      i++;
   }
   if (!num) {
      if (!broadcast_shop_event(AUCTION_EVENT_NOTHING_TO_CLAIM,
                              this_player())) {
         add_failed_mess("You cannot find anything to claim.\n");
      }
   }
   return num;
}
int do_add(string name, object* obs, string res_str, string length) {
   int reserve;
   string ret;
   string place;
   int len;
   if (!is_open(this_player(), 0)) {
      add_failed_mess(this_object()->the_short() + " is not open.\n");
      return 0;
   }
   place = query_property("place");
   len = _auction_times[length];
   if (sizeof(_auctions) >= _max_auctions) {
      if (!broadcast_shop_event(AUCTION_EVENT_FULL,
                             this_player(), name, obs, reserve, len)) {
         add_failed_mess("The auction house is full.\n");
      }
      return 0;
   }
   if (res_str) {
      reserve = MONEY_HAND->value_from_string(res_str, place);
      if (!reserve) {
         if (!broadcast_shop_event(AUCTION_EVENT_BAD_MONEY,
                             this_player(), name, obs, reserve, len)) {
            add_failed_mess("Unable to figure out how much " + res_str +
                            " is.\n");
         }
         return 0;
      }
   }
   ret = "You are putting " + query_multiple_short(obs) + " up for "
         "auction as " + name + " for " +
          query_time_end_string(len);
   if (reserve) {
     ret += " with a reserve price of " +
            MONEY_HAND->money_value_string(reserve, place);
   }
   if (!broadcast_shop_event(AUCTION_EVENT_ADD_AUCTION,
                             this_player(), name, obs, reserve, len, ret + ".")) {
      write(ret + ".\n");
      write("Are you sure you wish to do this? ");
   }
   input_to("confirm_auction", 0, name, obs, reserve, len);
   add_succeeded_mess(({ "", "$N put$s $I up for auction.\n" }), obs);
   return 1;
}
void confirm_auction(string check, string name, object* obs, int reserve, int len) {
   string place;
   string ret;
   place = query_property("place");
   check = lower_case(check);
   if (!strlen(check) || check[0] != 'y') {
      if (!broadcast_shop_event(AUCTION_EVENT_ADD_ABORT,
                             this_player(), name, obs, reserve, len)) {
         write("Ok, Aborting.\n");
      }
      return ;
   }
   add_item_to_auction(obs, name, reserve,
                       this_player()->query_cap_name(), len, 0, 0);
   ret = "You put " + query_multiple_short(obs) + " up for "
         "auction as " + name + " for " +
          query_time_end_string(len);
   if (reserve) {
     ret += " with a reserve price of " +
            MONEY_HAND->money_value_string(reserve, place) + "";
   }
   if (!broadcast_shop_event(AUCTION_EVENT_CONFIRM_AUCTION,
                             this_player(), name, obs, reserve, len, ret + ".")) {
      write(ret + ".\n");
   }
   obs->move("/room/rubbish");
}
int do_info() {
   string ret;
   string name;
   int len;
   if (!is_open(this_player(), 0)) {
      add_failed_mess(this_object()->the_short() + " is not open.\n");
      return 0;
   }
   ret = "$I$3=The times for the auction are:\n";
   foreach (name, len in _auction_times) {
      ret += name + ": " + query_time_end_string(len) + "\n";
   }
   if (!broadcast_shop_event(AUCTION_EVENT_INFO, this_player(), ret)) {
      write("$P$Auction lengths$P$" + ret);
   }
   return 1;
}
void init() {
   add_command("list", "", (: do_list() :));
   add_command("browse", "<string'auction id'>", (: do_browse($4[0]) :));
   add_command("bid", "<string'auction id'> for <string'money'>",
               (: do_bid($4[0], $4[1]) :));
   add_command("bid", "<string'money'> on <string'auction id'>",
               (: do_bid($4[1], $4[0]) :));
   add_command("claim", "", (: do_claim() :));
   add_command("withdraw", "<string'auction id'> [from auction]",
                (: do_withdraw($4[0]) :));
   if (_allow_add) {
      if (!_bid_type_names) {
         _bid_type_names = implode(keys(_auction_times), "|");
      }
      add_command("info", "", (: do_info() :));
      add_command("add", "{" + _bid_type_names +
                   "} auction of <indirect:object:me> as <string'name'>",
                  (: do_add($4[2], $1, 0, $4[0]) :));
      add_command("add", "{" + _bid_type_names +
                  "}  auction of <indirect:object:me> as <string'name'> reserve <string'price'>",
                  (: do_add($4[2], $1, $4[3], $4[0]) :));
   }
}