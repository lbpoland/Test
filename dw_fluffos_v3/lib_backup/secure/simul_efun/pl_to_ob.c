object player_to_object(string str)
{
  string tmp;
  if (this_player())
    tmp = this_player()->expand_nickname(lower_case(str));
  if (tmp) str = tmp;
  return this_object()->find_player(lower_case(str));
}