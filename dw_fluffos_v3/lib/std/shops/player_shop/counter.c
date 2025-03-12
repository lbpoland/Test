inherit "/std/room/basic_room";
#include <player_shop.h>
#include <money.h>
private nosave mixed *_money;
private nosave object _register = 0;
private nosave string _save_file = "",
                      _place = UNSET_STR,
                      _office = "",
                      _storeroom = "",
                      _mgr_office = "",
                      _shop_front = "",
                      _store_dir = "",
                      _office_dir = "",
                      _shop_dir = "";
private nosave int _call_save = 0;
int action(string);
void add_money_ob(object);
int adjust_register(string, int);
string directions_to(string);
private int do_calc(int,string,int);
private int do_correction(mixed);
private int do_log(mixed *);
int query_register();
private void save_me(string);
void save_register(int);
protected void set_office(string);
protected void set_directions(string, string, string);
void create()
{
   do_setup++;
   ::create();
   do_setup--;
   add_property("no burial", 1);
   add_property("determinate", "");
   if (!do_setup)
   {
      this_object()->setup();
      this_object()->reset();
   }
   add_item("calculator", "A standard shop's calculator used to total "
     "up all those difficult prices.  To use, see \"syntax calc\".");
   add_help_file("player_shop_counter");
}
void init()
{
   ::init();
   if (!_office || _office == "") return;
   this_player()->command_override((: action :));
   add_command("calc", "<number> {+|-|*|/} <number>",
     (: do_calc($4[0],$4[1],$4[2]) :));
   if (_office->query_employee(this_player()->query_name()) ||
     this_player()->query_creator())
   {
      add_command("log",
        "shop {bought|sold} <number> <string'item(s)'> for <word'amount'>",
        (: do_log($4) :));
      add_command("correction",
        "shop {bought|sold} <number> <string'item(s)'> for <word'amount'>",
        (: do_correction($4) :));
   }
}
int action(string str)
{
   string st1;
   if (_office->query_employee(this_player()->query_name()) ||
     this_player()->query_creator())
     return 0;
   sscanf(str,"%s %s",str,st1);
   if(str == "get" || str == "take")
      if (strsrch(st1, "register") != -1)
      {
         tell_object(this_player(), "You are not an active employee here!\n");
         return 1;
      }
   return 0;
}
void add_money_ob(object money)
{
   if (previous_object() && previous_object() != find_object(_office))
   {
      LOG_ERROR("counter.c", "add_money_ob()");
      return;
   }
   if (!money) return;
   money->move( _register );
   save_register(TRUE);
}
int adjust_register(string player, int amount)
{
   int value;
   object cash, change;
   if (previous_object() && previous_object() != find_object(_office))
   {
      LOG_ERROR("counter.c", "adjust_register(" + player+","+amount+")");
      return 0;
   }
   if (amount < 0) return 0;
   cash = present(MONEY_ALIAS, _register);
   if ( !cash ) return 0;
   _money = cash->query_money_array() + ({});
   value = MONEY_HAND->query_total_value(_money, _place);
   if (value < amount) amount = value;
   change = MONEY_HAND->pay_amount_from( amount, cash, _place );
   if (change) change->move( _register );
   _office->shop_log(ACCOUNTS, player, "adjusted the register by "+
     MONEY_HAND->money_value_string(amount, _place), UNPAID);
   save_register(TRUE);
   return amount;
}
string directions_to(string place)
{
   if (place == _storeroom) return _store_dir;
   if (place == _office) return _office_dir;
   if (place == _shop_front) return _shop_dir;
   return "here";
}
private int do_calc(int a, string sign, int b)
{
   int c = 0;
   string result = a+ " "+ sign+ " "+ b+ " = ",
          temp;
   switch (sign)
   {
     case "+" :
        result += sprintf("%d\n", a+b);
        break;
     case "-" :
        result += sprintf("%d\n", a-b);
        break;
     case "*" :
        result += sprintf("%d\n", a*b);
        break;
     case "/" :
        if (!b)
        {
           tell_object( this_player(),
             "Trying to divide by zero?  Whatever next?\n");
           return 1;
        }
        if (a % b) c = ((a%b) * 100)/b;
        temp = sprintf("%02d",c);
        result += sprintf("%d.%s\n", a/b, temp[0..1]);
        break;
   }
   tell_object(this_player(), result);
   add_succeeded_mess("$N use$s the calculator.\n");
   return 1;
}
private int do_correction(mixed *args)
{
   _office->shop_log(LOG_ENTRY, this_player()->query_name(),
     "ERROR IN LOG - correct entry follows:", UNPAID);
   _office->shop_log(LOG_ENTRY, this_player()->query_name(),
     args[0]+ " "+ args[1]+ " "+ args[2]+ " for "+ args[3], UNPAID);
   add_succeeded_mess("$N make$s a correction in the transaction log book.\n");
   return 1;
}
private int do_log(mixed *args)
{
   _office->shop_log(LOG_ENTRY, this_player()->query_name(),
     args[0]+ " "+ args[1]+ " "+ args[2]+ " for "+ args[3], PAID);
   add_succeeded_mess("$N make$s an entry in the transaction log book.\n");
   return 1;
}
void event_death(object k, object *o, object k2, string r, string k3)
{
   _office->event_death(k, o, k2, r, k3);
}
void event_enter(object ob, string message, object from)
{
   _office->event_enter(ob, message, from);
}
int query_register()
{
   object cash = present(MONEY_ALIAS, _register);
   if (!cash) return 0;
   _money = cash->query_money_array() + ({});
   return MONEY_HAND->query_total_value(_money, _place);
}
private void save_me(string name)
{
   int difference;
   object cash;
   mixed *old = _money + ({});
   if (!_register) return;
   cash = present(MONEY_ALIAS, _register);
   if (!cash) _money = ({});
   else _money = (mixed *)cash->query_money_array() + ({});
#ifdef DEBUG
   tell_creator(CREATOR, "Register contains: %O.\n", _money);
#endif
   _office->save_register(_money);
   difference = MONEY_HAND->query_total_value(_money, _place) -
     MONEY_HAND->query_total_value(old, _place);
   if (!difference) return;
   _office->adjust_takings(difference);
   if (!name || name == "") return;
   if (difference < 0)
      _office->shop_log(PURCHASE, name, "removed "+
        MONEY_HAND->money_value_string(-difference, _place)+
        " from register", UNPAID);
   else
      _office->shop_log(SALE, name, "added "+
        MONEY_HAND->money_value_string(difference, _place)+
        " to register", UNPAID);
}
void save_register(int no_player)
{
   remove_call_out(_call_save);
   _call_save = call_out((: save_me($((!no_player)?
      this_player()->query_name():"shop")) :), 1);
}
protected void set_directions(string office, string storeroom, string shop)
{
   _office_dir = office;
   _store_dir = storeroom;
   _shop_dir = shop;
}
protected void set_long(string long_desc)
{
   long_desc += "Employees of the shop can \"log\" transactions or "
     "\"correction\"s here.  The shop's cash register is under the "
     "counter and there is a calculator next to that.\n";
   ::set_long(long_desc);
}
protected void set_office(string path)
{
   object cash;
   _office = path;
   _storeroom = _office->query_storeroom();
   _mgr_office = _office->query_mgr_office();
   _shop_front = _office->query_shop_front();
   _place = _office->query_place();
   if (_register) return;
   _register = clone_object("/obj/misc/cash_register");
   _register->set_name("register");
   _register->set_short("cash register");
   _register->add_adjective("cash");
   _register->set_long("The cash register is really just an iron drawer "
     "mounted underneath the counter.  In a certain light, it almost "
     "seems tongue-shaped.\n");
   _register->set_shop(this_object());
   add_hidden_object(_register);
   _register->reset_get();
   _money = _office->restore_register();
   if (!_money || !sizeof(_money)) return;
   cash = clone_object(MONEY_OBJECT);
   cash->set_money_array(_money);
   cash->move(_register);
}