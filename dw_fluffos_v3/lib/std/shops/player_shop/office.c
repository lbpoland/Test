inherit "/std/room/basic_room";
#include <player_shop.h>
#include <mail.h>
#include <board.h>
#include <money.h>
#include <move_failures.h>
#include <refresh.h>
#include "office.h"
private nosave string _proprietor = UNSET_STR,
                      _shop_name = UNSET_STR,
                      _very_short = UNSET_STR,
                      _place = UNSET_STR,
                      _channel = UNSET_STR,
                      _storeroom = "",
                      _shop_front = "",
                      _counter = "",
                      _mgr_office = "",
                      _store_dir = "",
                      _counter_dir = "",
                      _shop_dir = "",
                      _shopkeeper = "",
                      _stock_policy = "",
                      _cab_name = "",
                      _review_month = "",
                      _savedir = "",
                      _creator = CREATOR;
private nosave object _chart = 0,
                      _board = 0,
                      _notice = 0;
private nosave mapping _history = 0,
                       _applicants = 0,
                       _policies = 0,
                       _new_policies = 0,
                       _list = ([]),
                       _times = ([]),
                       _employees = ([]);
private nosave int _call_save = 0,
                   _call_hist = 0,
                   _call_hist_clear = 0,
                   _call_times = 0,
                   _call_hire_list = 0,
                   _call_mail_hirees = 0,
                   _call_summon = 0,
                   _call_emps = 0,
                   _call_review = 0,
                   _call_apps = 0,
                   _call_apps_clear = 0,
                   _call_pols = 0,
                   _call_pols_clear = 0,
                   _call_newpols = 0,
                   _call_newpols_clear = 0;
private string *_retired = ({}),
               *_got_bonus = ({}),
               _last_month = "last month",
               _eom = CREATOR;
private mapping _baddies = ([]),
                _declined = ([]),
                _accounts = (["profit":0,"bonus":0]);
private int _max_emp = MAX_EMP,
            _bonus_val = 0,
            _bonus = 0,
            _pay_val = 4,
            _num_cabinets = MIN_CABINETS,
            _net_takings = 0;
private mixed *_register = ({});
void create()
{
   do_setup++;
   ::create();
   do_setup--;
   if (!do_setup)
   {
      this_object()->setup();
      this_object()->reset();
   }
   seteuid("Room");
   add_property("determinate", "");
   add_help_file("player_shop_office");
}
#include "office_code/admin.c"
#include "office_code/applications.c"
#include "office_code/baddies.c"
#include "office_code/cabinets.c"
#include "office_code/emp_cmd.c"
#include "office_code/lists.c"
#include "office_code/logging.c"
#include "office_code/masked.c"
#include "office_code/memo.c"
#include "office_code/personnel.c"
#include "office_code/policies.c"
#include "office_code/review.c"
#include "office_code/save.c"
#include "office_code/stock.c"
protected void add_manager_exit(string dir, string path)
{
   add_exit(dir, path, "door");
   modify_exit(dir, ({"function", ({this_object(),
     "check_manager"}), "door short", "office door", "door long",
     "There is a sign on the door which reads: \""+ _proprietor+
     "- Private\".\n"}));
   _mgr_office = path;
}
mapping get_applicants()
{
   load_applicants();
   clear_applicants();
   return copy(_applicants + ([]));
}
mapping get_baddies() { return copy(_baddies + ([])); }
string *get_employees()
{
   string *employees = m_indices(_employees);
   foreach (string word in employees)
      if (_employees[word][EMP_POINTS] & SUPERVISOR)
         employees -= ({word});
   return copy(sort_array(employees, 1));
}
string *get_managers()
{
   return copy(sort_array(keys(filter(_employees,
        (: _employees[$1][EMP_POINTS] & MANAGER :))), 1));
}
mapping get_new_policies()
{
   load_new_policies();
   clear_new_policies();
   return copy(_new_policies);
}
mapping get_policies(int type)
{
   load_policies();
   clear_policies();
   if (type)
      return copy(filter(_policies, (: _policies[$1][1] :)));
   else
      return copy(filter(_policies, (: !_policies[$1][1] :)));
}
string *get_retired() { return copy(sort_array(_retired, 1)); }
string *get_supervisors()
{
   string *supervisors = keys(filter(_employees,
        (: _employees[$1][EMP_POINTS] & SUPERVISOR :)));
   foreach (string word in supervisors)
      if (_employees[word][EMP_POINTS] & MANAGER)
         supervisors -= ({word});
   return copy(sort_array(supervisors, 1));
}
int num_employees_in()
{
   int any = 0;
   foreach (string word in m_indices(_employees))
      if (_employees[word][EMP_POINTS] & CLOCKED_IN)
      {
         if (_employees[word][EMP_POINTS] & NPC) continue;
         if (!find_player(word) || !interactive(find_player(word)))
         {
            reset_employee(word, CLOCKED_IN);
            shop_log(GENERAL, word, "was clocked out", UNPAID);
         }
         else any++;
      }
   return any;
}
int query_applicant(string player)
{
   load_applicants();
   clear_applicants();
   if (!sizeof(_applicants)) return FALSE;
   if (_applicants[player]) return copy(_applicants[player][APP_TYPE]);
   return FALSE;
}
int query_baddie(string player)
{
   if (!m_sizeof(_baddies)) return FALSE;
   if (_baddies[player]) return copy(_baddies[player][BAD_TIME]);
   return FALSE;
}
int query_bonus() { return copy(_accounts["bonus"]); }
string query_channel() { return copy(_channel); }
string query_counter() { return copy(_counter); }
void query_creator(string creator) { return copy(_creator); }
int query_declined(string player)
{
   if (!sizeof(_declined)) return FALSE;
   if (_declined[player]) return copy(_declined[player]);
   return FALSE;
}
int query_employee(string player)
{
   if (_employees[player]) return copy(_employees[player][EMP_POINTS]);
   return FALSE;
}
mapping query_employees() { return copy(_employees + ([])); }
string *query_list_array() { return copy(m_indices(_list) + ({})); }
mapping query_list_mapping() { return copy(_list) + ([]); }
string query_list_string()
{
   if (!m_sizeof(_list)) return "absolutely nothing at the moment";
   return query_multiple_short(m_indices(_list));
}
int query_manager(string player)
{
   if (_employees[player]) return (_employees[player][EMP_POINTS] & MANAGER);
   return FALSE;
}
int query_maxemp() { return copy(_max_emp); }
string query_mgr_office() { return copy(_mgr_office); }
int query_num_cabinets() { return copy(_num_cabinets); }
int query_pay() { return copy(_pay_val); }
string query_place() { return copy(_place); }
int query_policy(string policy)
{
   load_policies();
   clear_policies();
   if (m_sizeof(_policies) && _policies[policy]) return 2;
   load_new_policies();
   clear_new_policies();
   if (m_sizeof(_new_policies) && _new_policies[policy]) return 1;
   return 0;
}
int query_profit() { return copy(_accounts["profit"]); }
string query_proprietor() { return copy(_proprietor); }
int query_retired(string player)
{
   return (member_array(player, _retired) == -1)?FALSE:TRUE;
}
string query_savedir() { return copy(_savedir); }
string query_shop_front() { return copy(_shop_front); }
string query_shop_name() { return copy(_shop_name); }
string query_shopkeeper() { return copy(_shopkeeper); }
int query_stock(string items) { return _storeroom->query_num_items(items, 0); }
string query_storeroom() { return copy(_storeroom); }
int query_supervisor(string player)
{
   if (_employees[player])
      return (_employees[player][EMP_POINTS] & SUPERVISOR);
   return FALSE;
}
protected void save_emps()
{
   if (_very_short == UNSET_STR) return;
   remove_call_out(_call_emps);
   _call_emps = call_out((: do_save_emps() :), SAVE_DELAY);
}
protected void save_me()
{
   if (_very_short == UNSET_STR) return;
   remove_call_out(_call_save);
   _call_save = call_out((: do_save() :), SAVE_DELAY);
}
protected void set_channel(string name, int board)
{
   _channel = lower_case(name);
   if (board)
   {
      _board = clone_object("/obj/misc/board");
      _board->set_datafile(name);
      _board->move(this_object());
   }
}
protected void set_counter(string path) { _counter = path; }
protected void set_creator(string creator) { _creator = creator; }
protected void set_directions(string store, string counter, string shop)
{
   _store_dir = store;
   _counter_dir = counter;
   _shop_dir = shop;
}
protected void set_place(string place) { _place = place; }
protected void set_proprietor(string name) { _proprietor = name; }
protected void set_shop_front(string path) { _shop_front = path; }
protected void set_shop_name(string name) { _shop_name = name; }
protected void set_shopkeeper(string path)
{
   _shopkeeper = path;
   path=_shopkeeper->query_name();
   if (!_employees || !_employees[path])
   {
      _employees += ([path:EMP_MAP]);
      _employees[path][EMP_POINTS] = EMPLOYEE + NPC;
   }
}
protected void set_storeroom(string path) { _storeroom = path; }
protected void set_stock_policy(string desc) { _stock_policy = desc; }
protected void set_very_short(string name)
{
   if (PLAYER_SHOP->query_shop(name) != file_name(this_object()))
      return;
   _very_short = name;
   _savedir = sprintf("/save/player_housing/%s/player_shops/%s/",
      lower_case(geteuid(this_object())), name);
   if (file_size(_savedir+ "shop_data.o") > 0)
      unguarded((: restore_object, _savedir+ "shop_data" :));
   if (file_size(_savedir+ "employees") > 0)
      _employees = restore_variable(unguarded((: read_file,
        _savedir+ "employees" :)));
   if (file_size(_savedir+ "times") > 0)
      _times = restore_variable(unguarded((: read_file,
      _savedir+ "times" :)));
   if (file_size(_savedir+ "list") > 0)
      _list = restore_variable(unguarded((: read_file, _savedir+ "list" :)));
}
string shop_very_short() { return copy(_very_short); }