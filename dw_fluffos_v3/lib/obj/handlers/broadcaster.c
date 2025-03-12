#define DIR_ARRAY ({ "east", "northeast", "north", "northwest", \
                     "west", "southwest", "south", "southeast", "east" })
#define SAVE_FILE "/save/broadcaster"
#define BROADCAST_HISTORY_LENGTH 10
void broadcast_event( object *things,
                      int *centre,
                      string message,
                      int range,
                      int inside,
                      int underwater );
void npc_hear_shouts(object newlistener);
int npc_unhear_shouts(object oldlistener);
void npc_shout_event( object shouter,
                      string start,
                      string message,
                      string lang,
                      int *coord,
                      int range );
private void load_me();
private void save_me();
private nosave object *_listeners;
private nosave mapping _channels;
private nosave mapping _channel_history;
private mapping _channel_ids;
void create() {
   _listeners = ({ });
   _channels = ([ ]);
   _channel_ids = ([ ]);
   _channel_history = ([ ]);
   load_me();
}
mixed *get_direc_dist( int *co_ord1, int *co_ord2 ) {
   int dx, dy, dz, sector;
   if (!pointerp(co_ord1) ||
       !pointerp(co_ord2)) {
      return ({ 0, DIR_ARRAY[0], 0 });
   }
   dx = co_ord1[ 0 ] - co_ord2[ 0 ];
   dy = co_ord1[ 1 ] - co_ord2[ 1 ];
   dz = co_ord1[ 2 ] - co_ord2[ 2 ];
   if ( dx > 0 ) {
      if ( ( 1000 * dy ) > ( 2414 * dx ) ) {
         sector = 0;
      } else {
         if ( ( 1000 * dy ) > ( 414 * dx ) ) {
            sector = 1;
         } else {
            if ( ( 1000 * dy ) > ( -414 * dx ) ) {
               sector = 2;
            } else {
               if ( ( 1000 * dy ) > ( -2414 * dx ) ) {
                  sector = 3;
               } else {
                  sector = 4;
               }
            }
         }
      }
   } else {
      if ( ( 1000 * dy ) < ( 2414 * dx ) ) {
         sector = 4;
      } else {
         if ( ( 1000 * dy ) < ( 414 * dx ) ) {
            sector = 5;
         } else {
            if ( ( 1000 * dy ) < ( -414 * dx ) ) {
               sector = 6;
            } else {
               if ( ( 1000 * dy ) < ( -2414 * dx ) ) {
                  sector = 7;
               } else {
                  sector = 8;
               }
            }
         }
      }
   }
   return ({ dx * dx + dy * dy + dz * dz, DIR_ARRAY[ sector ], dz });
}
void broadcast_event( object *things, int *centre, string message,
      int range, int inside, int underwater ) {
   int *to;
   string text;
   object thing, place;
   mixed *dir_direc;
   if ( !pointerp( things ) ||
        !pointerp( centre ) ||
        sizeof( centre ) != 3 ) {
      return;
   }
   foreach ( thing in things ) {
      if ( !living( thing ) ) {
         continue;
      }
      place = environment( thing );
      if ( !place ) {
         continue;
      }
      to = (int *)place->query_co_ord();
      if ( !pointerp( to ) || sizeof( to ) != 3 ) {
         continue;
      }
      switch ( (string)place->query_property( "location" ) ) {
         case "inside" :
            if ( !inside ) {
               continue;
            }
            break;
         case "underwater" :
            if ( !underwater ) {
               continue;
            }
            break;
         default :
      }
      dir_direc = get_direc_dist( centre, to );
      if ( dir_direc[ 0 ] < 0 ) {
         continue;
      }
      if ( dir_direc[ 0 ] > range * range ) {
         continue;
      }
      switch ( dir_direc[ 0 ] ) {
         case 0 :
            continue;
         case 1 .. 2500 :
            if ( ( dir_direc[ 2 ] * dir_direc[ 2 ] ) > ( dir_direc[ 0 ] / 2 ) ) {
               if ( dir_direc[ 2 ] > 0 ) {
                  text = "Right above you, "+ message +"\n";
               } else {
                  text = "Right below you, "+ message +"\n";
               }
            } else {
               text = "Very close to the "+ dir_direc[ 1 ] + ", "+
                     message +"\n";
            }
            break;
         case 2501 .. 40000 :
            text = "Nearby to the "+ dir_direc[ 1 ] + ", "+ message +"\n";
            break;
         case 40001 .. 640000 :
            text = "To the "+ dir_direc[ 1 ] + ", "+ message +"\n";
            break;
         case 640001 .. 10240000 :
            text = "In the distance to the "+ dir_direc[ 1 ] + ", "+
                  message +"\n";
            break;
         default:
            continue;
      }
      if(interactive(thing) && query_verb() == "shout") {
        text = thing->colour_event("shout", "") + text + "%^RESET%^";
      }
      thing->add_message( "$I$5="+ text, ({ }) );
   }
}
void npc_hear_shouts(object newlistener) {
  int i;
  if (member_array(newlistener,_listeners)!=-1) {
     return;
  }
  i = member_array(0,_listeners);
  if (i != -1) {
    _listeners[i]=newlistener;
  } else {
    _listeners=_listeners+({newlistener});
  }
}
int npc_unhear_shouts(object oldlistener) {
  int i;
  if (sizeof(_listeners)==0) {
    return 0;
  }
  i = member_array(oldlistener,_listeners);
  if (i == -1) {
    return 0;
  }
  _listeners = _listeners[0..i] + _listeners[i+1..];
  return 1;
}
void npc_shout_event( object shouter, string start, string message,
      string lang, int *coord, int range ) {
  if (_listeners) {
    _listeners -= ({ 0 });
    _listeners->event_person_shout(shouter, start, message,
                                  lang, coord, range );
  }
}
void add_object_to_channel(string channel_name,
                           object ob) {
   if (!_channels[channel_name]) {
      _channels[channel_name] = ({ });
   }
   _channels[channel_name] += ({ ob });
}
int remove_object_from_channel(string channel_name,
                               object ob) {
   if (_channels[channel_name]) {
      if (member_array(ob, _channels[channel_name]) != -1) {
         _channels[channel_name] -= ({ ob });
         if (!sizeof(_channels[channel_name])) {
           map_delete(_channels, channel_name);
         }
         return 1;
      }
   }
   return 0;
}
void broadcast_to_channel(mixed ob,
                          string channel,
                          mixed message) {
   string str;
   if (!ob) {
      return ;
   }
   if (objectp(ob)) {
      str = ob->query_cap_name();
   }
   if (_channels[channel]) {
      _channels[channel] -= ({ 0 });
      _channels[channel]->event_channel_message(ob, channel, message);
      if (!_channel_history[channel]) {
         _channel_history[channel] = ({ });
      }
      _channel_history[channel] += ({ ({ str, message, time() }) });
      if (sizeof(_channel_history[channel]) > BROADCAST_HISTORY_LENGTH) {
         _channel_history[channel] = _channel_history[channel][1..];
      }
   }
}
mixed *query_channel_history(string channel) {
   return _channel_history[channel];
}
object *query_channel_members(string channel) {
   return _channels[channel];
}
int is_channel(string channel) {
  return !undefinedp(_channels[channel]);
}
mapping query_all_channels() {
   return _channels;
}
int query_next_channel_number(string channel) {
   int next_num;
   next_num = ++_channel_ids[channel];
   save_me();
   return next_num;
}
private void save_me() {
   unguarded( (: save_object(SAVE_FILE) :) );
}
private void load_me() {
   unguarded( (: restore_object(SAVE_FILE, 1) :) );
}
mapping query_dynamic_auto_load() {
   return ([ "channels" : _channels,
       "history" : _channel_history ]);
}
void init_dynamic_arg(mapping arg) {
   _channels = arg["channels"];
   if (!_channels) {
      _channels = ([ ]);
   }
   _channel_history = arg["history"];
   if (!_channel_history) {
      _channel_history = ([ ]);
   }
}