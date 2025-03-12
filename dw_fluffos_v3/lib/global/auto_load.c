#include <move_failures.h>
#include <virtual.h>
#include <player.h>
#define AUTO_STR_LENGTH 3
#define AUTO_LOAD_TYPE 0
#define AUTO_LOAD_NAME 1
#define AUTO_LOAD_DATA 2
#define AUTO_LOAD_STATIC_ARG  0
#define AUTO_LOAD_DYNAMIC_ARG 1
private mixed auto_load;
private nosave int _no_calls;
private nosave function _finished;
private void auto_clone_alt( object thing, mixed *load_info,
                     object dest, object tell_pl, function move_f, string name);
private object *int_auto_load(int type, string name, mixed *load_info,
                              object dest, object tell_pl, int now,
                              function move_f);
private void move_to_destination(object thing, object dest, object tell_pl,
                                 function move_f);
string *fragile_auto_str_ob(object ob) {
   mixed static_arg;
   mixed dynamic_arg;
   string fname;
   static_arg = ob->query_static_auto_load();
   dynamic_arg = ob->query_dynamic_auto_load();
   if (!static_arg && !dynamic_arg) {
      return ({ });
   }
   if ( sscanf( file_name( ob ), "%s#%*d", fname) == 2 ) {
      return  ({ 1, fname, ({ static_arg, dynamic_arg }) });
   } else {
      return ({ 0, file_name(ob), ({ static_arg, dynamic_arg }) });
   }
}
private string *auto_str_ob(object ob) {
   string static_arg;
   string dynamic_arg;
   string catch_static;
   string catch_dynamic;
   string fname;
   int value;
   string ob_name;
   mixed* tmp;
   catch_static = catch(static_arg = (string)ob->query_static_auto_load());
   catch_dynamic = catch(dynamic_arg = (string)ob->query_dynamic_auto_load());
   if (!static_arg && !dynamic_arg) {
      if (catch_static || catch_dynamic) {
         catch(value = ob->query_value());
         ob_name = "unknown object";
         catch(ob_name = ob->short(1));
         catch(PLAYER_RECEIPT->set_object(file_name(ob)));
         PLAYER_RECEIPT->set_obname(ob_name);
         PLAYER_RECEIPT->set_value(value);
         catch(PLAYER_RECEIPT->set_static_data(({ static_arg, dynamic_arg })));
         tmp = fragile_auto_str_ob(find_object("/obj/misc/al_receipt"));
         tmp[0] = 1;
         if (!undefinedp(tmp[2][1]["::"]["cloned by"])) {
           tmp[2][1]["::"]["cloned by"] = "greco";
         }
      } else {
         tmp = ({ });
      }
      return tmp;
   }
   if ( sscanf( file_name( ob ), "%s#%*d", fname ) == 2 ) {
      return  ({ 1, fname, ({ static_arg, dynamic_arg }) });
   } else {
      return ({ 0, file_name( ob ), ({ static_arg, dynamic_arg }) });
   }
}
string *create_auto_load(object *obs, int into_array) {
  int i;
  string *tmp;
  string *al_tmp;
  if (into_array) {
    auto_load = ({ });
  } else {
    tmp = ({ });
  }
  for (i = sizeof(obs) - 1; i >= 0; i--) {
    reset_eval_cost();
    if (!objectp(obs[i])) {
       continue;
    }
    if (!catch(al_tmp = auto_str_ob(obs[i]))) {
      if (into_array) {
         auto_load += al_tmp;
      } else {
         tmp += al_tmp;
      }
    }
  }
  return tmp;
}
void load_auto_load_alt( mixed *auto_string, object dest,
                                   object tell_pl, function finished) {
   int i;
   reset_eval_cost();
   if ( !auto_string || !sizeof( auto_string ) ) {
      return;
   }
   if ( !pointerp( auto_string ) ) {
      return;
   }
   if ( ( dest == this_object() ) &&
        ( tell_pl == this_object() ) &&
        !this_object()->query_no_check() ) {
      this_object()->set_no_check( 1 );
      this_object()->set_max_weight( 100 + this_object()->query_max_weight() );
   }
   _finished = finished;
   reset_eval_cost();
   for ( i = 0; i < sizeof( auto_string ); i += AUTO_STR_LENGTH) {
      _no_calls++;
      call_out( (: int_auto_load :), i / 6,
                                     auto_string[ i + AUTO_LOAD_TYPE ],
                                     auto_string[ i + AUTO_LOAD_NAME ],
                                     auto_string[ i + AUTO_LOAD_DATA ],
                                     dest, tell_pl, 0, (: $1->move($2) :));
   }
}
object *load_auto_load_to_array( mixed *auto_string, object tell_pl ) {
   object *obs;
   int i;
   obs = ({ });
   if (!tell_pl) {
      tell_pl = this_player();
   }
   if (!tell_pl) {
      tell_pl = this_object();
   }
   for ( i = 0; i < sizeof( auto_string ); i += AUTO_STR_LENGTH) {
      _no_calls++;
      obs += int_auto_load(auto_string[ i + AUTO_LOAD_TYPE ],
                           auto_string[ i + AUTO_LOAD_NAME ],
                           auto_string[ i + AUTO_LOAD_DATA ],
                           0, tell_pl, 1, (: MOVE_OK :));
   }
   return obs - ({ 0 });
}
void load_auto_load_to_inventory(mixed *auto_string, object dest,
                                 object tell_pl, function move_f) {
   int i;
   if (!tell_pl) {
      tell_pl = this_player();
   }
   if (!tell_pl) {
      tell_pl = this_object();
   }
   for ( i = 0; i < sizeof( auto_string ); i += AUTO_STR_LENGTH) {
      _no_calls++;
      int_auto_load(auto_string[ i + AUTO_LOAD_TYPE ],
                    auto_string[ i + AUTO_LOAD_NAME ],
                    auto_string[ i + AUTO_LOAD_DATA ],
                    dest, tell_pl, 0, move_f);
   }
}
private object create_auto_load_object( string name,
                                        mixed *load_info,  object dest,
                                        object tell_pl, function move_f) {
   object thing;
   catch(name = (string)CLONER->other_file( name ));
   if ( !catch( thing = (object)CLONER->clone( name ) ) ) {
      if ( thing ) {
         if ( base_name( thing ) == name ) {
            auto_clone_alt(thing, load_info, dest, tell_pl, move_f, name);
         } else {
            move_to_destination(thing, dest, tell_pl, move_f);
         }
      } else {
  tell_object( tell_pl, "%^RED%^Could not clone "+ name +
         ".%^RESET%^\n" );
  thing = clone_object( PLAYER_RECEIPT );
  thing->set_object( name );
  thing->set_static_save( load_info );
  move_to_destination(thing, dest, tell_pl, move_f);
      }
   } else {
      tell_object( tell_pl, "%^RED%^Error in loading "+ name +
       ".%^RESET%^\n" );
      thing = clone_object( PLAYER_RECEIPT );
      thing->set_object( name );
      thing->set_static_save( load_info );
      move_to_destination(thing, dest, tell_pl, move_f);
   }
   return thing;
}
private object *int_auto_load(int type, string name, mixed *load_info,
                              object dest, object tell_pl, int now,
                              function move_f) {
   object thing;
   object new_thing;
   mixed *stuff;
   int reduce;
   _no_calls--;
   if ( type ) {
      thing = create_auto_load_object(name, load_info, dest, tell_pl, move_f);
      if ( name == PLAYER_RECEIPT) {
         stuff = thing->query_static_save();
         if (stuff) {
            new_thing = create_auto_load_object(name, load_info, dest,
                                         tell_pl, move_f);
            if (new_thing) {
               thing->dest_me();
               thing = new_thing;
            }
         }
      }
   } else {
      if ( !find_object( name ) ) {
         if ( !catch( load_object( name ) ) ) {
            thing = find_object( name );
            if ( thing ) {
               auto_clone_alt(thing, load_info, dest, tell_pl, move_f, name);
            } else {
               tell_object( tell_pl, "%^RED%^Could not load "+ name +
          ".%^RESET%^\n" );
            }
         } else {
            tell_object( tell_pl, "%^RED%^Error in loading "+ name +
       ".%^RESET%^\n" );
         }
      } else {
         tell_object( tell_pl, "%^RED%^Object "+ name +
          " exists.%^RESET%^\n" );
      }
   }
   if (_no_calls == 0 && _finished) {
      evaluate(_finished, this_object());
      _finished = 0;
      this_object()->set_no_check( 0 );
      reduce = (int)this_object()->query_max_weight() -
             (int)this_object()->query_loc_weight();
      if ( reduce > 1 ) {
         if ( reduce > 100 ) {
            reduce = 100;
         }
         this_object()->set_max_weight( (int)this_object()->query_max_weight() -
                                 reduce );
      }
      this_object()->calc_burden();
   }
   if (thing) {
      return ({ thing });
   }
   return ({ });
}
private string ident( object thing ) {
   mixed word;
   catch(word = (string)thing->query_short());
   if ( stringp( word ) ) {
      return "\""+ word +"\"";
   }
   return file_name( thing );
}
private void auto_clone_alt( object thing, mixed *load_info,
                     object dest, object tell_pl, function move_f, string name) {
   string ob_path;
   reset_eval_cost();
   if ( load_info[ AUTO_LOAD_STATIC_ARG ] ) {
      catch( thing->init_static_arg( load_info[ AUTO_LOAD_STATIC_ARG ],
                                     tell_pl ) );
   }
   catch( thing->set_player( tell_pl ) );
   if ( load_info[ AUTO_LOAD_DYNAMIC_ARG ] ) {
      catch( thing->init_dynamic_arg( load_info[ AUTO_LOAD_DYNAMIC_ARG ],
                                      tell_pl ));
   }
   ob_path = thing->query_property(VIRTUAL_NAME_PROP);
   if (ob_path) {
      ob_path = CLONER->other_file( ob_path );
      if (file_size(ob_path) < 0) {
         thing->dest_me();
         thing = clone_object( PLAYER_RECEIPT );
         thing->set_object( name );
         thing->set_static_save( load_info );
         thing->set_virtobname( ob_path );
      } else {
         thing->add_property(VIRTUAL_NAME_PROP, ob_path);
      }
   }
   ob_path = CLONER->illegal_thing(base_name(thing), thing->query_short());
   if(ob_path) {
     thing->dest_me();
     thing = clone_object( ob_path );
   }
   move_to_destination(thing, dest, tell_pl, move_f);
}
private void move_to_destination(object thing, object dest, object tell_pl,
                                 function move_f) {
   object place;
   int ret_val;
   string catch_str;
   place = dest;
   ret_val = MOVE_OK - 1;
   while ( place && ret_val != MOVE_OK) {
      catch_str = catch( ret_val =  evaluate(move_f, thing, place ) );
      if(catch_str) {
        tell_object(tell_pl, "%^RED%^Error moving object: " + catch_str +
        ".%^RESET%^\n");
        ret_val = MOVE_OK - 1;
      }
      if (ret_val != MOVE_OK) {
         if ( environment( place ) ) {
            tell_object( tell_pl, "%^RED%^Cannot move "+ ident( thing ) +
       " into "+
       ident( place ) +" (move returned " +
                         catch_str + "); attempting to move it into "+
                  ident( environment( place ) ) +".%^RESET%^\n" );
            place = environment( place );
         } else if ( ( place != environment(tell_pl) ) &&
                     environment( tell_pl ) ) {
            tell_object( tell_pl, "%^RED%^Cannot move "+ ident( thing ) +
       " into "+
       ident( place ) +" (move returned " +
                         ret_val + "); attempting to move it into "
       "environment of " + tell_pl->query_name() +
       ".%^RESET%^\n" );
            place = environment( tell_pl );
         } else  if (place != find_object("/room/broken")) {
            tell_object( tell_pl, "%^RED%^Cannot move "+ ident( thing ) +
       " into "+
       ident( place ) +" (move returned " + ret_val +
                         "); moving it to the room for broken objects "+
                         "--- please ask a creator for help.%^RESET%^\n" );
            load_object("/room/broken");
            place = find_object( "/room/broken" );
         } else {
            tell_object( tell_pl, "%^RED%^Cannot move "+ ident( thing ) +
       " into "+
       " the room for broken objects "+
       "--- This is a serious errror!  Please tell a "
       "creator immediately.%^RESET%^\n");
            place = 0;
         }
         move_f = (: $1->move($2) :);
      }
   }
}
int query_auto_loading() {
   return _no_calls > 0;
}
protected mixed query_auto_load_string() {
   return auto_load;
}
protected void set_auto_load_string(mixed str) {
   auto_load = str;
}