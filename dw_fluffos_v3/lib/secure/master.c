inherit "/secure/master/directory_assignments";
#define ROOT "Root"
#include <log.h>
#include <player_handler.h>
#define TRUSTEES ([ ROOT : 1, "cratylus" : 1,])
#define READ_MASK 1
#define WRITE_MASK 2
#define GRANT_MASK 4
#define LOCK_MASK 8
#define SENIOR 4
#define DIRECTOR 1
#define TRUSTEE 2
private mapping positions, permissions;
private nosave  mapping trustees, checked_master, snoop_list;
private nosave  object unguarded_ob;
protected void create() {
  set_eval_limit(2000000);
  permissions = ([ ]);
  positions   = ([ ]);
  checked_master = ([ ]);
  snoop_list = ([ ]);
  unguarded_ob = 0;
  trustees = TRUSTEES;
  if (!unguarded((: restore_object, "/secure/master" :)))
    if (!unguarded((: restore_object, "/secure/config/master_fallback" :)))
      error("The master object couldn't restore its save file.");
}
string query_name() { return "Root"; }
object connect(int port) {
  object ob;
  if (!find_object("/secure/login")) {
    log_file("REBOOT", "Mud rebooted at "+ctime(time())+"["+time()+"]"+"\n");
  }
#ifdef __VERSION__
#  define VERSION __VERSION__
#endif
  printf("LPmud version : %s on port %d.", VERSION, port);
  switch (port) {
    case 4243 :
      ob = clone_object("/secure/nlogin");
      if(!ob)
        destruct(this_object());
      break;
    default :
      ob = clone_object("/secure/login");
      break;
  }
  ob->set_login_port(port);
  printf("\n");
  return ob;
}
int query_trustee(mixed str) {
  if (pointerp(str)) {
    str = filter(str, (: interactive($1) :));
    return sizeof(filter((object *)str,
                         (: geteuid($1) == ROOT ||
                          positions[geteuid($1)] == TRUSTEE ||
                          trustees[geteuid($1)] :))) == sizeof(str);
  }
  return ((str == ROOT) || (positions[str] == TRUSTEE) ||
          (trustees[str]));
}
int query_administrator(mixed str) {
  return query_trustee(str);
}
int high_programmer(mixed str) {
  return query_trustee(str);
}
int query_director( mixed arg ) {
  if ( pointerp( arg ) ) {
    arg = filter(arg, (: interactive($1) :));
    return sizeof( filter( (object *)arg,
                           (: ( positions[ geteuid( $1 ) ] == DIRECTOR ) ||
            query_trustee( geteuid( $1 ) ) :) ) ) == sizeof( arg );
  }
  return ( ( positions[ arg ] == DIRECTOR ) || query_trustee( arg ) );
}
int query_leader( mixed arg ) { return query_director( arg ); }
int query_lord( mixed arg ) { return query_director( arg ); }
int query_only_director( string word ) {
   return positions[ word ] == DIRECTOR;
}
int query_only_leader( string word ) { return query_only_director( word ); }
int query_only_lord( string word ) { return query_only_director( word ); }
string *query_directors() {
  return filter_array(keys(positions),
                      "query_only_director", this_object());
}
string *query_leaders() { return query_directors(); }
string *query_lords() { return query_directors(); }
int query_player_trustee(string str) {
  return query_trustee(str) && PLAYER_HANDLER->test_user(str);
}
int query_player_administrator(string str) {
  return query_player_trustee(str);
}
int query_player_high_lord(string str) {
  return query_player_trustee(str);
}
string *high_programmers() { return keys( trustees ); }
string *query_administrators() { return keys( trustees ); }
string *query_trustees() { return keys( trustees ); }
string *query_all_directors() {
  return filter_array(keys(positions), "query_director", this_object() );
}
string *query_all_leaders() { return query_all_directors(); }
string *query_all_lords() { return query_all_directors(); }
int is_leader_of(string person, string domain) {
  return ("/d/" + domain + "/master")->query_lord() == person;
}
int is_deputy_of(string person, string domain) {
   return ("/d/" + domain + "/master")->query_deputy(person);
}
int is_liaison_deputy(string person) {
   return "/d/liaison/master"->query_deputy(person);
}
int query_liaison_deputy_or_director(mixed arg) {
  if ( pointerp( arg ) ) {
    arg = filter(arg, (: interactive($1) :));
    return sizeof( filter( (object *)arg,
                           (: query_director(geteuid( $1 )) ||
            is_liaison_deputy( geteuid( $1 ) ) :) ) ) == sizeof( arg );
  }
  return ( is_liaison_deputy(arg) || query_director( arg ) );
}
int query_liaison_deputy_or_lord(mixed arg) {
  return query_liaison_deputy_or_director(arg);
}
int query_senior( mixed arg ) {
   if ( pointerp( arg ) )
      return sizeof(filter( (object *)arg,
            (: ( positions[ geteuid( $1 ) ] == SENIOR ) ||
            query_leader( geteuid( $1 ) ) :) ) ) == sizeof( arg );
   return ( ( positions[ arg ] == SENIOR ) || query_leader( arg ) );
}
string *query_all_seniors() {
   return filter_array( keys( positions ), "query_senior", this_object() );
}
string *query_domains() {
  string *domains;
  domains = (get_dir("/d/") - ({ "lost+found", "core" }));
  return filter(domains, (: $1[<4..] != "_dev" :));
}
int valid_load(string path, mixed euid, string func) { return 1; }
string get_root_uid() { return ROOT; }
string get_bb_uid() { return "Room"; }
string *define_include_dirs() {
  return ({ "/include/%s" });
}
int valid_trace() { return 1; }
void shut(int min) {
  "/obj/shut"->shut(min);
}
void remove_checked_master(string name) {
  map_delete(checked_master, name);
}
mapping query_checked_master() { return checked_master; }
varargs mixed apply_unguarded(function f, int local) {
  object previous_unguarded;
  string err;
  mixed val;
  if (base_name(previous_object(0)) != "/secure/simul_efun") {
    error("Illegal unguarded apply.");
    return 0;
  }
  previous_unguarded = unguarded_ob;
  if (local)
    unguarded_ob = master();
  else
    unguarded_ob = previous_object(1);
  err = catch(val = (mixed)(*f)());
  unguarded_ob = previous_unguarded;
  if (err) {
    error(err);
  }
  return val;
}
#include "/secure/master/permission.c"
#include "/secure/master/crash.c"
#include "/secure/master/create_dom_creator.c"
#include "/secure/master/creator_file.c"
#include "/secure/master/dest_env.c"
#include "/secure/master/ed_stuff.c"
#include "/secure/master/file_exists.c"
#include "/secure/master/logging.c"
#include "/secure/master/parse_command.c"
#include "/secure/master/preload.c"
#include "/secure/master/query_pl_level.c"
#include "/secure/master/simul_efun.c"
#include "/secure/master/snoop.c"
#include "/secure/master/valid_database.c"
#include "/secure/master/valid_exec.c"
#include "/secure/master/valid_hide.c"
#include "/secure/master/valid_ident.c"
#include "/secure/master/valid_link.c"
#include "/secure/master/valid_override.c"
#include "/secure/master/valid_read.c"
#include "/secure/master/valid_seteuid.c"
#include "/secure/master/valid_shadow.c"
#include "/secure/master/valid_socket.c"
#include "/secure/master/valid_write.c"
#include "/secure/master/valid_copy.c"
#include "/secure/master/virtual_objects.c"
#include "/secure/master/valid_bind.c"
#include "/secure/master/valid_to_c.c"
#include "/secure/master/valid_binary.c"