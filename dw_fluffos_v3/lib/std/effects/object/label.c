#include <effect.h>
int query_indefinite() { return 1; }
object create_store(mapping map,
                    object player) {
   object store;
   store = clone_object( "/std/container" );
   if ( objectp( player ) ) {
      store->set_player( player );
   }
   if ( mapp( map ) ) {
      store->init_dynamic_arg( map );
   }
   return store;
}
string query_classification() { return "object.label"; }
mixed* beginning( object thing, object label, int id ) {
   object store;
   store = clone_object( "/std/container" );
   label->move( store );
   thing->add_extra_look( file_name(this_object()) );
   return ({ store, store->query_dynamic_auto_load() });
}
mixed* merge_effect( object thing, mixed* store, object label, int id ) {
   if (!store) {
      store = ({ 0, ([ ]) });
   }
   if (mapp(store)) {
      store = ({ 0, store });
   }
   if ( !store[0] ) {
      store[0] = create_store(store[1], environment(thing));
   }
   label->move( store[0] );
   store[1] = store[0]->query_dynamic_auto_load();
   return store;
}
void end( object thing, mixed* store, int id ) {
  int i;
  if (arrayp(store)) {
    for(i=0; i<sizeof(store); i++)
      if(objectp(store[i]))
         store[i]->dest_me();
  } else if(objectp(store))
    store->dest_me();
   thing->remove_extra_look( this_object() );
}
mixed* restart( object thing, mixed stuff, int id ) {
   object player;
   object store;
   mapping map;
   int enum;
   if (mapp(stuff)) {
      map = stuff;
   } else if (stuff) {
      map = stuff[1];
   } else {
      map = ([ ]);
   }
   player = environment( thing );
   thing->add_extra_look( file_name(this_object()) );
   store = create_store(map, environment(thing));
   enum = thing->sid_to_enum(id);
   thing->set_arg_of(enum, ({ store, map }));
}
string extra_look( object thing ) {
   int *enums;
   object store;
   object *labels;
   mixed *bing;
   enums = (int *)thing->effects_matching( "object.label" );
   if ( !sizeof( enums ) ) {
      return "";
   }
   bing = thing->arg_of( enums[ 0 ] );
   if (pointerp(bing)) {
      store = bing[0];
      if (!store) {
         store = create_store(bing[1], environment(thing));
         thing->set_arg_of(enums[0], ({ store, bing[1] }));
      }
   }
   if ( !objectp( store ) ) {
      return "";
   }
   labels = (object *)store->find_inv_match( "" );
   if ( !sizeof( labels ) ) {
      return "";
   }
   return capitalize( (string)thing->query_pronoun() ) +" has "+
         query_multiple_short( labels ) +" stuck on "+
         (string)thing->query_objective() +".\n";
}