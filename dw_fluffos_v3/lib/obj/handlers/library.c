#include <quest_handler.h>
#include <player_handler.h>
#define XP 10000
#define XP_QUESTS ({"womble's brooch", "balance quest", "easy post quest", \
                    "hard post quest", "apprentice baker" })
#define RESTORE_PATH  "save/library/"
#define MAX_CACHE_SIZE 100
#define CACHE_TIMEOUT 900
inherit "/std/object";
int *times;
string player_name, *quests, text_file;
mapping player_quest_info;
nosave mapping qps;
nosave int requests, cache_hits;
class qinfo {
  int cached;
  string player_name;
  string *quests;
  int *times;
  string text_file;
  mapping player_quest_info;
}
nosave mapping player_cache = ([ ]);
int new_top_quest();
int query_quest_time(string, string);
private void init_data(string pl_name) {
  player_name = pl_name;
  quests = ({ });
  times = ({ });
  text_file = "";
  player_quest_info = ([ ]);
}
void clean_cache() {
  string name;
  foreach(name in keys(player_cache))
    if(player_cache[name]->cached < time() - CACHE_TIMEOUT)
      map_delete(player_cache, name);
}
private int get_data_file(string name) {
  int success;
  class qinfo tmp;
  requests++;
  if(player_cache[name]) {
    player_cache[name]->cached = time();
    cache_hits++;
    return 1;
  }
  success = unguarded((: restore_object, RESTORE_PATH+name[0..0]+"/"+name :));
  if(!success)
    init_data(name);
  tmp = new(class qinfo,
            cached : time(),
            player_name : player_name,
            quests : quests,
            times : times,
            text_file : text_file,
            player_quest_info : player_quest_info);
  player_cache[name] = tmp;
  if((sizeof(player_cache) > MAX_CACHE_SIZE) &&
     (find_call_out("clean_cache") == -1))
    call_out("clean_cache", 60);
  return success;
}
private void save_data_file(string name) {
  if(!player_cache[name])
    return;
  player_name = player_cache[name]->player_name;
  quests = player_cache[name]->quests;
  times = player_cache[name]->times;
  text_file = player_cache[name]->text_file;
  player_quest_info = player_cache[name]->player_quest_info;
  unguarded((: save_object, RESTORE_PATH+name[0..0]+"/"+name :));
  return ;
}
string query_title( string name ) {
  string quest;
  get_data_file( name );
  if(!player_cache[name]->quests || !sizeof(player_cache[name]->quests)) {
    return 0;
  }
  quest = player_cache[name]->
    quests[random(sizeof(player_cache[name]->quests))];
  return (string)QUEST_HANDLER->query_quest_title(quest);
}
string *query_quests(string name) {
  get_data_file(name);
  if(!player_cache[name]->quests ) {
    return ({ });
  }
  return player_cache[name]->quests + ({ });
}
string get_most_recent_quest(string name) {
  int loop, highest;
  string quest_name;
  string *quests;
  int *times;
  if(!get_data_file(name))
    return "Sorry";
  quests = player_cache[name]->quests;
  times = player_cache[name]->times;
  if(sizeof(quests) == 0)
    return "None";
  for(highest = loop = 0; loop < sizeof(quests); loop++) {
    if(times[loop] > highest) {
      highest = times[loop];
      quest_name = quests[loop];
    }
  }
  return quest_name;
}
int get_most_recent_time(string name) {
  int loop, hightime;
  string *quests;
  int *times;
  if(!get_data_file(name)) {
    return -1;
  }
  quests = player_cache[name]->quests;
  times = player_cache[name]->times;
  if(sizeof(quests) == 0) {
    return 0;
  }
  for(hightime = loop = 0; loop < sizeof(quests); loop++) {
    if(times[loop] > hightime) {
      hightime = times[loop];
    }
  }
  return hightime;
}
int set_quest(string pl_name, string qu_name, int no_xp) {
  int qu_level;
  object ob;
  object card;
  int i;
  if(!find_player(pl_name) || find_player(pl_name)->query_property("guest"))
    return 0;
  i = QUEST_HANDLER->query_quest_status(qu_name);
  ob = find_player (pl_name);
  if (i == 0 && ob->query_playtester()) {
    tell_object (ob, "%^BOLD%^If this quest weren't inactive, you'd be "
      "showered in riches right about now!\n%^RESET%^");
  }
  if(i < 1) {
   user_event( "inform", pl_name +" completes "+ qu_name + " (inactive)", "quest");
    return 0;
  }
  if (ob && ob->advancement_restriction()) {
    log_file ("/log/secure/playtesters/protection_log", "%s: %s "
      "completed quest %s while advancement restricted active.\n", ctime(time()),
      pl_name, qu_name);
    return 0;
  }
  if(qps && qps[pl_name])
    map_delete(qps, pl_name);
  get_data_file(pl_name);
  if ( member_array( qu_name, player_cache[pl_name]->quests ) != -1 )
    return 0;
  player_cache[pl_name]->quests += ({ qu_name });
  player_cache[pl_name]->times += ({ time() });
  qu_level = (int)QUEST_HANDLER->query_quest_level(qu_name);
  if ( qu_level < 1 )
    return 0;
  QUEST_HANDLER->quest_completed( pl_name, qu_name, previous_object() );
  save_data_file( pl_name );
  if ( !ob ) {
    return 0;
  }
  if(member_array(qu_name, XP_QUESTS) != -1) {
    ob->adjust_xp(XP*qu_level, 0);
    call_out("save_them", 1, ob);
  }
  ob->set_title( "quest",
                 (string)QUEST_HANDLER->query_quest_title( qu_name ) );
  card = clone_object ("/d/underworld/creator_cards/creator_card");
  card->move (ob, "$N appear$s in your inventory with a flash.");
  return 1;
}
int unset_quest(string pl_name, string qu_name) {
  int qu_level;
  get_data_file(pl_name);
  if ( member_array( qu_name, player_cache[pl_name]->quests ) == -1 )
    return 0;
  qu_level = (int)QUEST_HANDLER->query_quest_level(qu_name);
  if ( qu_level < 1 )
    return 0;
  player_cache[pl_name]->quests -= ({ qu_name });
  player_cache[pl_name]->times -= ({ time() });
  save_data_file( pl_name );
  return 1;
}
void save_them( object thing ) {
  if ( thing )
    thing->save_me();
}
void set_player_quest_info( string pl_name, string qu_info, mixed *details ) {
  get_data_file( pl_name );
  if(!player_cache[pl_name]->player_quest_info )
    player_cache[pl_name]->player_quest_info = ([ ]);
  player_cache[pl_name]->player_quest_info[qu_info] = details;
  save_data_file(pl_name);
}
mapping query_all_player_quest_info( string pl_name ) {
  if(!get_data_file( pl_name ))
    return 0;
  if ( !player_cache[pl_name]->player_quest_info )
    return 0;
  return copy(player_cache[pl_name]->player_quest_info);
}
mixed *query_player_quest_info( string pl_name, string qu_info ) {
  if(!get_data_file( pl_name))
    return 0;
  if(!player_cache[pl_name]->player_quest_info)
    return 0;
  player_cache[pl_name]->player_quest_info =
    player_cache[pl_name]->player_quest_info + ([ ]);
  return player_cache[pl_name]->player_quest_info[qu_info];
}
int query_quest_time(string name, string qu_name) {
  int time;
  if(!get_data_file(name)) {
    return 0;
  }
  time = member_array(qu_name, player_cache[name]->quests);
  if(time < 0) {
    return 0;
  }
  return player_cache[name]->times[time];
}
string query_story(string name) {
  string story, *quests;
  int loop;
  if(!get_data_file(name)) {
    return "You can find nothing in the library on " + name + "\n";
  }
  story = "";
  if(player_cache[name]->text_file != "") {
    return unguarded((: read_file, text_file :));
  }
  quests = player_cache[name]->quests;
  if(!sizeof(quests)) {
    return "That person has lead a most unadventureous life";
  }
  for(loop = 0; loop < sizeof(quests); loop++) {
    story += capitalize(QUEST_HANDLER->query_quest_story(quests[loop])) +".\n";
  }
  return story;
}
int query_quest_done(string player, string quest) {
  if(!get_data_file(player))
    return 0;
  return (member_array(quest, player_cache[player]->quests) != -1);
}
int flush_cache (string name) {
  qps[name] = 0;
}
int query_quest_points( string name ) {
   int points;
   string word;
   string *quests;
   if(!qps)
     qps = ([ ]);
   if(qps[name])
     return qps[name]-1;
   get_data_file( name );
   quests = player_cache[name]->quests;
   if ( !quests || !sizeof( quests ) )
      points = 0;
   else {
     foreach( word in quests ) {
       points += (int)QUEST_HANDLER->query_quest_level( word );
     }
   }
   qps[name] = points+1;
   return points;
}
int restart(mixed name) {
  class qinfo tmp;
  if(objectp(name))
    name = name->query_name();
  if(!PLAYER_HANDLER->test_user(name))
    return 0;
  init_data(name);
  tmp = new(class qinfo,
            cached : time(),
            player_name : player_name,
            quests : quests,
            times : times,
            text_file : text_file,
            player_quest_info : player_quest_info);
  player_cache[name] = tmp;
  save_data_file(name);
  return 1;
}
mixed *stats() {
  int percentage;
  if(requests)
    percentage = (cache_hits * 100) / requests;
  return ({
    ({ "cache size", sizeof(player_cache) }),
      ({ "requests", requests }),
      ({ "cache hits", cache_hits }),
      ({ "cache misses", requests - cache_hits }),
      ({ "percentage hits", percentage }),
      });
}