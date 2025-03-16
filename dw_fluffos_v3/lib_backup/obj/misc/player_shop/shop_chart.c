#include <player_shop.h>
#include <money.h>
inherit "/std/object";
private nosave string _office;
void setup()
{
   set_name("chart");
   set_short("items chart");
   add_adjective("items");
   reset_get();
}
string long(string word, int dark)
{
   mapping list = _office->query_list_mapping();
   string chart, *items = sort_array(keys(list),1);
   if (!m_sizeof(list))
   {
      return "There are no items on the list.\n";
   }
   chart = sprintf("\n%-2s  %-25s  %-3s  %-5s  %-4s  %-4s  %-3s  %-4s  %-8s\n",
      "no", "items", "max", "stock", "avst", "avsl", "buy", "sell", "cabinets");
   chart += sprintf("%-2s  %-25s  %-3s  %-5s  %-4s  %-4s  %-3s  %-4s  %-8s\n",
      "--", "-----", "---", "-----", "----", "----", "---", "----", "--------");
   for (int i = 0; i < sizeof( items ); i++)
   {
      reset_eval_cost();
      chart += sprintf("%2d  %-25s  %3d  %5d  %4d  %4d  %3d  %4d  %8s\n",
         i + 1, items[i], list[items[i]][CHART_MAX],
         _office->query_stock(items[i]), list[items[i]][CHART_AVE],
         list[items[i]][CHART_AVESALE], list[items[i]][CHART_BUY],
         list[items[i]][CHART_SELL],
         implode(list[items[i]][CHART_CAB], (: $1+","+$2 :), "")[1..]);
   }
   return sprintf("%s%s", ::long(word,dark), chart);
}
void set_office(string office)
{
   _office = office;
   set_long("This chart lists the items of interest to the shop.  All "
      "prices are in "+ pluralize(MONEY_HAND->smallest_in(_office->
      query_place()))+ ".\n");
}