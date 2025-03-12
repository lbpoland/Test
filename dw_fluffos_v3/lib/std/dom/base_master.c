#include <project_management.h>
#include <player_handler.h>
#include <error_handler.h>
#define LOCK_MASK 8
#define PROJECT_CODE "$project$"
mapping members;
mapping access;
nosave private mapping _project_cache;
private int _use_tracker;
private string _idle_mess;
string *deputies;
private mapping _directory_assignments;
private mapping _rcsforce_allowed;
string query_lord();
int query_use_tracker();
void set_use_tracker(int);
string query_domain() {
  string *words;
  if (!file_name (this_object())) {
    return "";
  }
  words =  explode (file_name(this_object()), "/");
  if (sizeof (words) < 2) {
    return "";
  }
  return words[1];
}
int query_prevent_shadow() {
   return 1;
}
protected void create() {
   members = ([ ]);
   access = ([ ]);
   deputies = ({ });
   _project_cache = ([ ]);
   _rcsforce_allowed = ([ ]);
   _idle_mess = 0;
   unguarded((: restore_object, file_name(this_object()) :));
   if (!deputies) {
      deputies = ({ });
   }
   if (!_directory_assignments) {
      _directory_assignments = ([ ]);
   }
   if ( !_rcsforce_allowed ) {
       _rcsforce_allowed = ([ ]);
   }
}
void save_me() {
   unguarded((: save_object, file_name(this_object()) :));
}
int add_permission(string euid,
                   string path,
                   int mask)
{
   if (previous_object() != master()) {
      return 0;
   }
   if (!access[path]){
      access[path] = ([ euid : mask ]);
   } else {
      access[path][euid] |= mask;
   }
   save_me();
   return 1;
}
int remove_permission(string euid,
                      string path,
                      int mask)
{
   if (previous_object() != master())
      return 0;
   if (!access[path])
      return 0;
   if (!access[path][euid])
      return 0;
   access[path][euid] &= ~mask;
   if (!access[path][euid])
      map_delete(access[path], euid);
   if (!sizeof(access[path]))
      map_delete(access, path);
   save_me();
   return 1;
}
int check_permission(string euid,
                     string *path,
                     int mask)
{
   string p;
   mapping perms;
   if ((sizeof(path) >= 3)
       && (path[2] == "master.c" || path[2] == "master.o"
           || path[2] == "master"))
      return 0;
   p = "/" + implode(path, "/");
   perms = master()->permission_match_path(access, p);
   if (!perms || !sizeof(perms)) {
      return 0;
   }
   if (perms[euid] && ((perms[euid] & mask) || (perms["all"] & mask))) {
      return 1;
   }
   if (perms["all"] & LOCK_MASK) {
      return -1;
   }
   return 0;
}
int valid_read(string,
               string euid,
               string)
{
   return 1;
   return (members[euid] != 0);
}
int valid_write(string *path,
                string euid,
                string)
{
   return 0;
   if ((sizeof(path) >= 3)
       && (path[2] == "master.c" || path[2] == "master.o"
           || path[2] == "master"))
      return 0;
   return (members[euid] != 0);
}
void dest_me()
{
   destruct(this_object());
}
int check_call_tree(int only_lord)
{
   object *obs;
   int found;
   int i;
   obs = previous_object(-1);
   for (i = 0; i < sizeof(obs); i++) {
     if (file_name(obs[i])[0..12] == "/global/lord#" ||
         (file_name(obs[i])[0..15] == "/global/creator#")) {
       if("/secure/master"->query_administrator(obs[i]->query_name()) ||
          obs[i]->query_name() == query_lord() ||
          (!only_lord &&
           (member_array(obs[i]->query_name(), deputies) != -1))) {
         found = 1;
       } else {
         return 0;
       }
     }
   }
   return found;
}
int add_member(string name)
{
   if (!check_call_tree(0)) {
      return 0;
   }
   if (members[name])
      return 0;
   members[name] = "newbie";
   save_me();
   return 1;
}
int remove_member(string name)
{
   int pos;
   if (!check_call_tree(member_array(name, deputies) != -1)) {
      return 0;
   }
   if (!members[name])
      return 0;
   members = m_delete(members, name);
   pos = member_array(name, deputies);
   if (pos != -1) {
      deputies = deputies[0..pos - 1] + deputies[pos + 1..];
   }
   save_me();
   return 1;
}
int add_deputy(string name)
{
   if (!check_call_tree(1)) {
      return 0;
   }
   if (!members[name])
      return 0;
   if (!deputies)
      deputies = ({ });
   if (member_array(name, deputies) != -1)
      return 1;
   deputies += ({ name });
   save_me();
   return 1;
}
int remove_deputy(string name)
{
   int pos;
   if (!check_call_tree(1)) {
      return 0;
   }
   if (!deputies)
      deputies = ({ });
   pos = member_array(name, deputies);
   if (pos == -1)
      return 0;
   deputies = deputies[0..pos - 1] + deputies[pos + 1..];
   save_me();
   return 1;
}
int add_rcsforce_allowed( string creator, string directory ) {
    if (!check_call_tree(1)) {
      return 0;
   }
   if ( _rcsforce_allowed[ creator ] ) {
        _rcsforce_allowed[ creator ] += ({ directory });
   }
   else {
        _rcsforce_allowed[ creator ] = ({ directory });
   }
   save_me();
   return 1;
}
int remove_rcsforce_allowed( string creator, string directory ) {
    if (!check_call_tree(1)) {
      return 0;
   }
   if ( _rcsforce_allowed[ creator ] ) {
        _rcsforce_allowed[ creator ] -= ({ directory });
        if ( sizeof( _rcsforce_allowed ) == 0 ) {
            map_delete( _rcsforce_allowed, creator );
        }
        save_me();
   }
   return 1;
}
string *query_members()
{
   return keys(members);
}
int set_project(string name,
                string pro)
{
   if (!check_call_tree(0)) {
      return 0;
   }
   if (!members[name])
      return 0;
   if (!pro || pro == "")
      pro = "project unset";
   members[name] = pro;
   save_me();
   return 1;
}
string query_project(string name)
{
  string *proj;
  string project;
  project = members[name];
  if (!project) {
    return "project unset";
  }
  if (strsrch (project, PROJECT_CODE) != -1) {
    if (!sizeof (_project_cache)) {
      _project_cache = ([ ]);
    }
   if (undefinedp (_project_cache[name])) {
      proj = PROJECT_HANDLER->query_projects_for_creator_in_domain
        (name, query_domain());
      if (sizeof (proj)) {
        _project_cache[name] = query_multiple_short (proj);
      }
      else {
        _project_cache[name] = members[name];
      }
    }
    return replace (project, ({PROJECT_CODE,
      _project_cache[name]}));
  }
  else {
    return members[name];
  }
}
int query_deputy(string name)
{
   if (!deputies)
      return 0;
   if (member_array(name, deputies) != -1)
      return 1;
   return 0;
}
string *query_deputies()
{
   return copy(deputies);
}
mapping query_access()
{
   return copy(access);
}
string query_lord()
{
   return "Something is broken";
}
int can_rcsforce(string file, string person, string locker) {
    string *directories;
    string fdir;
    if (query_deputy(person)) {
        return 1;
    }
    directories = _rcsforce_allowed[ person ];
    if ( directories ) {
        fdir = file[ 0..strsrch( file, "/", -1 ) -1 ];
        foreach ( string directory in directories ) {
            if ( fdir[ 0.. sizeof( directory ) - 1 ] == directory ) {
                return 1;
            }
        }
    }
    return 0;
}
string query_changelog (string filename) {
  return  "/d/" + query_domain() + "/ChangeLog";
}
void set_use_tracker(int i) {
  _use_tracker = i;
}
int query_use_tracker() {
  return _use_tracker;
}
int nuke_creator_project_cache(string *creators) {
  if (!_project_cache) {
    return 0;
  }
  foreach (string c in creators) {
    map_delete (_project_cache, c);
    return 1;
  }
}
int set_idle_mess( string txt ) {
   if (!check_call_tree(1)) {
        return 0;
   }
   _idle_mess = txt;
   save_me();
   return 1;
}
string query_idle_mess() {
    return _idle_mess;
}
string* query_assigned_to_directory(string* dir) {
   string str;
   int i;
   i = sizeof(dir) - 1;
   do {
      str = "/" + implode(dir[0..<i], "/");
      i--;
   } while (i >= 0 && !_directory_assignments[str]);
   if (_directory_assignments[str]) {
      return _directory_assignments[str];
   }
   return ({ query_lord() });
}
int assign_people_to_directory(string dir, string* people) {
   if (previous_object() != master()) {
      return 0;
   }
   if (sizeof(people)) {
      if (sizeof(people) == 1 && people[0] == ERROR_ASSIGNED_NO_ONE) {
         people = ({ });
      }
      _directory_assignments[dir] = people;
   } else {
      map_delete(_directory_assignments, dir);
   }
   save_me();
   return 1;
}
mapping query_directory_assignments() {
   mapping ret;
   string dir;
   ret = copy(_directory_assignments);
   dir = "/d/" + query_domain();
   if (!ret[dir]) {
      ret[dir] = ({ query_lord() });
   } else {
      ret[dir] |= ({ query_lord() });
   }
   return ret;
}