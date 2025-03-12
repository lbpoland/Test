#include <player_handler.h>
#include <login.h>
#include <move_failures.h>
inherit "/global/auto_load";
class delivery_item {
    object delivery_ob;
    string sent_by;
    int submit_time;
    int delay_time;
}
protected void set_delivery_delay(int new_time);
protected int valid_delivery(class delivery_item delivery, string person);
protected void deliver_item(string who, object ob, string sent_by);
protected void set_burdened_mess(string s);
protected void set_delivery(mapping x);
protected void set_delivery_mess(string s);
protected void set_save_file(string str);
public int query_delivery_delay();
public string query_burdened_mess();
public string query_delivery_mess();
public string query_save_file();
public varargs mixed query_delivery(string person);
public void add_delivery(mixed who, mixed sender, object item, int delay);
public void check_delivery(mixed person, string type);
public void clear_delivery();
public void setup_delivery();
public void load_file();
public void save_file();
private mapping _delivery;
private mixed _item_save;
private nosave string _save_file;
private nosave object _cont;
private nosave string _delivery_mess;
private nosave string _burdened_mess;
private nosave int _delivery_delay;
void create() {
    _delivery = ([ ]);
    _save_file = "";
    _delivery_delay = 5;
    _delivery_mess = "\nA small womble wearing a bright green hat "
        "strides up to you confidently and hands you $N.  She "
        "mutters something about \"delivery\" and \"$S\", before "
        "scurrying away.\n";
    _burdened_mess = "\nA small womble wearing a bright purple "
        "hat strides up to you, and places \"$N\" on the ground.  She "
        "mutters something about a gift from \"$S\", and the runs off.\n";
    _cont = clone_object("/std/container");
    call_out("tidy_up", 30 + random(30));
}
public void setup_delivery() {
    LOGIN_HANDLER->add_static_login_call("all", "check_delivery",
        base_name(this_object()));
}
public string query_save_file() {
    return _save_file;
}
protected void set_save_file(string str) {
    _save_file = str;
}
public void clear_delivery() {
    _delivery = ([ ]);
    save_file();
}
protected void set_delivery(mapping x) {
    _delivery = x;
    save_file();
}
void add_delivery(mixed who, mixed sender, object item, int delay) {
    string name, from;
    class delivery_item parcel;
    if (objectp(who))
        name = who->query_name();
    else
        name = who;
    if (objectp(sender))
        from = sender->query_cap_name();
    else
        from = sender;
    parcel = new(class delivery_item,
        delivery_ob : item, submit_time : time(), sent_by : from,
        delay_time : delay);
    if (undefinedp(_delivery[name]))
        _delivery[name] = ({ parcel });
    else
        _delivery[name] += ({ parcel });
    log_file("DELIVERY", "%s added a new delivery item for %s, %s sent "
        "by %s.\n", previous_object()->short(), name, item->short(),
        from);
    item->move(_cont);
    save_file();
}
protected int valid_delivery(class delivery_item delivery, string person) {
  if (delivery->submit_time + delivery->delay_time > time())
    return 1;
  if (!objectp(delivery->delivery_ob))
    return 0;
  call_out( (: deliver_item :), _delivery_delay, person, delivery->delivery_ob,
            delivery->sent_by);
  return 0;
}
public void check_delivery(mixed person, string type) {
    if (type != LOGIN && type != RECONNECT)
        return;
    if (!_delivery[person])
        return;
    _delivery[person] = filter(_delivery[person],
        (: valid_delivery($1, $(person)) :));
    if (!sizeof(_delivery[person]))
        map_delete(_delivery, person);
    save_file();
}
protected void deliver_item(string who, object ob, string sent_by) {
    string new_mess;
    object player;
    player = find_player(who);
    if (!player)
        ob->move("/room/rubbish");
    if (ob->move(player) != MOVE_OK) {
        if (environment(player)) {
            new_mess = replace(_burdened_mess, ({ "$S", sent_by, "$N",
                "$0$" }));
            player->add_message(new_mess,  ({ ({ "my_a_short:" +
            file_name(ob) }) }));
            ob->move(environment(player), );
        }
        else {
            ob->move("/room/rubbish", "$N appear$s in a puff of smoke.");
            log_file("DELIVERY", "%s: %s sent to the rubbish room, %s has "
                "no environment.\n", ctime(time()), ob->short(),
                player->short());
        }
    }
    else {
        new_mess = replace(_delivery_mess, ({ "$S", sent_by, "$N", "$0$" }));
        player->add_message(new_mess,  ({ ({ "my_a_short:" +
            file_name(ob) }) }));
        log_file("DELIVERY", "%s: %s delivered to %s.\n", ctime(time()),
            ob->short(), who);
    }
}
int query_theft_command() {
    return -1;
}
void clean_delivery_mapping() {
    string *people, person;
    people = keys(_delivery);
    foreach (person in people) {
        _delivery[person] = filter(_delivery[person],
            (: objectp($1->delivery_ob) :));
    }
    _delivery = filter(_delivery, (: sizeof($2) :));
}
public void save_file() {
  mixed *tmp;
  string player;
  class delivery_item *values;
  if(_save_file == "")
    return;
  _item_save = ({ });
  clean_delivery_mapping();
  foreach (player, values in _delivery) {
    tmp = map(values, (: $1->delivery_ob :));
    if (!arrayp(tmp))
      continue;
    _item_save += ({ player, create_auto_load(tmp, 0) });
  }
  tell_creator("ceres", "Saving: %s\n", _save_file);
  unguarded((: save_object, _save_file :));
  _item_save = 0;
}
void load_file() {
  int i, j, size;
  mixed *tmp;
  string who;
  mixed *items;
  if(_save_file == "")
    return;
  log_file("DELIVERY", "Attempting to load save file at %s.\n",
           ctime(time()));
  tell_creator("ceres", "Loading: %s\n", _save_file);
  if (file_size(_save_file + ".o") > -1) {
    unguarded((: restore_object, _save_file :));
    if (!_cont)
      _cont = clone_object("/std/container");
    all_inventory(_cont)->move("/room/rubbish");
    for (i = 0; i < sizeof(_item_save); i = i + 2) {
      who = _item_save[i];
      items = _item_save[i + 1];
      if (!_delivery[who])
        return;
      tmp = load_auto_load_to_array(items, this_player());
      size = sizeof(tmp);
      for (j = 0; j < size; j++) {
        _delivery[who][j]->delivery_ob = tmp[size - j - 1];
        tmp[j]->move(_cont);
      }
    }
    _item_save = 0;
  }
}
public string query_delivery_mess() {
    return _delivery_mess;
}
public int query_delivery_delay() {
    return _delivery_delay;
}
protected void set_delivery_delay(int new_time) {
    _delivery_delay = new_time;
}
protected void set_delivery_mess(string s) {
    _delivery_mess = s;
}
protected void set_burdened_mess(string s) {
    _burdened_mess = s;
}
public string query_burdened_mess() {
    return _burdened_mess;
}
public varargs mixed query_delivery(string person) {
    if (undefinedp(_delivery[person])) {
        return copy(_delivery);
    }
    else {
        return copy(_delivery[person]);
    }
}
void dest_me() {
    if (_cont)
        _cont->dest_me();
}
object query_cont() {
  return _cont;
}
void tidy_up() {
  string person;
  foreach(person in keys(_delivery)) {
    if(!PLAYER_HANDLER->test_user(person) || !PLAYER_HANDLER->test_active(person)) {
      log_file("DELIVERY", "%s Removing delivery for %s (inactive).\n",
               this_object()->query_short(), person);
      map_delete(_delivery, person);
    }
  }
  save_file();
}
mixed *stats() {
    return ({
        ({ "delivery mess", replace(_delivery_mess, ({ "\n",  "" }) ) }),
        ({ "burdened mess", replace(_burdened_mess, ({ "\n",  "" }) ) }),
        ({ "delivery delay", _delivery_delay, }),
        ({ "delivery save file", _save_file, }),
        ({ "undelivered items", _cont ? sizeof(all_inventory(_cont)) : 0 }),
    });
}