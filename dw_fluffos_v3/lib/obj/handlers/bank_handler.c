#define RESTORE_PATH "/save/bank_accounts/"
#define CHEAT_THRESHOLD 200000
class franchise {
   string office;
   int cost_per_month;
   int cost_per_new_account;
}
class bank_data {
   string master_office;
   class franchise* franchises;
   int cost_to_start;
   int default_cost_per_month;
   int default_cost_per_new_account;
}
private mapping accounts;
private nosave mapping _banks;
void do_cheat_check(string, string, int, string, int);
void create() {
   string str;
   _banks = ([ ]);
   str = unguarded((: read_file, RESTORE_PATH + "bank_data.o" :));
   if (str) {
      _banks = restore_variable(str);
   }
}
private void save_banks() {
   unguarded((: write_file, RESTORE_PATH + "bank_data.o",
                save_variable(_banks), 1 :));
}
private void init_data( string word ) {
  accounts = ([ ]);
}
int get_data_file( string name ) {
  int success;
  success = unguarded((: restore_object, RESTORE_PATH+
           name[0..0]+"/"+name :));
  if(!success) {
    init_data(name);
    return success;
  }
  return 1;
}
private void save_data_file( string name ) {
  if(!unguarded((: save_object, RESTORE_PATH+name[0..0]+"/"+name :)))
    debug_printf("Problem saving " + RESTORE_PATH+name[0..0]+"/"+name);
}
int query_account( string word, string bank_name ) {
  get_data_file( word );
  if ( !accounts ) {
    return -1;
  }
  if ( member_array( bank_name, m_indices( accounts ) ) == -1 ) {
    return -1;
  }
  return accounts[ bank_name ];
}
void adjust_account( string name, string bank_name, int amount ) {
  int before;
  get_data_file( name );
  before = accounts[ bank_name ];
  accounts[bank_name] += amount;
  if ( accounts[ bank_name ] < 0 ) {
    accounts = m_delete( accounts, bank_name );
  }
  do_cheat_check(name, bank_name, amount, "by", before);
  save_data_file( name );
  return;
}
void set_account( string name, string bank_name, int amount ) {
  int before;
  get_data_file( name );
  before = accounts[ bank_name ];
  if ( amount < 0 ) {
    accounts = m_delete( accounts, bank_name );
  } else {
    accounts[ bank_name ] = amount;
  }
  do_cheat_check(name, bank_name, amount, "to", before);
  save_data_file( name );
  return;
}
string *query_accounts(string player) {
  get_data_file(player);
  if(!accounts)
    return ({ });
  return keys(accounts);
}
void create_new_bank(string name, string master) {
   class bank_data data;
   if (_banks[name]) {
      return ;
   }
   data = new(class bank_data);
   data->master_office = master;
   data->franchises = ({ });
   data->cost_to_start = 2600000;
   data->default_cost_per_month = 360000;
   data->default_cost_per_new_account = 400;
   _banks[name] = data;
   save_banks();
}
void remove_bank(string name) {
   map_delete(_banks, name);
   save_banks();
}
class bank_data query_bank_data(string name) {
   return copy(_banks[name]);
}
void add_new_franchise(string name, string franchise_office) {
   class franchise franchise;
   if (!_banks[name]) {
      return ;
   }
   foreach (franchise in _banks[name]->franchises) {
      if (franchise->office == franchise_office) {
         return ;
      }
   }
   franchise = new(class franchise);
   franchise->office = franchise_office;
   franchise->cost_per_month = _banks[name]->default_cost_per_month;
   franchise->cost_per_new_account = _banks[name]->default_cost_per_new_account;
   _banks[name]->franchises += ({ franchise });
   save_banks();
   return ;
}
void set_bank_default_cost_to_open(string name, int amount) {
   if (!_banks[name]) {
      return ;
   }
   _banks[name]->cost_to_start = amount;
   save_banks();
   return ;
}
void set_bank_default_cost_per_new_account(string name, int amount) {
   if (!_banks[name]) {
      return ;
   }
   _banks[name]->default_cost_per_new_account = amount;
   save_banks();
   return ;
}
void set_bank_franchise_cost_per_month(string name, string franchise_office,
                                     int amount) {
   class franchise franchise;
   if (!_banks[name]) {
      return ;
   }
   foreach (franchise in _banks[name]->franchises) {
      if (franchise->office == franchise_office) {
         franchise->cost_per_month = amount;
         save_banks();
         return ;
      }
   }
   return ;
}
void set_bank_franchise_cost_per_new_account(string name, int amount) {
   if (!_banks[name]) {
      return ;
   }
   _banks[name]->cost_per_new_account = amount;
   save_banks();
   return ;
}
void set_bank_default_cost_per_month(string name, int amount) {
   if (!_banks[name]) {
      return ;
   }
   _banks[name]->default_cost_per_month = amount;
   save_banks();
   return ;
}
int query_bank_default_cost_to_open(string name) {
   if (!_banks[name]) {
      return -1;
   }
   return _banks[name]->cost_to_start;
}
int query_bank_default_cost_per_new_account(string name) {
   if (!_banks[name]) {
      return -1;
   }
   return _banks[name]->default_cost_per_new_account;
}
int query_bank_franchise_cost_per_month(string name, string franchise_office) {
   class franchise franchise;
   if (!_banks[name]) {
      return -1;
   }
   foreach (franchise in _banks[name]->franchises) {
      if (franchise->office == franchise_office) {
         return franchise->cost_per_month;
      }
   }
   return -1;
}
int query_bank_franchise_cost_per_new_account(string name,
                                              string franchise_office) {
   class franchise franchise;
   if (!_banks[name]) {
      return -1;
   }
   foreach (franchise in _banks[name]->franchises) {
      if (franchise->office == franchise_office) {
         return franchise->cost_per_new_account;
      }
   }
   return -1;
}
int query_bank_default_cost_per_month(string name) {
   if (!_banks[name]) {
      return -1;
   }
   return _banks[name]->default_cost_per_month;
}
string query_bank_master_office(string name) {
   if (!_banks[name]) {
      return 0;
   }
   return _banks[name]->master_office;
}
void set_bank_master_office(string name, string master) {
   if (!_banks[name]) {
      return 0;
   }
   _banks[name]->master_office = master;
   save_banks();
}
string* query_banks() {
   return keys(_banks);
}
string* query_franchises(string bank) {
   if (!_banks[bank]) {
      return ({ });
   }
   return map(_banks[bank]->franchises, (: $1->office :) );
}
void do_cheat_check(string name, string bank_name, int amount,
                    string str, int after) {
#ifdef LOGGING
  if((amount - after) > CHEAT_THRESHOLD) {
    log_file ("BANK_CHEAT", sprintf ("%s: %s deposited %d into %s.\n",
                                     ctime(time()), name, (amount-after),
                                     bank_name));
  }
#endif
}