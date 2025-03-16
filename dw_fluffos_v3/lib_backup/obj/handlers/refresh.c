#include <refresh.h>
#include <playerinfo.h>
#define SAVE_FILE "/save/refresh"
mapping refresh_callbacks;
mapping delete_callbacks;
nosave string loaded_by;
nosave string loaded_time;
protected void load_me()
{
  refresh_callbacks = 0;
  delete_callbacks = 0;
  unguarded( (: restore_object, SAVE_FILE, 0 :) );
  if (!refresh_callbacks) {
    refresh_callbacks = ([ ]);
  }
  if (!delete_callbacks) {
    delete_callbacks = ([ ]);
  }
}
protected void save_me()
{
  unguarded( (: save_object, SAVE_FILE, 0 :) );
}
string query_name() {
   return "Refresh Handler";
}
void create()
{
  seteuid("/secure/master"->creator_file(file_name(this_object())));
  load_me();
  if (!previous_object()) {
    loaded_by = "The Masked Man";
  } else {
    if (previous_object()->query_creator()) {
      loaded_by = "Creator: " + previous_object()->query_name();
    } else if (previous_object()->query_interactive()) {
      loaded_by = "Player: " + previous_object()->query_name();
    } else {
      loaded_by = file_name(previous_object());
      if (this_player())
        loaded_by += sprintf(" (%s)", this_player()->query_name());
    }
  }
  loaded_time = ctime(time());
}
void dest_me()
{
  save_me();
  destruct(this_object());
}
nomask mixed dwep()
{
  efun::destruct(this_object());
  return "Destructed With Extreme Prejudice";
}
string register_refresh(mixed ob, string func)
{
  object real;
  if (objectp(ob)) {
    ob = base_name(ob);
  }
  if (!ob) {
    return "Please supply an object";
  }
  real = load_object(ob);
  if (!real) {
    return "Couldn't find object";
  }
  if (func && !function_exists(func, real)) {
    return "Couldn't find function";
  }
  if (!func) {
    if (refresh_callbacks[ob]) {
      map_delete(refresh_callbacks, ob);
    }
  } else {
    if (refresh_callbacks[ob]) {
      refresh_callbacks[ob] = func;
    } else {
      refresh_callbacks += ([ ob : func ]);
    }
  }
  save_me();
}
string register_delete(mixed ob, string func)
{
  object real;
  if (objectp(ob)) {
    ob = base_name(ob);
  }
  if (!ob) {
    return "Please supply an object";
  }
  real = load_object(ob);
  if (!real) {
    return "Couldn't find object";
  }
  if (func && !function_exists(func, real)) {
    return "Couldn't find function";
  }
  if (!func) {
    if (delete_callbacks[ob]) {
      map_delete(delete_callbacks, ob);
    }
  } else {
    if (delete_callbacks[ob]) {
      delete_callbacks[ob] = func;
    } else {
      delete_callbacks += ([ ob : func ]);
    }
  }
  save_me();
}
varargs void player_refreshed(object player, int totally) {
  string ob;
  if (base_name(file_name(previous_object())) != "/global/player") {
    return;
  }
  foreach (ob in keys(refresh_callbacks)) {
    object obj;
    obj = load_object(ob);
    if (obj) {
      mixed *vals;
      vals = ({ refresh_callbacks[ob], player, totally });
      call_out( (: call_other, obj, vals :), 1);
    }
  }
}
varargs void player_deleted(string player)
{
  string ob;
  if (file_name(previous_object()) != "/secure/delete_clear" &&
      file_name(previous_object()) != "/cmds/lord/rmp_layer" &&
      !master()->high_programmer(previous_object(-1))) {
    unguarded( (: write_file, "/log/CHEAT", ctime( time() ) +
                ": illegal attempt to delete player files using "+
                "refresh_handler\nTrace: "+ back_trace() :) );
    return;
  }
  foreach (ob in keys(delete_callbacks)) {
    object obj;
    obj = load_object(ob);
    if (obj) {
      mixed *vals;
      vals = ({ delete_callbacks[ob], player, PLAYER_DELETED });
      call_out( (: call_other, obj, vals :), 1);
    }
  }
  "/secure/related_files"->delete_related_files(player, 1, 0);
}
mapping query_funcs()
{
  return ([
    "refresh callbacks" : refresh_callbacks,
    "delete callbacks" : delete_callbacks,
    ]);
}
mixed *stats()
{
  return ({
    ({ "refreshes", sizeof(refresh_callbacks) }),
    ({ "deletes", sizeof(delete_callbacks) }),
    ({ "loaded by", loaded_by }),
    ({ "loaded time", loaded_time }),
    });
}