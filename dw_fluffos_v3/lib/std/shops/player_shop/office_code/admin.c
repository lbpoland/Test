private void add_board_message(string subject, string post)
{
   string *employees;
   if (_board)
   {
#ifdef DEBUG
      tell_creator(CREATOR, "Posting message %s to board %s.\n", subject,
        _channel);
#endif
      BOARD_HAND->add_message(_channel, _proprietor,
        subject, post + "--\n"+ _proprietor+ " (proprietor)");
   }
   else
   {
      employees = _retired;
      foreach(string employee in m_indices(_employees))
         if (!(_employees[employee][EMP_POINTS] & NPC))
            employees += ({ employee });
      if (!sizeof(employees))
      {
#ifdef DEBUG
         tell_creator(CREATOR, "No employees to send mail to.\n");
#endif
         return;
      }
      employees += ({CREATOR});
#ifdef DEBUG
      tell_creator(CREATOR, "Sending mail %s to all employees.\n", subject);
#endif
      AUTO_MAILER->auto_mail(implode(employees, ","), _proprietor,
           subject+ " ("+ _very_short+ ")", "", post);
   }
}
private void adjust_bonus(string emp, int amount)
{
   string sign = "";
   _accounts["bonus"] += amount;
   if (amount < 0)
   {
      sign = "-";
      amount = -amount;
   }
   shop_log( ACCOUNTS, emp, sprintf( "adjusted the bonus account by %s%s",
     sign, MONEY_HAND->money_value_string( amount, _place ) ), UNPAID );
   save_me();
}
private void adjust_profit(string emp, int amount)
{
   string sign = "";
   _accounts["profit"] += amount;
   if (amount < 0)
   {
      sign = "-";
      amount = -amount;
   }
   shop_log(ACCOUNTS, emp, sprintf("adjusted the profit account by %s%s",
     sign, MONEY_HAND->money_value_string(amount, _place)), UNPAID);
   save_me();
}
void adjust_takings(int amt)
{
   if (previous_object() && previous_object() != find_object(_counter))
   {
      LOG_ERROR("office.c", "adjust_bought("+amt+")");
      return;
   }
   _net_takings += amt;
   save_me();
}
void calc_bonus()
{
   int bonus_val, bonus_divisor = 0;
   foreach (string str in m_indices(_employees))
   {
      if (_employees[str][EMP_NOBONUS]) continue;
      if (_employees[str][EMP_POINTS] & MANAGER)
      {
         bonus_divisor += 4;
      }
      else if (_employees[str][EMP_POINTS] & SUPERVISOR || _eom == str)
      {
         bonus_divisor += 3;
      }
      else
      {
         bonus_divisor += 2;
      }
   }
   if (!bonus_divisor) bonus_val = _accounts["bonus"];
   else bonus_val = ( _accounts["bonus"] * 2 ) / bonus_divisor;
   tell_object(this_player(), "Based on the bonus fund of "+
     MONEY_HAND->money_value_string(_accounts["bonus"], _place)+
     ", the following bonuses are anticipated:\n"
     "\n     Managers    - "+
     MONEY_HAND->money_value_string(bonus_val * 2, _place)+
     "\n     Supervisors - "+
     MONEY_HAND->money_value_string(to_int(bonus_val * 1.5), _place)+
     "\n     Employees   - "+
     MONEY_HAND->money_value_string(bonus_val, _place)+ "\n");
}
int calc_pay()
{
   int amount = 0;
   foreach(string word in m_indices(_employees))
      amount += _employees[word][EMP_PAY];
   return amount;
}
private string cap_name(string name)
{
   if (!name) return 0;
   if (test_player(name))
      return PLAYER_HANDLER->query_cap_name(name);
   else return capitalize(name);
}
int check_manager( string action )
{
   object tp = this_player();
   string tp_name = tp->query_name();
   if (tp->query_creator() || (_employees[tp_name][EMP_POINTS] & MANAGER) ||
     (member_array(tp_name, _retired) != -1)) return 1;
   return notify_fail( "You are not a manager here!\n" );
}
string directions_to( string place )
{
   if (place == _counter) return copy(_counter_dir);
   if (place == _storeroom) return copy(_store_dir);
   if (place == _shop_front) return copy(_shop_dir);
   return "here";
}
int do_set(mixed *args, string pattern)
{
   int value, best;
   object money;
   switch(pattern)
   {
      case SET_EMPS :
         if (args[0] < MIN_EMP || args[0] > MAX_EMP)
         {
            tell_object(this_player(), "Must be between "+ MIN_EMP+
              " and "+ MAX_EMP+ ".\n");
            return 1;
         }
         shop_log(PERSONNEL, this_player()->query_name(),
           "set maximum employees to "+ args[0], PAID);
         _max_emp = args[0];
         break;
      case SET_PAY :
         money = clone_object( MONEY_OBJECT );
         money->set_money_array(MONEY_HAND->query_values_in(_place));
         if ((best = money->find_best_fit(args[1])) == -1)
         {
            tell_object(this_player(),
              "That currency is not used by the shop.\n");
            return 1;
         }
         value = args[0] * (money->query_money_array())[best + 1];
         money->dest_me();
         if (value < 1)
         {
            tell_object(this_player(),
              "You must pay your employees something.\n");
            return 1;
         }
         shop_log(PERSONNEL, this_player()->query_name(), "set pay to "+
           MONEY_HAND->money_value_string(value, _place), PAID);
         _pay_val = value;
         add_board_message("Pay", sprintf("The base pay rate has today "
           "been set to:\n\n   Managers: %s\n   Supervisors: %s\n   "
           "Employees: %s\n", MONEY_HAND->money_value_string(value * 2, _place),
           MONEY_HAND->money_value_string(to_int(value * 1.5), _place),
           MONEY_HAND->money_value_string(value, _place)));
         break;
   }
   tell_object(this_player(), "Ok.\n");
   save_me();
   return 1;
}
int do_transfer(mixed *args)
{
   int value, best;
   object money;
   string tp;
   if (args[2] == args[3] || !args[0])
   {
      tell_object(this_player(), "The point being?\n");
      return 1;
   }
   tp = this_player()->query_name();
   money = clone_object(MONEY_OBJECT);
   money->set_money_array(MONEY_HAND->query_values_in(_place));
   if ((best = money->find_best_fit(args[1])) == -1)
   {
      tell_object(this_player(), "That currency is not used by "
        "the shop.\n");
      return 1;
   }
   value = args[0] * (money->query_money_array())[best + 1];
   money->dest_me();
   switch(args[2]) {
   case "register" :
      if (_counter->query_register() < value)
      {
         tell_object(this_player(), "There isn't that much available.\n");
         return 1;
      }
      _counter->adjust_register(tp, value);
      if (args[3] == "profit") adjust_profit(tp, value);
      else adjust_bonus( tp, value );
      break;
   case "bonus" :
      if (_accounts["bonus"] < value)
      {
         tell_object(this_player(), "There isn't that much available.\n");
         return 1;
      }
      adjust_bonus(tp, -value);
      if (args[3] == "profit") adjust_profit(tp, value);
      else
      {
         money = MONEY_HAND->make_new_amount(value, _place);
         _counter->add_money_ob(money);
         shop_log(ACCOUNTS, tp, "adjusted the register by "+
           MONEY_HAND->money_value_string(value, _place), UNPAID);
      }
      break;
   case "profit" :
      if (_accounts["profit"] < value)
      {
         tell_object(this_player(), "There isn't that much available.\n");
         return 1;
      }
      adjust_profit(tp, -value);
      if (args[3] == "bonus") adjust_bonus( tp, value );
      else
      {
         money = MONEY_HAND->make_new_amount(value, _place);
         _counter->add_money_ob(money);
         shop_log( ACCOUNTS, tp, "adjusted the register by "+
           MONEY_HAND->money_value_string(value, _place), UNPAID);
      }
      break;
   }
   shop_log (ACCOUNTS, tp, "transferred "+ args[0]+ " "+ args[1]+ " from "+
      args[2]+ " to "+ args[3], PAID);
   tell_object(this_player(), "Ok.\n");
   return 1;
}
private void load_applicants()
{
   if (remove_call_out(_call_apps) != -1 ||
      remove_call_out(_call_apps_clear) != -1) return;
   if (!_applicants)
      if (file_size(_savedir+ "applications") > 0)
         _applicants = restore_variable(unguarded((: read_file,
            _savedir+ "applications" :)));
      else _applicants = ([]);
}
private void load_history()
{
   if (remove_call_out(_call_hist) != -1 ||
      remove_call_out(_call_hist_clear) != -1) return;
   if (!_history)
      if (file_size(_savedir+ "history") > 0)
         _history = restore_variable(unguarded((: read_file,
            _savedir+ "history" :)));
      else _history = ([]);
}
private void load_new_policies()
{
   if (remove_call_out(_call_newpols) != -1 ||
      remove_call_out(_call_newpols_clear) != -1) return;
   if (!_new_policies)
      if ( file_size(_savedir+ "new_policies") > 0 )
         _new_policies = restore_variable(unguarded((: read_file,
            _savedir+ "new_policies" :)));
      else _new_policies = ([]);
}
private void load_policies()
{
   if (remove_call_out(_call_pols) != -1 ||
      remove_call_out(_call_pols_clear) != -1) return;
   if (!_policies)
      if ( file_size( _savedir+ "policies" ) > 0 )
         _policies = restore_variable( unguarded( (: read_file,
            _savedir+ "policies" :) ) );
      else _policies = ([]);
}
string * query_eom() { return ({_last_month,_eom,}); }
private void remove_employee(string employee)
{
   employee = lower_case(employee);
   if (_employees[employee])
   {
      map_delete(_employees, employee);
      save_emps();
   }
   remove_applicant(employee);
   remove_retired(employee);
   remove_call_out(_call_hire_list);
   _call_hire_list = call_out((: check_hire_list() :), 5);
}
private void remove_retired(string retired)
{
   retired = lower_case(retired);
   if (member_array(retired, _retired) == -1) return;
   _retired -= ({retired});
   save_me();
}
private void reset_employee(string word, int bit)
{
   if (!_employees[word]) return;
   if ((bit < EMPLOYEE) || (bit > CLOCKED_IN))
   {
#ifdef DEBUG
      tell_creator(CREATOR, "Trying to reset an employee bit < %d || > %d\n",
         EMPLOYEE, CLOCKED_IN );
#endif
      return;
   }
   _employees[word][EMP_POINTS] -= _employees[word][EMP_POINTS] & bit;
   if (bit != CLOCKED_IN) save_emps();
}
mixed *restore_register() { return copy(_register + ({})); }
void set_employee(string word, int bit)
{
   if (!_employees[word]) return;
   _employees[word][EMP_POINTS] |= bit;
   if (bit != CLOCKED_IN) save_emps();
}
void summon_shopkeeper()
{
   object shopkeeper = find_object(_shopkeeper);
   if (shopkeeper && environment(shopkeeper)) return;
   if (num_employees_in()) return;
   _shopkeeper->start_shift();
}