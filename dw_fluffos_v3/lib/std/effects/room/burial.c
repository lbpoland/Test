#include <effect.h>
#include <cmds/bury.h>
class arg_stuff {
   object cont;
   object* obs;
   int* added;
}
private mapping _stuff;
private int _call_id;
int timeout_ob(object room, int enum, object ob);
void check_buried();
void create() {
   _stuff = ([ ]);
}
string query_classification() { return "room.burial"; }
mixed beginning( object room, object ob ) {
   if (!_stuff[room]) {
      _stuff[room] = new(class arg_stuff);
      _stuff[room]->cont = clone_object("/std/container");
      _stuff[room]->cont->add_property("burial object", 1);
      _stuff[room]->obs = ({ });
      _stuff[room]->added = ({ });
   }
   ob->move(_stuff[room]->cont);
   event (ob, "bury", ob, room);
   _stuff[room]->obs += ({ ob });
   _stuff[room]->added += ({ time() });
   if (!_call_id) {
      _call_id = call_out("check_buried", BURY_TIMEOUT);
   }
   return room;
}
mixed merge_effect( object room, class arg_stuff womble, object ob ) {
   if (!_stuff[room]) {
      _stuff[room] = new(class arg_stuff);
      _stuff[room]->cont = clone_object("/std/container");
      _stuff[room]->obs = ({ });
      _stuff[room]->added = ({ });
      _stuff[room]->cont->add_property("burial object", 1);
   }
   ob->move(_stuff[room]->cont);
   event (ob, "bury", ob, room);
   _stuff[room]->obs += ({ ob });
   _stuff[room]->added += ({ time() });
   if (!_call_id) {
      _call_id = call_out("check_buried", BURY_TIMEOUT);
   }
   return room;
}
void end( object room, class arg_stuff womble ) {
    if ( womble && classp( womble ) ) {
      all_inventory(womble->cont)->move("/room/rubbish");
      womble->cont->dest_me();
    }
}
int query_indefinite() { return 1; }
void check_buried() {
   object room;
   int i;
   class arg_stuff bing;
   _call_id = call_out("check_buried", BURY_TIMEOUT);
   foreach (room, bing in _stuff) {
     if(!classp(bing))
       continue;
     if (!room) {
       bing->obs = filter(bing->obs, (: $1 && environment($1) == $2 :),
                          bing->cont);
       bing->obs->dest_me();
       if(bing->cont)
         bing->cont->dest_me();
       map_delete(_stuff, room);
     } else {
       for (i = 0; i < sizeof(bing->obs); i++) {
         if (!bing->obs[i] ||
             environment(bing->obs[i]) != bing->cont)  {
           bing->obs = bing->obs[0..i-1] + bing->obs[i+1..];
           bing->added = bing->added[0..i-1] + bing->added[i+1..];
         } else if (bing->added[i] + BURY_TIMEOUT < time()) {
           bing->obs[i]->dest_me();
           bing->obs = bing->obs[0..i-1] + bing->obs[i+1..];
           bing->added = bing->added[0..i-1] + bing->added[i+1..];
         }
       }
       if (!sizeof(bing->obs)) {
         if (bing->cont) {
           bing->cont->dest_me();
         }
         map_delete(_stuff, room);
       }
     }
   }
   if (!sizeof(_stuff)) {
     remove_call_out(_call_id);
     _call_id = 0;
   }
}
object* query_buried_objects(object room) {
   if (_stuff[room]) {
      return _stuff[room]->obs;
   }
   return ({ });
}
object query_buried_container(object room) {
   if (_stuff[room]) {
      return _stuff[room]->cont;
   }
   return 0;
}
int remove_from_burial(object room, object ob) {
   int i;
   if (_stuff[room]) {
      i = member_array(ob, _stuff[room]->obs);
      if (i != -1) {
         _stuff[room]->obs = _stuff[room]->obs[0..i-1] +
                             _stuff[room]->obs[i+1..];
         _stuff[room]->added = _stuff[room]->added[0..i-1] +
                               _stuff[room]->added[i+1..];
         return 1;
      }
   }
   return 0;
}
mapping query_dynamic_auto_load() {
   return ([ "stuff" : _stuff ]);
}
void init_dynamic_arg(mapping map) {
   if (map && map["stuff"]) {
      _stuff = map["stuff"];
      if (!_call_id) {
         _call_id = call_out("check_buried", BURY_TIMEOUT);
      }
   }
}