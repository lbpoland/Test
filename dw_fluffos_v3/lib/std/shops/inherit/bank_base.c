#include <money.h>
#include <move_failures.h>
#define NAME (string)this_player()->query_name()
#define CAP_NAME (string)this_player()->one_short()
#define POSS (string)this_player()->query_possessive()
#define HANDLER "/obj/handlers/bank_handler"
#define OLD_BANK "/d/am/save/bank"
private string _franchise;
private int _total_difference;
private nosave int _account_cost;
private nosave int _percentage;
private nosave string _bank_name;
string query_money_place();
void adjust_float(int amount);
int is_open_for(string type, string person);
void event_save(object ob);
void create() {
  _account_cost = 400;
  _total_difference = 0;
  _percentage = 10;
}
int query_bank() {
   return 1;
}
int query_account_cost() { return _account_cost; }
void set_account_cost( int number ) { _account_cost = number; }
int query_percentage() { return _percentage; }
void set_percentage( int number ) { _percentage = number; }
int query_total_difference() { return _total_difference; }
void adjust_total_difference(int amount) {
   _total_difference += amount;
}
void set_total_difference(int amount) {
   _total_difference = amount;
}
string query_bank_name() { return _bank_name; }
void set_bank_name( string word ) { _bank_name = word; }
int get_account(string player) {
  return HANDLER->query_account( player, _bank_name );
}
void set_account( string player, int amount ) {
  HANDLER->set_account( player, _bank_name, amount );
}
void adjust_account(string person, int amount) {
}
string query_franchise() {
   return _franchise;
}
void set_franchise(string franchise) {
   _franchise = franchise;
}
int can_adjust_account(string person, int amount) {
   if ( ( get_account( person ) + amount ) >= 0 ) {
      return 1;
   }
   add_failed_mess("You do not have enough money to complete the "
                   "transaction.\n");
   return 0;
}
object find_main_bank() {
   object office;
   string room;
   room = BANK_HANDLER->query_bank_master_office(_bank_name);
   if (!room) {
      return 0;
   }
   office = load_object(room);
   if (!office) {
      return 0;
   }
   if (office->query_bank()) {
      return office;
   }
   return 0;
}
string query_main_branch_owner() {
   object branch;
   branch = find_main_bank();
   if (!branch) {
      return "no owner";
   }
   if (branch->query_owner()) {
      return lower_case(branch->query_owner());
   }
   return "no owner";
}
int do_balance() {
  int amount;
   if (!query_bank_name()) {
      add_failed_mess("This is a forgotten bank in a dusty land.\n");
      return 0;
   }
   if (!is_open_for("bank", this_player()->query_name())) {
      add_failed_mess("The bank is not open for withdrawals.\n");
      return 0;
   }
   amount = get_account(this_player()->query_name());
  if ( amount < 0 ) {
    notify_fail( "You do not have an account here.\n" );
    return 0;
  }
  if ( !amount ) {
     add_succeeded_mess(
       ({ "Your account is empty.\n",
           "$N checks the balance of $p account.\n" }));
    return 1;
  }
  add_succeeded_mess(
     ({ "You have "+ (string)MONEY_HAND->money_value_string( amount,
         query_money_place() ) +
        " in your account.\n",
        "$N checks the balance of $p account.\n" }));
  return 1;
}
int do_withdraw( string type ) {
  int amount;
  int total;
  object money;
   if (this_player()->query_property("dead"))  {
      add_failed_mess("You are dead.  You know what they say; you can't take "
         "it with you.\n");
      return 0;
   }
   if (!query_bank_name()) {
      add_failed_mess("This is a forgotten bank in a dusty land.\n");
      return 0;
   }
   if (!is_open_for("withdraw", this_player()->query_name())) {
      add_failed_mess("The bank is not open for withdrawals.\n");
      return 0;
   }
   total = get_account(this_player()->query_name());
   if ( total < 0 ) {
      notify_fail( "You do not have an account here.\n" );
      return 0;
   }
   amount = MONEY_HAND->value_from_string(type, query_money_place());
   if ( amount <= 0 ) {
      notify_fail( "You must withdraw something.\n" );
      return 0;
   }
   if ( amount > total ) {
      add_failed_mess( "You don't have that much money in your account!\n" );
      return 0;
   }
   if (!can_adjust_account(this_player()->query_name(), -amount)) {
      add_failed_mess("The bank cannot handle this transaction.\n");
      return 0;
   }
   money = MONEY_VAULT->get_money_ob();
   money->set_money_array(MONEY_HAND->create_money_array(amount,
       query_money_place()));
   if (money->move(this_player()) != MOVE_OK)  {
      if (money->move(this_object()) != MOVE_OK) {
         add_failed_mess("Unable to put the money on the floor, cancelling "
               "the transaction.\n");
         money->move("/room/rubbish");
         return 0;
      } else {
         write("You are carrying too much weight to accept your money, "
               "So it is placed on the floor for you.\n");
      }
   }
   set_account(this_player()->query_name(), total - amount );
   adjust_account(this_player()->query_name(), -amount);
   _total_difference -= amount;
   event_save(this_object());
   add_succeeded_mess( ({
      "You withdraw "
      + MONEY_HAND->money_value_string( amount, query_money_place() )
      +".\nYou have "
      + MONEY_HAND->money_value_string( get_account( this_player()->query_name() ),
                                        query_money_place() )
      + " in your account after the withdrawal.\n",
      "$N withdraws some money from $p account.\n"
   }) );
   this_player()->save();
   return 1;
}
int do_deposit( string words ) {
   int amount;
   int total;
   int tmp;
   int howmuch;
   mixed money;
   if (!query_bank_name()) {
      add_failed_mess("This is a forgotten bank in a dusty land.\n");
      return 0;
   }
   if (!is_open_for("deposit", this_player()->query_name())) {
      add_failed_mess("The bank is not open for deposits.\n");
      return 0;
   }
   total = get_account(this_player()->query_name());
   if ( total < 0 ) {
      notify_fail("You don't have an account here.\n");
      return 0;
   }
   money = MONEY_HAND->parse_money(words, this_player(), query_money_place());
   if( money == NO_MATCH ) {
      add_failed_mess( "Deposit what?\n" );
      return 0;
   }
   else if( money == NO_MONEY ) {
      add_failed_mess( "You can't deposit that.\n" );
      return 0;
   }
   else if( money == NO_LEGAL ) {
      add_failed_mess( "You can only deposit legal tender.\n");
      return 0;
   }
   amount = money->query_value_in(query_money_place());
   if(amount < 200) {
      money->move(this_player());
      add_failed_mess("That is too small an amount, you must deposit "
                      "at least " +
                      MONEY_HAND->money_value_string(200, query_money_place()) +
                      ".\n");
      return 0;
   }
   if (!can_adjust_account(this_player()->query_name(), amount)) {
      money->move(this_player());
      add_failed_mess("The bank cannot handle this transaction.\n");
      return 0;
   }
   tmp = ( amount * _percentage ) / 100;
   adjust_float(tmp);
   howmuch = amount;
   amount = amount - tmp;
   set_account(this_player()->query_name(), total + amount );
   _total_difference += amount;
   adjust_account(this_player()->query_name(), amount);
   event_save(this_object());
   money->move("/room/rubbish");
   this_player()->save();
   add_succeeded_mess(
       ({  "You give the teller "+ MONEY_HAND->
           money_string(money->query_money_array(), query_money_place()) +
           ", which after expenses leaves "+ MONEY_HAND->
           money_value_string( amount, query_money_place() ) +".\n"
           "This gives a total of " + MONEY_HAND->
           money_value_string(total + amount, query_money_place() ) +
           " in your account.\n",
           "$N deposits some money into $p account.\n" }) );
   return 1;
}
int do_open() {
  int amount;
  if (!is_open_for("open account", this_player()->query_name())) {
     add_failed_mess("The bank is not open for new accounts.\n");
     return 0;
  }
  if ( get_account(this_player()->query_name()) >= 0 ) {
    notify_fail( "You already have an account here.\n" );
    return 0;
  }
  if ( _account_cost ) {
    amount = this_player()->query_value_in( query_money_place() );
    if ( amount < _account_cost ) {
      notify_fail( "You do not have enough money to open an account.\n" );
      return 0;
    }
    write( "It will cost you "+ (string)MONEY_HAND->money_value_string(
      _account_cost, query_money_place() ) +
      " to open the account.\nDo you still wish to "+
      "open an account here? " );
    input_to( "check_open" );
    return 1;
  }
  set_account(this_player()->query_name(), 0 );
  add_succeeded_mess( "$N $V an account.\n" );
  return 1;
}
void check_open( string word ) {
  object money;
  int amount;
  object main;
  word = lower_case( word );
  if (!strlen(word) || word [ 0 ] !=  'y') {
    write( "Okay, not opening an account.\n" );
    return ;
  }
  amount = this_player()->query_value_in( query_money_place() );
  if (amount < _account_cost) {
    write("You lost all your money!\n");
    return ;
  }
  set_account(this_player()->query_name(), 0 );
  write( "You now have an account here.\n" );
  money = this_player()->query_money_object(0);
  money = MONEY_HAND->pay_amount_from( _account_cost, money, query_money_place() );
  if (money  &&  money->move(this_player()) != MOVE_OK)  {
    write("Your change is too heavy and you drop it on the floor.\n");
    money->move(this_object());
  }
  amount = BANK_HANDLER->query_cost_for_new_account(_bank_name,
                                                    query_franchise());
  main = find_main_bank();
  if (main) {
     main->adjust_float(amount);
  }
  adjust_float(_account_cost - amount);
  return ;
}
int do_close() {
  int total;
  object money;
  total = get_account(this_player()->query_name());
  if ( total < 0 ) {
    notify_fail( "You do not have an account here.\n" );
    return 0;
  }
  if ( total ) {
    if ( money = (object)MONEY_HAND->make_new_amount( total, query_money_place() ) ) {
      write( "You receive "+ (string)money->short() +" on closing "+
        "your account.\n" );
      if ( (int)money->move( this_player() ) != MOVE_OK ) {
        write( "You are too heavily burdened to accept all that money, so "+
          "the teller puts it on the counter for you.\n" );
        money->move( this_object() );
      }
      adjust_float(-total);
      _total_difference -= total;
    } else {
      write( "The amount of money in your account was not even worth a "+
        "coin of the lowest denomination in the local currency.  Sorry.\n"+
        "Your account is now closed.\n" );
    }
  } else {
    write( "You close your account.\n" );
  }
  add_succeeded_mess("$N $V an account.\n");
  set_account(this_player()->query_name(), -1 );
  event_save(this_object());
  this_player()->save();
  return 1;
}
mixed *stats() {
  return ({
    ({ "account cost", _account_cost }),
    ({ "percentage", _percentage }),
    ({ "total difference", _total_difference }),
    ({ "bank name", _bank_name }),
    ({ "place", query_money_place() }) });
}
void init() {
  add_command( "balance", "" );
  add_command( "withdraw", "<string>",
               (: do_withdraw($4[0]) :) );
  add_command( "open", "account" );
  add_command( "close", "account" );
  add_command( "deposit", "<string>", (: do_deposit($4[0]) :) );
}