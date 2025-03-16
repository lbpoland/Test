#define clear_applicants() _call_apps_clear = \
                         call_out((: _applicants = 0 :), CLEAR_DELAY)
#define clear_history() _call_hist_clear = \
                         call_out((: _history = 0 :), CLEAR_DELAY)
#define clear_new_policies() _call_newpols_clear = \
                             call_out((: _new_policies = 0 :), CLEAR_DELAY)
#define clear_policies() _call_pols_clear = \
                         call_out((: _policies = 0 :), CLEAR_DELAY)
#define save_applicants() _call_apps = \
                          call_out((: do_save_applicants() :), SAVE_DELAY);
#define save_hist() _call_hist = \
                          call_out((: do_save_hist() :), SAVE_DELAY);
#define save_new_policies() _call_newpols = \
                          call_out((: do_save_new_policies() :), SAVE_DELAY);
#define save_policies() _call_pols = \
                          call_out((: do_save_policies() :), SAVE_DELAY);
void     add_applicant(string,string);
private void add_baddie( string, string, string);
private void add_board_message(string, string);
private void add_chart_cabinet(string, int);
private void add_declined(string);
private void add_employee(string);
protected void add_manager_exit(string, string);
private void add_policy(string);
void     add_policy_suggest(string, string, string, int);
private void add_vote(string, int);
private void adjust_bonus(string, int);
void     adjust_bought(string, int);
private void adjust_profit(string, int);
void     adjust_sold(string, int);
void     adjust_takings(int);
string   badge_list();
void     calc_bonus();
int      calc_pay();
private string cap_name(string);
void check_hire_list();
int      check_manager(string);
void     confirm_cabinet(string, int);
private void demote(string, string);
string   directions_to(string);
private int do_ban(mixed *);
private int do_bank(mixed);
int do_cancel();
private int do_chart(mixed *, string);
private int do_check();
private int do_claim(string);
private int do_clock(string);
int      do_commend(string);
private int do_confirm();
int      do_demote(string);
int      do_fire(mixed *);
int      do_leave(mixed *);
int      do_list();
int      do_logs(mixed *, string);
private int do_memo();
private int do_office();
private int do_policy_vote(string, string, string);
private int do_promote(string);
int      do_remove();
int      do_rent();
private int do_resign();
int      do_retire();
private void do_save();
private void do_save_applicants();
private void do_save_emps();
private void do_save_hist();
private void do_save_new_policies();
private void do_save_policies();
int      do_set(mixed *, string);
int      do_suspend(mixed *);
int      do_transfer(mixed *);
int      do_unban(string);
int      do_vote(mixed *, string);
int      do_warn(mixed *);
private void employee_log(string, string);
string   employees_clocked_in();
private void end_memo(string,string);
private void fire_them(string, string, string);
mapping  get_applicants();
mapping  get_baddies();
string  *get_employees();
string  *get_managers();
mapping  get_new_policies();
mapping  get_policies(int);
string  *get_retired();
string   get_stock_policy();
string  *get_supervisors();
private void hire(string);
private string list_stuff(string);
private void load_applicants();
private void load_history();
private void load_new_policies();
private void load_policies();
private void mail_hirees();
private void monthly_review();
int      num_employees_in();
private void put_on_list(string);
int      query_applicant(string);
int      query_ave(string);
int      query_baddie(string);
int      query_bonus();
int      query_buy(string);
int     *query_cabinet(string);
int      query_cabinet_used(int);
string   query_channel();
string   query_counter();
void     query_creator(string);
int      query_declined(string);
int      query_employee(string );
mapping  query_employees();
string  *query_list_array();
string   query_list_string();
int      query_manager(string);
int      query_max(string);
int      query_maxemp();
string   query_mgr_office();
int      query_num_cabinets();
int      query_on_list(string);
int      query_pay();
string   query_place();
int      query_policy(string);
int      query_profit();
string   query_proprietor();
int      query_retired(string);
int      query_sell(string);
string   query_shop_front();
string   query_shop_name();
string   query_shopkeeper();
int      query_stock(string);
string   query_storeroom();
int      query_supervisor(string);
private string query_worked(string);
private void remove_applicant(string);
private void remove_baddie(string);
private void remove_chart_cabinet(string, int);
private void remove_declined(string);
private void remove_employee(string);
private void remove_policy(string);
private void remove_retired(string);
private void reset_employee(string, int);
mixed   *restore_register();
private void review_employees();
private void rm_cab();
protected void save_emps();
private void save_list();
protected void save_me();
void     save_register(mixed *);
private void save_times();
private void send_memo(string, string, string);
private void set_buy(string, int);
protected void set_channel(string, int);
protected void set_counter(string);
protected void set_creator(string);
protected void set_directions(string, string, string);
private void set_emp_time(string);
private void set_employee(string, int);
private void set_max(string, int);
protected void set_place(string);
protected void set_proprietor(string);
private void set_sell(string, int);
protected void set_shop_front(string);
protected void set_shop_name(string);
protected void set_shopkeeper(string);
protected void set_stock_policy(string);
protected void set_storeroom(string);
protected void set_very_short(string);
void     shop_log(int, string, string, int);
string   shop_very_short();
void     summon_shopkeeper();
private void take_off_list(string);
private void update_averages();
void     view_record(string,string);
private void write_memo(string);
#define CHART_ADDITEM       "add <string'item'>"
#define CHART_REMITEM       "remove <string'item'>"
#define CHART_MAXITEM       "max <string'item'> <number>"
#define CHART_BUYITEM       "buy <string'item'> <number>"
#define CHART_SELLITEM      "sell <string'item'> <number>"
#define CHART_ASSIGN_ITEM   "assign <string'item'> <number'cabinet number'>"
#define CHART_UNASSIGN_ITEM "unassign <string'item'> <number'cabinet number'>"
#define LOG_BLANK  ""
#define LOG_NUMBER "<number>"
#define LOG_MGR    "{personnel|accounts|chart}"
#define LOG_CHART  "chart"
#define LIST_BLANK  ""
#define LIST_CHOICE "{employees|applicants|baddies}"
#define SET_EMPS "maximum <number> [employees]"
#define SET_PAY  "pay <number'amount'> <string'type'>"
#define VOTE_APPLICANT "<word'applicant'> {y|n|a}"
#define VOTE_POLICY    "policy <word'name'> {y|n}"
#define VIEW_EMP "<string'employee'>"
#define VIEW_APP "application [by] <string'applicant'>"
#define POLICY_SUGGEST "suggest {manager|shop} <word'policy'>"
#define POLICY_REMOVE  "remove <word'policy'>"
#define LIST_CABINET      "cabinet <number'cabinet'>"
#define LIST_ITEM         "<string'item'>"
#define LIST_ITEM_CABINET "<string'item'> in cabinet <number'cabinet'>"