#include <weather.h>
#include <climate.h>
#include <am_time.h>
void open_up();
void close_up();
private string _keeper;
private string *_outside_rooms;
private string *_exits;
private string _burglar;
private string _file;
private int _flag;
private int _open;
private int _closed;
private nosave object _keeper_ob;
void event_weather(int whats_changed){
   if(whats_changed >= 8){
      if (_flag) {
         call_out("night_time_check", 1);
      } else {
         call_out("day_time_check", 1);
      }
   }
}
protected void night_time_check(){
   int bing;
   bing = AM_TIME_HANDLER->query_am_hour(time() );
   if (bing > 12 && bing < 23 && !_closed) {
      _open = 0;
      _closed = 1;
      close_up();
   }
   if (bing > 0 && bing < 12 && !_open) {
      _closed = 0;
      _open = 1;
      open_up();
   }
}
protected void day_time_check(){
   int bing;
   bing = AM_TIME_HANDLER->query_am_hour(time() );
   if (bing > 0 && bing < 12 && !_closed) {
      _open = 0;
      _closed = 1;
      close_up();
   }
   if (bing > 12 && bing < 23 && !_open) {
      _closed = 0;
      _open = 1;
      open_up();
   }
}
void set_night_close(int night, string shopkeeper, string *outside,
    string burglar_func){
   int i;
   _flag = night;
   WEATHER->weather_notify( this_object(), NOTIFY_DAY );
   _keeper = _file = shopkeeper;
   if (sizeof(outside) && !(sizeof(outside)%2)) {
      _exits = allocate(sizeof(outside)/2);
      _outside_rooms = allocate(sizeof(outside)/2);
      for(i=0; i<sizeof(outside); i++) {
         if(!i%2)
            _outside_rooms[i] = outside[i];
         else
            _exits[i-1] = outside[i];
      }
   }
   _burglar = burglar_func;
}
void close_up(){
   object *obs;
   object *people;
   object bing;
   object *keeper_ob;
   int i;
   if (_keeper == "none") {
     event (this_object(), "person_say", "The shopkeeper says: ",
       "I'm sorry, it's time to close!", "common");
     tell_room (this_object(), "The shopkeeper ushers you out of "
          "the store.\n");
   }
   else {
      keeper_ob = children(_keeper);
      if (!sizeof(keeper_ob)) {
         return;
      }
      if (keeper_ob[0]->query_fighting()) {
         call_out("close_up", 60);
         return;
      }
      keeper_ob[0]->do_command("'I'm sorry, it's time to close!");
      keeper_ob[0]->do_command(":ushers you out of the store.");
      keeper_ob[0]->move("/room/rubbish");
   }
   obs = all_inventory( this_object() );
   people = filter(obs, (: $1->query_property("player") :));
   foreach(bing in people){
      bing->move_with_look(_outside_rooms[0]);
   }
   for(i=0; i<sizeof(_outside_rooms); i++){
      _outside_rooms[i]->modify_exit(_exits[i], ({"open", 0, "locked", 1,
          "difficulty", 4}));
   }
}
void open_up(){
   int i;
   for(i=0; i<sizeof(_outside_rooms); i++){
     _outside_rooms[i]->modify_exit(_exits[i], ({"open", 1, "locked", 0,
        "difficulty", 4}));
   }
   if (_keeper == "none") {
      return;
   }
   _keeper_ob = clone_object(_file);
   _keeper_ob->move(this_object());
}
void event_enter(object ob, string message, object from){
   if (!_burglar) {
      return;
   }
   if (!_closed) {
      return;
   }
   if (ob->query_creator()) {
      return;
   }
   if (!ob->query_property("player")) {
      return;
   }
   call_out(_burglar, 1, ob);
}
mapping query_dynamic_auto_load() {
   return ([ "keeper ob" : _keeper_ob ]);
}
void init_dynamic_arg(mapping map) {
   _keeper_ob = map["keeper ob"];
}