private void add_chart_cabinet(string word, int number)
{
   if (!_list[word]) return;
   _list[word][CHART_CAB] += ({number});
   _list[word][CHART_CAB] = sort_array(_list[word][CHART_CAB], 1);
   save_list();
}
void confirm_cabinet(string confirm, int rent)
{
   if (previous_object() && previous_object() != this_object())
   {
      LOG_ERROR("office.c", "confirm_cabinet("+confirm+","+rent+")");
      return;
   }
   confirm = lower_case(confirm);
   if ( strlen(confirm) < 1 ||
     (confirm[0] != 'y' && confirm[0] != 'n'))
   {
       tell_object(this_player(), sprintf("Please enter 'yes' or 'no'.\n"
         "Are you sure you want to %s a cabinet? ", (rent)?"rent":"remove"));
       input_to("confirm_cabinet", 0, rent);
       return ;
   }
   if (confirm[0] == 'n')
   {
      tell_object(this_player(), "Ok.\n");
      return;
   }
   if (rent)
      if (_storeroom->add_cabinet())
      {
         _num_cabinets++;
         adjust_profit(this_player()->query_name(), -CABINET_COST);
         shop_log(ACCOUNTS, this_player()->query_name(),
           "rented cabinet for "+ MONEY_HAND->money_value_string(CABINET_COST,
           _place), PAID);
         save_me();
      }
   else
   {
      string cab_name;
      if ((cab_name = _storeroom->remove_cabinet()) != "")
      {
         _num_cabinets--;
         shop_log(ACCOUNTS, this_player()->query_name(),
           "removed cabinet", PAID);
         if (file_size(_savedir+ _cab_name + ".o") > 0)
         {
            _cab_name = cab_name;
            call_out((: rm_cab() :), 5);
         }
         save_me();
      }
   }
   tell_object(this_player(), "Cabinet "+ (rent)?"rent":"remov" + "ed.\n");
}
private int do_check()
{
   string result = "Current cabinet assignments are:\n";
   for (int x = 0; x < _num_cabinets; x++)
   {
      string *items = ({});
      result += sprintf("Cabinet %2d: ", x+1);
      foreach(string item in m_indices(_list))
         if (member_array(x+1, _list[item][CHART_CAB]) != -1)
            items += ({sprintf("%s (%d)", item, _list[item][CHART_MAX])});
      if (sizeof(items)) result += query_multiple_short( items );
      result += "\n";
   }
   result += "\n";
   tell_object(this_player(), "$P$Cabinet assignments$P$"+ result);
   return 1;
}
int do_remove()
{
   int stock;
   if (!((stock = _num_cabinets) > MIN_CABINETS))
   {
      tell_object(this_player(), "The shop already contains the "
        "minimum number of cabinets.\n");
      return 1;
   }
   if (sizeof(_storeroom->query_stock(stock)))
   {
      tell_object(this_player(), "Cabinet "+ stock+
        " still contains stock.\n");
      return 1;
   }
   if (query_cabinet_used(stock))
   {
      tell_object(this_player(), "Cabinet "+ stock+
        " is still assigned to hold stock.\n");
      return 1;
   }
   tell_object(this_player(), "Are you sure you wish to remove a cabinet? ");
   input_to("confirm_cabinet", 0, 0);
   return 1;
}
int do_rent()
{
   if (!(_num_cabinets < MAX_CABINETS))
   {
      tell_object(this_player(), "The shop already contains the "
        "maximum number of cabinets.\n");
      return 1;
   }
   if (CABINET_COST > _accounts["profit"])
   {
      tell_object(this_player(), "Cabinets currently cost "+
        MONEY_HAND->money_value_string(CABINET_COST, _place) +
        ".  There is not enough money in the profit account.\n");
      return 1;
   }
   tell_object(this_player(), "Are you sure you wish to rent a cabinet for "+
     MONEY_HAND->money_value_string( CABINET_COST, _place ) + " per month? ");
   input_to("confirm_cabinet", 0, 1);
   return 1;
}
int *query_cabinet(string item)
{
   return (!_list[item])?({}):copy(_list[item][CHART_CAB]);
}
int query_cabinet_used(int cabinet)
{
   foreach(string word in m_indices(_list))
      if ( member_array(cabinet, _list[word][CHART_CAB]) != -1)
         return TRUE;
   return FALSE;
}
private void remove_chart_cabinet(string word, int number)
{
   if (!_list[word]) return;
   _list[word][CHART_CAB] -= ({number});
   save_list();
}
private void rm_cab()
{
#ifdef DEBUG
   tell_creator(CREATOR, "Removing cabinet file %s.\n",
     _savedir+ _cab_name+ ".o");
#endif
   unguarded((: rm, _savedir+ _cab_name+ ".o" :));
   _cab_name = "";
}