#include <library.h>
string _quest_name;
void set_quest_name(string quest_name)
{
   _quest_name = quest_name;
}
void set_quest_param(mixed player, string key, mixed value)
{
   mixed info;
   if (!stringp(player))
      player = player->query_name();
   info = LIBRARY->query_player_quest_info(player, _quest_name);
   if (!mapp(info))
      info = ([ ]);
   info[key] = value;
   LIBRARY->set_player_quest_info(player, _quest_name, info);
}
mixed query_quest_param(mixed player, string key)
{
   mixed info;
   if (!stringp(player))
      player = player->query_name();
   info = LIBRARY->query_player_quest_info(player, _quest_name);
   if (!mapp(info))
      return 0;
   return info[key];
}
void clear_quest_info(mixed player)
{
   if (!stringp(player))
      player = player->query_name();
   LIBRARY->set_player_quest_info(player, _quest_name, 0);
}