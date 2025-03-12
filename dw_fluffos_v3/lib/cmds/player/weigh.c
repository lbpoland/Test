#define MAX_OBJECTS_AT_ONCE   5
string weight_string(int number);
int cmd(object *things, int brief);
string weight_string(int number) {
   number = (number + 4) / 9;
   switch (number) {
      case 0:
         return "uh oh";
      case 1:
         return "half a pound";
      case 2:
         return "a pound";
      case 3:
         return "a pound and a half";
      case 4 .. 14 :
         return query_num((number + 1) / 2) + " pounds";
      case 15 .. 24:
         return "ten pounds";
      case 25 .. 34:
         return "fifteen pounds";
      case 35 .. 149:
         return query_num(((number + 10) / 20) * 10) + " pounds";
      case 150 .. 249:
         return "a hundred pounds";
      case 250 .. 349:
         return "a hundred and fifty pounds";
      case 350 .. 1499:
         return query_num(((number + 100) / 200) * 100) + " pounds";
      case 1500 .. 2499:
         return "a thousand pounds";
      case 2500 .. 2499:
         return "fifteen hundred pounds";
      case 3500 .. 14999:
         return query_num(((number + 1000) / 2000) * 1000) + " pounds";
      case 15000 .. 24999:
         return "ten thousand pounds";
      case 25000 .. 34999:
         return "fifteen thousand pounds";
      default:
         return query_num(((number + 10000) / 20000) * 10000) + " pounds";
   }
}
int cmd(object *things, int brief) {
   int     accuracy;
   int     weight;
   int     total = 0;
   string  results;
   object  thing;
   object *worn;
   object *wearing;
   if (sizeof(things) > MAX_OBJECTS_AT_ONCE)
   {
      return notify_fail("You cannot weigh that many things at once.\n");
   }
   accuracy = 9 + 89 / (1 + this_player()->query_dex());
   results = "";
   wearing = this_player()->query_wearing();
   worn = filter(things, (: member_array($1, $(wearing)) > -1 :));
   things -= worn;
   if (brief)  {
      foreach (thing in things)
         total += thing->query_complete_weight();
   }
   else foreach (thing in things)  {
      results += "You heft " + thing->the_short() +
                 " and guess that " +
        (thing->group_object() ? "they weigh " :
         thing->query_pronoun() + " weighs ");
      weight = thing->query_complete_weight();
      total += weight;
      if (4 * weight > accuracy)  {
         weight = (4 * weight + accuracy) / (2 * accuracy);
         results += "about " + weight_string(weight * accuracy) + ".\n";
      }
      else  {
         results += "less than " + weight_string(accuracy)+ ".\n";
      }
   }
   if (sizeof(worn))  {
      write("You are wearing " + query_multiple_short(worn, "the") +
             ".\n");
   }
   if (sizeof(things))  {
      if (!brief)  {
         write(results);
      }
      if (sizeof(things) > 1  ||  brief)  {
         if (4 * total > accuracy)  {
             total = (4 * total + accuracy) / (2 * accuracy);
             printf("The total weight is about " +
                    weight_string(total * accuracy) + ".\n");
         }
         else  {
             printf("The total weight is less than " +
                    weight_string(accuracy) + ".\n");
         }
      }
      tell_room(environment(this_player()),
                this_player()->one_short() + " hefts " +
                query_multiple_short(things) + (sizeof(things) > 1 ?
                " one at a time to see how much they weigh" :
                " to see how much it weighs" ) + ".\n",
                ({ this_player() }));
   }
   return 1;
}
mixed *query_patterns()
{
   return ({ "<indirect:object:me'item(s)'>", (: cmd($1, 0) :),
             "<indirect:object:me'item(s)'> brief", (: cmd($1, 1) :) });
}