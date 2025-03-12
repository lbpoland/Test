#define CREATOR "Ceres"
#include <login_handler.h>
#define SHADOW "/std/shadows/misc/team"
#define MAX_GROUP_SIZE 5
class group {
  object leader;
  int policy;
  object *members;
  int locked;
}
mapping groups,
        members;
private void check_group(string g_name);
private void disband_group(string g_name, string p_name);
private void tidy_members(string g_name);
void create() {
  members = ([ ]);
  groups = ([ ]);
}
void dest_me() {
  destruct(this_object());
}
void leaving(string p_name, string type) {
  class group record;
  string g_name;
  if((type != "logout") || (!members[p_name]))
    return;
  g_name = members[p_name];
  record = (class group)groups[g_name];
  map_delete(members, p_name);
  if(!record)
    return;
  if((record->leader == 0) || ((record->leader)->query_name() == p_name)) {
     disband_group(g_name, p_name);
#ifdef LOG_FILE
    log_file(LOG_FILE, sprintf("%s %s has left the game, the %s has been "
                             "disbanded.\n", ctime(time()), p_name, g_name));
#endif
  } else {
#ifdef LOG_FILE
    log_file(LOG_FILE, sprintf("%s %s left the game while a member of the %s\n",
                             ctime(time()), p_name, g_name));
#endif
    record->members = delete(record->members,
                             member_array(0, record->members), 1);
  }
  return;
}
int new_group(string g_name, object leader, int policy) {
  class group record;
  if(!undefinedp(groups[g_name]))
    return 0;
  record = new(class group);
  record->leader = leader;
  record->policy = policy;
  record->members = ({ leader });
  groups[g_name] = record;
  members[leader->query_name()] = g_name;
  leader->set_title( "TEAM", "Team Leader of "+ g_name );
   clone_object( SHADOW )->setup_shadow( leader );
#ifdef LOG_FILE
  log_file(LOG_FILE, sprintf("%s %s created by %s\n", ctime(time()),
                           g_name, leader->query_name()));
#endif
  return 1;
}
int end_group(string g_name) {
  class group record;
  object player;
  if(undefinedp(groups[g_name]))
    return 0;
  record = groups[g_name];
   foreach( player in record->members )
      if ( player ) {
         map_delete( members, player->query_name() );
         player->remove_title( "TEAM" );
         player->destruct_team_shadow();
      }
  map_delete(groups, g_name);
#ifdef LOG_FILE
  log_file(LOG_FILE, sprintf("%s %s disbanded\n", ctime(time()), g_name));
#endif
  return 1;
}
int join_group(string g_name, object player) {
  class group record;
  if(undefinedp(groups[g_name]))
    return 0;
  record = groups[g_name];
  record->members += ({ player });
  members[player->query_name()] = g_name;
   player->set_title( "TEAM", "Team Member of "+ g_name );
   clone_object( SHADOW )->setup_shadow( player );
#ifdef LOG_FILE
  log_file(LOG_FILE, sprintf("%s %s joined by %s\n", ctime(time()),
                           g_name, player->query_name()));
#endif
  return 1;
}
int leave_group(string g_name, object player) {
  class group record;
  if(player) {
    map_delete(members, player->query_name());
      player->remove_title( "TEAM" );
      player->destruct_team_shadow();
#ifdef LOG_FILE
    log_file(LOG_FILE, sprintf("%s %s left by %s\n", ctime(time()), g_name,
                             player->query_name()));
#endif
  }
  if(undefinedp(groups[g_name]))
    return 0;
  record = groups[g_name];
  if(member_array(player, record->members) == -1)
    return -1;
  record->members = delete(record->members,
                           member_array(player, record->members), 1);
  return 1;
}
object query_owner(string g_name) {
  class group record;
  if(undefinedp(groups[g_name]))
    return 0;
  record = (class group)groups[g_name];
  return record->leader;
}
object *query_members(string g_name) {
  class group record;
  if(undefinedp(groups[g_name]))
    return 0;
  tidy_members(g_name);
  record = groups[g_name];
  return (object *)record->members;
}
int query_policy(string g_name) {
  class group record;
  if(undefinedp(groups[g_name]))
    return 0;
  record = groups[g_name];
  return (int)record->policy;
}
string query_group(object player) {
  if(undefinedp(members[player->query_name()]))
    return 0;
  return members[player->query_name()];
}
int test_group(string g_name) {
  if(undefinedp(groups[g_name]))
    return 0;
  return 1;
}
int query_full(string g_name) {
  class group record;
  object member;
  if(undefinedp(groups[g_name]))
    return 0;
  tidy_members(g_name);
  record = (class group)groups[g_name];
  if(sizeof(record->members) >= MAX_GROUP_SIZE)
    return 1;
  return 0;
}
int query_locked(string g_name) {
  class group record;
  if(undefinedp(groups[g_name]))
    return 0;
  record = (class group)groups[g_name];
  return (record->locked);
}
int set_locked(string g_name, int lock) {
  class group record;
  if(undefinedp(groups[g_name]))
    return 0;
  record = (class group)groups[g_name];
  record->locked = lock;
  return 1;
}
string *list_groups() {
  string frog;
  foreach (frog in keys(groups)) {
    check_group(frog);
  }
  return keys(groups);
}
private void disband_group(string g_name, string p_name) {
  class group record;
  object person;
  object member;
  record = (class group)groups[g_name];
  foreach(member in record->members) {
    if(!member)
      break;
    map_delete(members, member->query_name());
    foreach(person in member->query_protectors())
      member->remove_protector(person);
    foreach(person in member->query_followers())
      member->remove_follower(person);
    tell_object(member, p_name+" has left the game and so the "+g_name+
                " has been disbanded.\n");
  }
  map_delete(groups, g_name);
}
private void check_group(string g_name) {
  class group record;
  record = (class group)groups[g_name];
  if (record->leader == 0) {
    disband_group(g_name, "Your leader");
  } else {
    record->members -= ({ 0 });
  }
}
private void tidy_members(string g_name) {
  class group record;
  object member;
  record = (class group)groups[g_name];
  foreach(member in record->members)
    if(!member)
      record->members -= ({ 0 });
}