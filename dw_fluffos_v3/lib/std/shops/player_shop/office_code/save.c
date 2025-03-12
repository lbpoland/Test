private void do_save()
{
#ifdef DEBUG
   tell_creator(CREATOR,"Saving shop data to %s/.\n", _savedir);
#endif
   unguarded((: save_object, _savedir+ "shop_data" :));
}
private void do_save_applicants()
{
   if (_very_short == UNSET_STR) return;
#ifdef DEBUG
   tell_creator(CREATOR,"Saving applications data to %s.\n",
     _savedir+ "applications");
#endif
   unguarded((: write_file, _savedir+ "applications",
     save_variable(_applicants), 1 :));
   clear_applicants();
}
private void do_save_emps()
{
#ifdef DEBUG
   tell_creator(CREATOR,"Saving employee data to %s.\n",
     _savedir+ "employees");
#endif
   unguarded((: write_file, _savedir+ "employees",
     save_variable(_employees), 1 :));
}
private void do_save_hist()
{
   if (_very_short == UNSET_STR) return;
#ifdef DEBUG
   tell_creator(CREATOR,"Saving history data to %s.\n",
     _savedir+ "history");
#endif
   unguarded((: write_file, _savedir+ "history",
     save_variable(_history), 1 :));
   clear_history();
}
private void do_save_new_policies()
{
   if (_very_short == UNSET_STR) return;
#ifdef DEBUG
   tell_creator(CREATOR,"Saving new policies data to %s.\n",
     _savedir+ "new_policies");
#endif
   unguarded((: write_file, _savedir+ "new_policies",
     save_variable(_new_policies), 1 :));
   _call_newpols_clear = call_out((: _new_policies= 0 :), CLEAR_DELAY);
}
private void do_save_policies()
{
   if (_very_short == UNSET_STR) return;
#ifdef DEBUG
   tell_creator(CREATOR,"Saving policies data to %s.\n",
     _savedir+ "policies");
#endif
   unguarded((: write_file, _savedir+ "policies",
      save_variable(_policies), 1 :));
   clear_policies();
}
private void save_list()
{
   if (_very_short == UNSET_STR) return;
#ifdef DEBUG
   tell_creator(CREATOR,"Saving chart list data to %s.\n",
     _savedir+ "list");
#endif
   unguarded((: write_file, _savedir+ "list",
     save_variable(_list), 1 :));
}
void save_register(mixed *money)
{
   _register = money;
   save_me();
}
private void save_times()
{
   if (_very_short == UNSET_STR) return;
#ifdef DEBUG
   tell_creator(CREATOR,"Saving times data to %s.\n",
     _savedir+ "times");
#endif
   unguarded((: write_file, _savedir+ "times",
     save_variable(_times), 1 :));
}