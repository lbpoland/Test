inherit "/std/object";
#include <money.h>
#define OBJECT_TAG "credit note"
private int _id;
private int _amount;
private string _franchise;
private string _bank;
void setup() {
   set_name("note");
   set_short("bank credit note");
   add_adjective( ({ "bank", "credit" }) );
   set_long("A small piece of paper which looks like some sort of "
            "bank transaction slip.\n");
   set_value(0);
   set_weight(1);
}
void setup_read_messages() {
   string extra;
   string place;
   place = query_property("place");
   if (_amount < 0) {
     extra = "Agrees to pay " +
             MONEY_HAND->money_value_string(-_amount, place) +
             " to the master bank.\n";
   } else {
     extra = "Slip for a withdrawl of " +
             MONEY_HAND->money_value_string(-_amount, place) +
             " from the master bank.\n";
   }
   add_read_mess("Credit note #" + _id + " for the bank " +
                    _bank + " from the franchise " +
                    _franchise->query_address() + ".\n\n" + extra,
                    0, "common", 0);
}
void set_credit_num(int num) {
   _id = num;
}
int query_credit_num() {
   return _id;
}
void set_bank_name(string bank) {
   _bank = bank;
}
string query_bank_name() {
   return _bank;
}
void set_franchise(string franchise) {
   _franchise = franchise;
}
string query_franchise() {
   return _franchise;
}
void set_amount(int amount) {
   _amount = amount;
}
int query_amount() {
   return _amount;
}
int is_valid_note() {
   object bank;
   object* obs;
   object ob;
   int ret;
   bank = load_object(query_franchise());
   obs = bank->find_commercial_items("bank");
   if (sizeof(obs)) {
      foreach (ob in obs) {
         ret = ob->is_valid_note(query_credit_num());
         if (ret) {
            return 1;
         }
      }
   }
   return 0;
}
int do_process() {
   object bank;
   object* obs;
   object ob;
   int ret;
   bank = load_object(query_franchise());
   obs = bank->find_commercial_items("bank");
   if (sizeof(obs)) {
      foreach (ob in obs) {
         ret = ob->process_note(query_credit_num());
         if (ret) {
            return 1;
         }
      }
   }
   return 0;
}
mixed* stats() {
   return ::stats() +
          ({ ({ "credit amount", query_amount() }),
             ({ "franchise", query_franchise() }),
             ({ "credit id", query_credit_num() }), });
}
mapping query_dynamic_auto_load() {
   mapping map;
   map = ::query_dynamic_auto_load();
   add_auto_load_value(map, OBJECT_TAG, "amount", query_amount());
   add_auto_load_value(map, OBJECT_TAG, "franchise", query_franchise());
   add_auto_load_value(map, OBJECT_TAG, "id", query_credit_num());
   add_auto_load_value(map, OBJECT_TAG, "bank", query_bank_name());
   return map;
}
void init_dynamic_arg(mapping map) {
   ::init_dynamic_arg(map);
   set_amount(query_auto_load_value(map, OBJECT_TAG, "amount"));
   set_franchise(query_auto_load_value(map, OBJECT_TAG, "franchise"));
   set_credit_num(query_auto_load_value(map, OBJECT_TAG, "id"));
   set_bank_name(query_auto_load_value(map, OBJECT_TAG, "bank"));
}