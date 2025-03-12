#include <move_failures.h>
inherit "/std/object";
inherit "/std/basic/holdable";
void create() {
   holdable::create();
   object::create();
}
void dest_me() {
   holdable::dest_me();
   object::dest_me();
}
mixed query_dynamic_auto_load() {
  return ([ "::" : object::query_dynamic_auto_load(),
            "hold" : holdable::query_dynamic_auto_load(),
          ]);
}
void init_dynamic_arg( mapping arg ) {
   if (arg["hold"]) {
      holdable::init_dynamic_arg(arg["hold"], arg["is lit"]);
   }
   ::init_dynamic_arg(arg["::"]);
}
void init_static_arg( mapping map ) {
   if ( !mapp( map ) ) {
      return ;
   }
   if ( map[ "::" ] ) {
      object::init_static_arg( map[ "::" ] );
   }
   holdable::init_static_arg(map["hold"]);
}
mapping int_query_static_auto_load() {
   mapping tmp;
   tmp = object::int_query_static_auto_load();
   return ([ "::" : tmp,
      "hold" : holdable::query_static_auto_load(),
          ]);
}
mapping query_static_auto_load() {
   if ( base_name( this_object() ) == "/obj/holdable" ) {
      return int_query_static_auto_load();
   }
   return 0;
}
varargs int move( mixed ob, string mess1, string mess2 ) {
   int ret;
   ret = holdable::move(ob);
   if (ret != MOVE_OK) {
      return ret;
   }
   return object::move( ob, mess1, mess2 );
}