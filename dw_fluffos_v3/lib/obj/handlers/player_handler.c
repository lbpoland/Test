inherit "/global/family";
inherit "/std/living/nationality";
#include <alias.h>
#include <player.h>
#include <login_handler.h>
#include <access.h>
#define MAX_CACHE_SIZE MAX_PLAYERS
#define CACHE_TIMEOUT 900
#define INACTIVE_LIMIT 1209600
#define ILLEGAL ({ "black", "blood", "cyber", "dark", "penis", "cock", "pussy",\
  "fuck", "shit", "death", "deth", "dragon", "fish", "hell", "mage", "pink", "lord",\
  "shadow", "evil", "killer", "slayer" })
private int gender;
private int creator;
private int time_on;
private int last_log_on;
private string last_on_from;
private int activity_counter;
private int start_time;
private string password;
private string deity;
private string guild_ob;
private string cap_name;
private mapping aliases;
private mapping map_prop;
private mapping new_skills;
private mapping player_info;
private mixed *guild_data;
private int _flags;
private string home_dir;
string player_ob;
class player_record {
  int cached;
  int touched;
  int deleting;
  int appealing;
  int gender;
  int creator;
  int active;
  int level;
  string cap_name;
  mapping map_prop;
  mapping player_info;
  string deity;
  string guild;
  mixed *guild_data;
  int age;
  int last;
  int flags;
  string last_on_from;
  int start_time;
  string family_name;
  string player_title;
  string password;
  mixed *project;
  mixed *plan;
  mixed *reference;
  mixed *signature;
  string home_dir;
  string nationality;
  string nationality_region;
  mixed nationality_data;
}
nosave mapping player_cache;
nosave string prev, prev_find, prev_name;
nosave int prev_count, prev_finds, delay;
int requests,
  cache_hits;
void create() {
  seteuid("Root");
  player_ob = "/global/player";
  player_cache = ([ ]);
}
object my_find_player(string player) {
  string *funs, stack = "";
  object *obs;
  int i;
  if(prev_name == player)
    return find_player(player);
  prev_name = player;
  if (base_name(previous_object()) == prev_find && delay > time() - 60 &&
      prev_name == player) {
    prev_finds++;
  } else {
    prev_finds = 1;
    delay = time();
    prev_find = base_name(previous_object());
  }
  if(!(prev_finds % 25)) {
    obs = call_stack(1);
    funs = call_stack(2);
    for(i=0; i<sizeof(obs); i++) {
      if(clonep(obs[i]))
        stack += base_name(obs[i]) + "#" + obs[i]->query_name();
      else
        stack += base_name(obs[i]);
      stack += "->" + funs[i] + "()\n";
    }
    log_file("GARBAGE", "%s %s checked %d players in %d seconds.\n%s",
             ctime(time())[4..18], prev_find, prev_finds, time() - delay,
             stack);
  }
  return find_player(player);
}
void clean_cache() {
  string name;
  foreach(name in keys(player_cache)) {
    if (player_cache[name]->cached < time() - CACHE_TIMEOUT) {
      map_delete(player_cache, name);
    }
  }
}
void remove_cache_entry(string name) {
  map_delete(player_cache, name);
}
private int validate_name(string name) {
  if (!stringp(name) || !name || name == "logon" || name[0] == '.' ||
      (sscanf(name, "%*s %*s") == 2) || strlen(name) < 2) {
    return 0;
  }
  if (sizeof(explode(name, "..")) > 1) {
    return 0;
  }
  return 1;
}
string query_player_file_name(string name) {
#ifdef USE_RAMDISK
  if(PLAYER_RAM_DIR) {
    if(file_size(PLAYER_RAM_DIR + name[0..0] + "/" + name + ".o.gz") == -1) {
      if(file_size(PLAYER_SAVE_DIR + name[0..0] + "/" + name + ".o.gz") > -1) {
        unguarded((: cp,
                   PLAYER_SAVE_DIR + name[0..0] + "/" + name + ".o.gz",
                   PLAYER_RAM_DIR + name[0..0] + "/" + name + ".o.gz" :));
      } else if((file_size(PLAYER_SAVE_DIR+name[0..0]+"/"+name+".o") >-1)) {
        unguarded((: cp,
                   PLAYER_SAVE_DIR + name[0..0] + "/" + name + ".o",
                   PLAYER_RAM_DIR + name[0..0] + "/" + name + ".o" :));
        unguarded((: compress_file,
                   PLAYER_RAM_DIR + name[0..0] + "/" + name + ".o" :));
      }
    }
    return PLAYER_RAM_DIR + name[0..0] + "/" + name;
  }
#endif
  return PLAYER_SAVE_DIR + name[0..0] + "/" + name;
}
string query_player_ram_file_name(string name) {
  return PLAYER_RAM_DIR + name[0..0] + "/" + name;
}
string query_player_disk_file_name(string name) {
  return PLAYER_SAVE_DIR + name[0..0] + "/" + name;
}
string query_delete_player_file_name(string name) {
   return PLAYER_SAVE_DIR + DELETE_DIR + "/" + name;
}
string query_appeal_player_file_name(string name) {
   return PLAYER_SAVE_DIR + APPEAL_DIR + "/" + name;
}
int load_player(string name) {
  class player_record tmp;
  mixed *file;
  int diff, deleting, appealing;
  string tstr, fname;
  object loaded_guild_ob;
  if (!validate_name(name)) {
    return 0;
  }
  requests++;
  if (player_cache[name]) {
    if (10 * (time() - player_cache[name]->cached) <
        (time() - player_cache[name]->touched)) {
      cache_hits++;
      return 1;
    }
  }
  if(file = unguarded((: get_dir, query_player_ram_file_name(name) + ".o.gz",
                       -1 :)))
    fname = query_player_ram_file_name(name);
  if (!file || !sizeof(file) || file[0][1] < 0) {
    file = unguarded((: get_dir, query_player_disk_file_name(name) +
                      ".o.gz", -1 :));
    fname = query_player_disk_file_name(name);
  }
  if (!file || !sizeof(file) || file[0][1] < 0) {
    file = unguarded((: get_dir, query_player_disk_file_name(name) +
                      ".o", -1 :));
    fname = query_player_disk_file_name(name);
  }
  if (!file || !sizeof(file) || file[0][1] < 0) {
    file = unguarded((: get_dir, query_delete_player_file_name(name) + ".o.gz",
                      -1 :));
    fname = query_delete_player_file_name(name);
  }
  if (!file || !sizeof(file) || file[0][1] < 0) {
    file = unguarded((: get_dir, query_delete_player_file_name(name) + ".o",
                      -1 :));
    fname = query_delete_player_file_name(name);
  }
  if (!file || !sizeof(file) || file[0][1] < 0) {
    file = unguarded((: get_dir, query_appeal_player_file_name(name) + ".o.gz",
                      -1 :));
    fname = query_appeal_player_file_name(name);
  }
  if (!file || !sizeof(file) || file[0][1] < 0) {
    file = unguarded((: get_dir, query_appeal_player_file_name(name) + ".o",
                      -1 :));
    fname = query_appeal_player_file_name(name);
  }
  if(!file || !sizeof(file) || file[0][1] < 0)
    return 0;
  if(player_cache[name] && player_cache[name]->touched == file[0][2]) {
    player_cache[name]->cached = time();
    cache_hits++;
    return 1;
  }
  gender = 0;
  creator = 0;
  time_on = 0;
  last_log_on = 0;
  last_on_from = 0;
  activity_counter = 0;
  start_time = 0;
  password = 0;
  deity = 0;
  guild_ob = 0;
  cap_name = 0;
  player_info = ([ ]);
  aliases = ([ ]);
  new_skills = ([ ]);
  map_prop = ([ ]);
  guild_data = 0;
  if (base_name(previous_object()) == prev && delay > time() - 60) {
    prev_count++;
  } else {
    prev_count = 1;
    delay = time();
    prev = base_name(previous_object());
  }
  if (!(prev_count % 25)) {
    tstr = prev;
    if (tstr == "/secure/login" && sizeof(previous_object(-1)) > 1) {
      tstr = base_name(previous_object(-1)[1]);
    }
    log_file("GARBAGE", "%s %s loaded %d player files in %d seconds.\n",
             ctime(time())[4..18], tstr, prev_count, time() - delay);
  }
#ifdef DEBUG
  string ob;
  if (base_name(previous_object()) != "/secure/login") {
    ob = base_name(previous_object());
  } else {
    ob = base_name(previous_object(-1)[1]);
  }
  log_file("CDEBUG", "%s: %O:%O\n", ob, call_stack(1), call_stack(2));
#endif
  if(!unguarded((: restore_object, fname, 1 :)))
    return 0;
  if(fname == query_appeal_player_file_name(name)) {
    appealing = file[0][2];
  } else if(fname == query_delete_player_file_name(name)) {
    deleting = file[0][2];
  }
  tmp = new (class player_record,
             cached: time(),
             touched: file[0][2],
             deleting: deleting,
             appealing: appealing,
             gender: gender,
             creator: creator,
             active: 0,
             level: 0,
             cap_name: cap_name,
             player_info: player_info,
             map_prop: map_prop,
             deity: deity,
             guild: guild_ob,
             guild_data: guild_data,
             flags: _flags,
             age: time_on,
             last: last_log_on,
             last_on_from: last_on_from,
             start_time: start_time,
             family_name: query_family_name(),
             player_title: query_player_title(),
             nationality: query_nationality(),
             nationality_region: query_nationality_region(),
             nationality_data: query_nationality_data(),
             password: password);
  if(aliases) {
    if (aliases[".project"])
      tmp->project = aliases[".project"][0..1023];
    if (aliases[".plan"])
      tmp->plan = aliases[".plan"][0..1023];
    if (aliases[".reference"])
      tmp->reference = aliases[".reference"][0..1023];
    if (aliases[".signature"])
      tmp->signature = aliases[".signature"][0..240];
  }
  diff = (time() - last_log_on) / (3600 * 24 * 7);
  diff *= 10;
  tmp->active = (activity_counter - diff) > -50 ? 1 : 0;
  if (guild_ob) {
    loaded_guild_ob = load_object( guild_ob );
    if ( loaded_guild_ob ) {
        tmp->level = (int) guild_ob->query_level(this_object());
    }
    else {
        tmp->level = 0;
    }
  }
  player_cache[name] = tmp;
  if ((sizeof(player_cache) > MAX_CACHE_SIZE) &&
      (find_call_out("clean_cache") == -1))
    call_out("clean_cache", 60);
  return 1;
}
string make_string(mixed *al, int max) {
  string str;
  int i;
  int lines;
  str = ALIAS_CMD->alias_string(al);
  sscanf(str, "%s $*$", str);
  str = replace(str, sprintf("%c", 7), "^G");
  str = replace(str, ({ "@@", "@ @ ", "\\;", "$escaped$", ";", "\n",
                          "$escaped$", ";" }));
  for (i = lines = 0; i < sizeof(str) && i < max*80 && lines < max; i++) {
    if (str[i] == '\n' || str[i] == ';') {
      lines++;
    }
  }
  return str[0..i - 1];
}
int test_user(string str) {
  if (player_cache[str])
    return 1;
  if (!validate_name(str))
    return 0;
  return file_size(query_player_disk_file_name(str) + ".o.gz") > 0 ||
    file_size(query_player_disk_file_name(str) + ".o") > 0 ||
    file_size(PLAYER_RAM_DIR + str[0..0] + "/" + str + ".o.gz") > 0 ||
    file_size(PLAYER_RAM_DIR + str[0..0] + "/" + str + ".o") > 0 ||
    file_size(query_delete_player_file_name(str) + ".o.gz") > 0 ||
    file_size(query_delete_player_file_name(str) + ".o") > 0 ||
    file_size(query_appeal_player_file_name(str) + ".o.gz") > 0 ||
    file_size(query_appeal_player_file_name(str) + ".o") > 0;
}
int test_deleting(string str) {
  if (player_cache[str])
    return player_cache[str]->deleting;
  if (!validate_name(str))
    return 0;
  if (file_size(query_delete_player_file_name(str) + ".o") > 0)
    return stat(query_delete_player_file_name(str) + ".o")[1];
  if(file_size(query_delete_player_file_name(str) + ".o.gz") > 0)
    return stat(query_delete_player_file_name(str) + ".o.gz")[1];
  return 0;
}
int test_appealing(string str) {
  if (player_cache[str])
    return player_cache[str]->appealing;
  if (!validate_name(str))
    return 0;
  if (file_size(query_appeal_player_file_name(str) + ".o") > 0)
    return stat(query_appeal_player_file_name(str) + ".o")[1];
  if(file_size(query_appeal_player_file_name(str) + ".o.gz") > 0)
    return stat(query_appeal_player_file_name(str) + ".o.gz")[1];
  return 0;
}
int test_gender(string str) {
  if (find_player(str)) {
    map_delete(player_cache, str);
    return find_player(str)->query_gender();
  }
  if (!load_player(str))
    return 0;
  return player_cache[str]->gender;
}
varargs int test_active(string player, int noload) {
  mixed *file;
  if (find_player(player)) {
    map_delete(player_cache, player);
    return 1;
  }
  if (noload) {
    if (player_cache[player])
      return player_cache[player]->active;
    file =
      unguarded((: stat,
                 query_player_disk_file_name(player) + ".o" :));
    if (!file || !sizeof(file)) {
      file =
        unguarded((: stat,
                   query_player_disk_file_name(player) + ".o.gz" :));
    }
    return (sizeof(file) && file[1] > time() - INACTIVE_LIMIT);
  }
  if (!load_player(player))
    return 0;
  return player_cache[player]->active;
}
string query_cap_name(string str) {
  if (find_player(str)) {
    map_delete(player_cache, str);
    return find_player(str)->query_cap_name();
  }
  if (!load_player(str))
    return 0;
  return player_cache[str]->cap_name;
}
int test_level(string str) {
  if (find_player(str)) {
    map_delete(player_cache, str);
    return find_player(str)->query_level();
  }
  if (!load_player(str))
    return 0;
  return player_cache[str]->level;
}
mixed query_guild_data() {
    return guild_data;
}
int query_skill(string skill) {
  if (mapp(new_skills)) {
    return new_skills[skill];
  }
  return 0;
}
int test_banished(string name) {
  return file_size(BANISH_DIR + name[0..0] + "/" + name + ".o") != -1;
}
varargs int test_valid(string name) {
  string *bits, bit, tname;
  name = lower_case(name);
  tname = replace(name, ({ "'", "", "_", " " }));
  bits = explode(tname, " ");
  name = replace(name, ({ "'", " ", "_", " " }));
  bits += explode(name, " ");
  foreach(bit in bits) {
    if (bit == "the" || bit == "von" || bit == "sto" || bit == "here" ||
    bit == "there" || bit == "time") {
      continue;
    }
    if (test_banished(bit))
      return 0;
  }
  name = replace(name, ({ " ", "" }));
  if (test_banished(name))
    return 0;
  foreach(bit in ILLEGAL) {
    if (strsrch(name, bit) != -1)
      return 0;
  }
  return 1;
}
string test_real_name(string str) {
  if (find_player(str)) {
    map_delete(player_cache, str);
    return find_player(str)->query_real_name();
  }
  if (!load_player(str))
    return "";
  return player_cache[str]->player_info["real_name"];
}
string test_email(string str) {
  if(file_name(previous_object())[0..13] != "/secure/finger" &&
     file_name(previous_object())[0..12] != "/secure/login" &&
     file_name(previous_object())[0..13] != "/secure/nlogin")
    return "";
  if (find_player(str)) {
    map_delete(player_cache, str);
    return find_player(str)->query_email();
  }
  if (!load_player(str))
    return "";
  return player_cache[str]->player_info["email"];
}
string test_birthday(string str) {
  if (find_player(str)) {
    map_delete(player_cache, str);
    return find_player(str)->query_birthday();
  }
  if (!load_player(str))
    return "";
  return player_cache[str]->player_info["birthday"];
}
string test_location(string str) {
  if (find_player(str)) {
    map_delete(player_cache, str);
    return find_player(str)->query_where();
  }
  if (!load_player(str))
    return "";
  return player_cache[str]->player_info["location"];
}
string test_homepage(string str) {
  if (find_player(str)) {
    map_delete(player_cache, str);
    return find_player(str)->query_homepage();
  }
  if (!load_player(str))
    return "";
  return player_cache[str]->player_info["homepage"];
}
string test_desc(string str) {
  if (find_player(str)) {
    map_delete(player_cache, str);
    return find_player(str)->query_desc();
  }
  if (!load_player(str))
    return "";
  return player_cache[str]->player_info["desc"];
}
mixed test_player_killer(string word, string str) {
  if (find_player(word)) {
    map_delete(player_cache, word);
    return find_player(word)->query_player_killer();
  }
  if (!load_player(word)) {
    return 0;
  }
  return player_cache[word]->flags & PLAYER_KILLER_FLAG;
}
mixed test_property(string word, string str) {
  if (find_player(word)) {
    map_delete(player_cache, word);
    return find_player(word)->query_property(str);
  }
  if (!load_player(word))
    return 0;
  return player_cache[word]->map_prop[str];
}
void special_add_property(string pname, string prop, mixed val) {
  if(player_cache[pname])
    player_cache[pname]->map_prop[prop] = val;
}
string test_deity(string word) {
  if (find_player(word)) {
    map_delete(player_cache, word);
    return find_player(word)->query_deity();
  }
  if (!load_player(word))
    return 0;
  return player_cache[word]->deity;
}
string test_guild(string word) {
  if (find_player(word)) {
    map_delete(player_cache, word);
    return find_player(word)->query_guild_ob();
  }
  if (!load_player(word))
    return "";
  return player_cache[word]->guild;
}
mixed *test_guild_data(string word) {
  if (find_player(word)) {
    map_delete(player_cache, word);
    return find_player(word)->query_guild_data();
  }
  if (!load_player(word))
    return ({ });
  return player_cache[word]->guild_data;
}
int test_age(string word) {
  if (find_player(word)) {
    map_delete(player_cache, word);
    return find_player(word)->query_time_on();
  }
  if (!load_player(word))
    return 0;
  return player_cache[word]->age;
}
int test_last(string word, int noload) {
  mixed *file;
  if (find_player(word)) {
    map_delete(player_cache, word);
    return find_player(word)->query_last_log_on();
  }
  if (noload) {
    if (player_cache[word]) {
      return player_cache[word]->last;
    }
    word = replace(word, ({ "/", "", "\\", "" }) );
    file =
      unguarded((: stat, query_player_ram_file_name(word) + ".o" :));
    if (!file || !sizeof(file)) {
      file = unguarded((: stat,
                        query_player_disk_file_name(word)+".o.gz" :));
    }
    if(!file || !sizeof(file)) {
      file = unguarded((: stat,
                        query_delete_player_file_name(word)+
                        ".o" :));
    }
    if (!file || !sizeof(file)) {
      file = unguarded((: stat,
                        query_delete_player_file_name(word)+
                        ".o.gz" :));
    }
    if(!file || !sizeof(file)) {
      file = unguarded((: stat,
                        query_appeal_player_file_name(word)+
                        ".o" :));
    }
    if (!file || !sizeof(file)) {
      file = unguarded((: stat,
                        query_appeal_player_file_name(word)+
                        ".o.gz" :));
    }
    if (!sizeof(file))
      return 0;
    return file[1];
  }
  if (!load_player(word)) {
    return 0;
  }
  return player_cache[word]->last;
}
string test_last_on_from(string word) {
  if (find_player(word)) {
    map_delete(player_cache, word);
    return query_ip_name(find_player(word)) + " (" +
      query_ip_number(find_player(word)) + ") ";
  }
  if (!load_player(word)) {
    return 0;
  }
  return player_cache[word]->last_on_from;
}
int test_start_time(string word) {
  if (find_player(word)) {
    map_delete(player_cache, word);
    return find_player(word)->query_start_time();
  }
  if (!load_player(word))
    return 0;
  return player_cache[word]->start_time;
}
int test_creator(string str) {
  str = lower_case (str);
  if (find_player(str)) {
    map_delete(player_cache, str);
    return find_player(str)->query_creator();
  }
  if (!load_player(str))
    return 0;
  return player_cache[str]->creator;
}
string test_home_dir(string str) {
  if (find_player(str)) {
    map_delete(player_cache, str);
    return find_player(str)->query_home_dir();
  }
  if (!load_player(str))
    return 0;
  return player_cache[str]->home_dir;
}
string test_family(string str) {
  if (find_player(str)) {
    map_delete(player_cache, str);
    return find_player(str)->query_family_name();
  }
  if (!load_player(str))
    return 0;
  return player_cache[str]->family_name;
}
string test_player_title(string str) {
  if (find_player(str)) {
    map_delete(player_cache, str);
    return find_player(str)->query_player_title();
  }
  if (!load_player(str))
    return 0;
  return player_cache[str]->player_title;
}
int test_password(string name, string pass) {
  if (!load_player(name)) {
    return 0;
  }
  if (find_player(name) && player_cache[name]->password == "") {
    if(file_size(query_player_ram_file_name(name) + ".o.gz") > 0)
      unguarded((: restore_object, query_player_ram_file_name(name), 1 :));
    else
      unguarded((: restore_object, query_player_disk_file_name(name), 1 :));
    player_cache[name]->password = password;
  }
  return crypt(pass, player_cache[name]->password) ==
    player_cache[name]->password;
}
string get_password(string name) {
  if(file_name(previous_object()) != "/secure/ftp_auth")
    return "x";
  if(!load_player(name))
    return "x";
  if(find_player(name) && player_cache[name]->password == "") {
    unguarded((: restore_object,
               query_player_disk_file_name(name), 1 :));
  }
  return player_cache[name]->password;
}
string query_signature(string name) {
  string sig;
  if (find_player(name)) {
    map_delete(player_cache, name);
    sig =
      make_string(find_player(name)->query_player_alias(".signature"),
                  3);
  } else {
    if (!load_player(name))
      return "";
    sig = make_string(player_cache[name]->signature, 3);
  }
  if (sig && sig != "")
    sig = "\n--\n" + strip_colours(sig);
  return sig;
}
string query_project(string name, int unused) {
  if (find_player(name)) {
    map_delete(player_cache, name);
    if (find_player(name)->query_player_alias(".project"))
      return make_string(find_player(name)->query_player_alias(".project"), 5);
    else
      return "";
  }
  if (!load_player(name))
    return "";
  return make_string(player_cache[name]->project, 5);
}
string query_plan(string name, int unused) {
  if (find_player(name)) {
    map_delete(player_cache, name);
    if (find_player(name)->query_player_alias(".plan"))
      return make_string(find_player(name)->query_player_alias(".plan"),
                         5);
    else
      return "";
  }
  if (!load_player(name))
    return "";
  return make_string(player_cache[name]->plan, 5);
}
string query_reference(string name) {
  if (find_player(name)) {
    map_delete(player_cache, name);
    if (find_player(name)->query_player_alias(".reference"))
      return make_string(find_player(name)->
                         query_player_alias(".reference"), 20);
    else
      return "";
  }
  if (!load_player(name))
    return "";
  return make_string(player_cache[name]->reference, 20);
}
string test_nationality(string str) {
  if (find_player(str)) {
    map_delete(player_cache, str);
    return find_player(str)->query_nationality();
  }
  if (!load_player(str)) {
    return 0;
  }
  return ((class player_record)player_cache[str])->nationality;
}
string test_nationality_region(string str) {
  if (find_player(str)) {
    map_delete(player_cache, str);
    return find_player(str)->query_nationality_region();
  }
  if (!load_player(str)) {
    return 0;
  }
  return player_cache[str]->nationality_region;
}
string test_nationality_data(string str) {
  if (find_player(str)) {
    map_delete(player_cache, str);
    return find_player(str)->query_nationality_data();
  }
  if (!load_player(str)) {
    return 0;
  }
  return player_cache[str]->nationality_data;
}
int test_ip_allowed(string name, string ip) {
  string *ips;
  if(ip == "127.0.0.1")
    return 1;
  if(find_player(name)) {
    map_delete(player_cache, name);
    ips = find_player(name)->query_rhosts();
  } else if (load_player(name))
    ips = player_cache[name]->player_info["allowed_ips"];
  if(!ips || !sizeof(ips))
    return 1;
  while(strlen(ip)) {
    if(member_array(ip, ips) != -1)
      return 1;
    ip = implode((string *)explode(ip, ".")[0..<2], ".");
  }
  return 0;
}
mixed *stats() {
  int percentage;
  if (requests)
    percentage = (cache_hits * 100) / requests;
  return ({ ({ "cache size", sizeof(player_cache) }),
              ({ "requests", requests }),
              ({ "cache hits", cache_hits }),
              ({ "cache misses", requests - cache_hits }),
              ({ "percentage hits", percentage }), });
}
nomask int query_prevent_shadow(object ob) { return 1; }