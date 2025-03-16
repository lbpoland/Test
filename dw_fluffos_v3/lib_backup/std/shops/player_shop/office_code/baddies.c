private void add_baddie(string word, string reason, string banner)
{
   object ob;
   word = lower_case(word);
   if (query_baddie(word))
   {
      if (_baddies[word][BAD_TIME] == time() ||
         reason == _baddies[word][BAD_REASON]) return;
      remove_baddie( word );
   }
   if (!sizeof(_baddies)) _baddies = ([word:BAD_MAP]);
   else _baddies += ([word:BAD_MAP]);
   _baddies[word][BAD_REASON] = reason;
   _baddies[word][BAD_BANNER] = banner;
   _baddies[word][BAD_TIME] = time();
   save_me();
   shop_log(GENERAL, banner, "banned "+ cap_name(word)+
      " for "+ reason, PAID);
   employee_log(word, sprintf("Banned by %s for %s.", cap_name(banner),
      reason));
   fire_them(_proprietor, word, reason);
   remove_applicant(word);
   if (!(ob = find_player(word))) return;
   if (environment(ob) == find_object(_shop_front))
   {
      tell_room(_shop_front, ob->query_short()+ " drifts out of the door, "
        "seemingly against "+ ob->query_possessive()+ " will.\n", ({ob}));
      tell_object(ob , "You feel yourself pushed out of the shop "
        "by a mysterious force.\n");
      tell_room(_shop_front->query_outside(), ob->query_short()+
        " drifts through the door of "+ _shop_name +
        ", seemingly against "+ ob->query_possessive()+ " will.\n", ({ob}));
      ob->move(_shop_front->query_outside());
   }
}
int do_ban(mixed *args)
{
   if (!test_player(lower_case(args[0])))
   {
      tell_object(this_player(), args[0]+ " is not a player.\n");
      return 1;
   }
   if (_employees[args[0]][EMP_POINTS] & MANAGER &&
      !this_player()->query_creator())
   {
      tell_object(this_player(), "You cannot ban "+ cap_name(args[0])+
         ".\n");
      return 1;
   }
   add_baddie(args[0], args[1], this_player()->query_name());
   tell_object(this_player(), "You ban "+ cap_name(args[0])+
     " for "+ args[1]+ ".\n");
   return 1;
}
int do_unban(string person)
{
   if (!query_baddie(person))
   {
      tell_object(this_player(), person+ " is not currently banned.\n");
      return 1;
   }
   remove_baddie(person);
   shop_log(GENERAL, this_player()->query_name(),
     "removed the ban on "+ cap_name(person), PAID);
   tell_object(this_player(), "You remove the ban on "+
     cap_name(person)+ ".\n" );
   return 1;
}
private void remove_baddie(string word)
{
   if (!query_baddie(word)) return;
   map_delete(_baddies, word);
   save_me();
}