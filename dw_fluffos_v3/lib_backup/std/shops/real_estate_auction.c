inherit "/std/shops/auction_house";
#include <housing.h>
#include <money.h>
#include <move_failures.h>
#include <room/auction.h>
#include <nomic_system.h>
#include <morpork.h>
#define AUCTION_LENGTH (3600*24*5)
#define NEW_AGREEMENT_COST 4000
#define REAL_ESTATE_NEW_LOT_BIDDING "new_low_bidding"
private nosave string* _areas;
private nosave string _city;
private nosave string _language;
int add_house(string house);
int check_can_bid(object person,
                  class auction which,
                  int bid_amount);
void create() {
   _areas = ({ });
   _city = "Ankh-Morpork";
   _language = "morporkian";
   ::create();
   add_help_file("real_estate");
}
void reset()
{
   call_out("after_reset", 10);
}
void add_housing_area(string area) {
   _areas += ({ area });
}
string* query_housing_areas() {
   return _areas;
}
void after_reset()
{
   string house;
   string *available;
   int i;
   string area;
   foreach (area in _areas) {
      available = HOUSING->query_vacant(area);
      if (sizeof(available)) {
        i = 1;
        foreach(house in available) {
          call_out("add_house", i++, house);
        }
      }
   }
}
int add_house(string house)
{
   object agreement;
   string text;
   int tim;
   if (member_array(house, keys(HOUSING->query_houses())) == -1) {
      return 0;
   }
   if(lower_case(HOUSING->query_owner(house)) != "for sale") {
     log_file("REAS", ctime(time()) + ": attempt to add house %s that's "
              "not for sale.\n", house);
     return 0;
   }
   HOUSING->set_rent(house, 0);
   agreement = clone_object(AGREEMENT);
   agreement->set_city(_city);
   agreement->set_language(_language);
   agreement->set_house(house);
   text = HOUSING->query_address(house);
   tim = query_last_auction_finish_time();
   if (tim + 60 * 60 < time() + query_auction_times()["very long"]) {
      tim = 0;
   } else {
      tim = tim + 60 * 60 - time();
   }
   if (add_item_to_auction(({ agreement }), text,
                           400, "Patrician", tim,
                           "housing_auction", house)) {
      HOUSING->set_under_offer(house);
      broadcast_shop_event(REAL_ESTATE_NEW_LOT_BIDDING, this_player(),
                           house);
      log_file("REAS", ctime(time()) + ": Added house %s\n", house);
      return 1;
   }
}
void housing_auction(int event_type,
                     class auction auct,
                     string house,
                     string buyer,
                     int cost,
                     object *obs)
{
   object book;
   switch (event_type) {
   case AUCTION_WITHDRAW_PHASE:
     if(lower_case(HOUSING->query_owner(house)) != "under offer") {
       write("House is not currently under offer!\n");
       log_file("REAS", ctime(time()) + ": attempted to withdraw %s when it "
                "was not 'Under Offer'.\n", house);
     } else {
       HOUSING->set_for_sale(house);
       log_file("REAS", ctime(time()) + ": %s back to For Sale.\n", house);
     }
     break;
   case AUCTION_CLAIM_PHASE:
      HOUSING->set_owner(house, buyer);
      HOUSING->set_value(house, cost);
      obs[0]->set_city(_city);
      obs[0]->set_language(_language);
      obs[0]->set_house(house);
      log_file("REAS", ctime(time()) + ": %O sold to %O for %O.\n",
               house, buyer,
               MONEY_HAND->money_value_string(cost, query_property("place")));
      book = clone_object(BOOK);
      if (book) {
         if (book->move(this_player()) != MOVE_OK) {
            book->move(this_object());
         }
      }
      write("A nice new house owner's guide pops up for you.\n");
      break;
   }
}
int do_agreement()
{
   string *houses;
   int i;
   string place;
   place = query_property("place");
   if (this_player()->query_value_in(place) < NEW_AGREEMENT_COST) {
      add_failed_mess("You need " +
                      MONEY_HAND->
                      money_value_string(NEW_AGREEMENT_COST,
                                         place) +
                      " to get a new agreement.\n");
      return 0;
   }
   houses = filter(keys(HOUSING->query_houses()),
                   (: HOUSING->query_owner($1) == $2 :),
                   this_player()->query_name());
   if (!sizeof(houses)) {
      add_failed_mess("You are not renting any houses.\n");
      return 0;
   }
   for (i = 0; i < sizeof(houses); i++) {
      printf("%c) %s %s\n", i + 'A',
             HOUSING->query_address(houses[i]),
             HOUSING->query_region(houses[i]));
   }
   write("It will cost you " + MONEY_HAND->
                      money_value_string(NEW_AGREEMENT_COST,
                                         place) + " for a new "
         "agreement.\n");
   write("Which house to choose? ");
   input_to("new_agreement_choice", 0, houses);
   add_succeeded_mess(({ "",
                         "$N enquires about a new rental agreement.\n" }));
   return 1;
}
protected void new_agreement_choice(string choice,
                          string *houses)
{
   int index;
   object agreement;
   string place;
   place = query_property("place");
   choice = lower_case(choice);
   if (!strlen(choice)) {
      write("Ok, canceling agreement check.\n");
      return;
   }
   index = choice[0] - 'a';
   if (index < 0 || index >= sizeof(houses)) {
      write("Choice out of bounds.\n");
      return;
   }
   if (this_player()->query_value_in(place) < NEW_AGREEMENT_COST) {
      add_failed_mess("You need " +
                      MONEY_HAND->
                      money_value_string(NEW_AGREEMENT_COST,
                                         place) +
                      " to get a new agreement.\n");
      return 0;
   }
   this_player()->pay_money(MONEY_HAND->
                            create_money_array(NEW_AGREEMENT_COST, place));
   agreement = clone_object(AGREEMENT);
   agreement->set_city(_city);
   agreement->set_language(_language);
   agreement->set_house(houses[index]);
   if (agreement->move(this_player()) != MOVE_OK) {
      write("Unable to move the agreement into your inventory.\n");
      return 0;
   }
   write("Created a new agreement for " +
         HOUSING->query_address(houses[index]) + ".\n");
}
int check_can_bid(object person,
                  class auction which,
                  int bid_amount)
{
   int total_money,
     total_bids;
   string *accounts;
   string account;
   class auction auction;
   accounts = "/obj/handlers/bank_handler"->query_accounts(person->
                                                           query_name());
   foreach(account in accounts) {
      total_money += "/obj/handlers/bank_handler"->query_account(person->
                                                                 query_name(),
                                                                 account);
   }
   foreach(auction in query_auctions()) {
      if (auction->current_bidder &&
          lower_case(auction->current_bidder) == person->query_name()) {
         total_bids += auction->bid;
      }
   }
   if (total_bids + bid_amount > total_money * 3) {
      add_failed_mess
         ("You do not have sufficient funds in your bank accounts "
          "to cover such a bid.\n");
      return 0;
   }
   return 1;
}
void init()
{
   ::init();
   add_command("request", "[agreement]", (: do_agreement() :));
}
void reset_auctions_to_under_offer() {
    class auction auc;
    foreach( auc in query_auctions() ) {
        HOUSING->set_under_offer(auc->extra);
    }
}
void set_city( string where ) {
    _city = where;
}
void set_language( string lang ) {
    _language = lang;
}
string query_city() {
    return _city;
}
string query_language() {
    return _language;
}
mixed *stats() {
  return ::stats() +
    ({
        ({ "areas", _areas }),
        ({ "city", _city }),
        ({ "language", _language }),
    });
}