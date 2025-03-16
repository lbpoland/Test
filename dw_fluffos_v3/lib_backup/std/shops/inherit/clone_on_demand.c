#include <armoury.h>
#define INFINITE_LEFT 10000
#define MAX_PROP "max per reset"
#define NUM_REMOVED "number removed this reset"
#define REFERENCE "name we are reference by"
#define DISPLAY "display in shop"
nosave object _cont;
nosave string _domain;
void create(){
}
object query_cont(){  return _cont;  }
void check_cont() {
  if (!_cont) {
     _cont = clone_object("/std/container");
     _cont->set_name( "clone_on_demand-store" );
  }
}
void reset() {
  object ob;
  check_cont();
  foreach( ob in all_inventory(_cont) ){
    ob->remove_property(NUM_REMOVED);
  }
}
void set_object_domain(string domain) {
   _domain = domain;
}
string query_object_domain() {
   return _domain;
}
varargs int add_object( string name, int max_per_reset, string display_as ) {
  object ob;
  if(!_cont) {
     _cont = clone_object("/std/container");
     _cont->set_name( "clone_on_demand-store" );
  }
  if (!(ob = this_object()->create_object(name))) {
    if(!ob = clone_object(name)) {
      ob = ARMOURY->request_item(name, 100, _domain);
    }
  }
  if(ob) {
    if (ob->query_decays()) {
      ob->set_decay_speed(0);
    }
    ob->move(_cont);
    if (display_as) {
         ob->add_property( DISPLAY, display_as);
    }
    ob->add_property( REFERENCE, name);
    ob->add_property( MAX_PROP, max_per_reset );
    return 1;
  }
  return 0;
}
int query_num_items_left(object ob) {
   int max;
   int num;
   max = ob->query_property( MAX_PROP );
   num = ob->query_property( NUM_REMOVED );
   if( max ){
     return max - num;
   }
   return INFINITE_LEFT;
}
int query_number_left(string name) {
   object * things;
   things = filter( all_inventory(_cont),
     (: $1->query_short() == $(name) :) );
   if( !sizeof(things) ) {
      return -1;
   }
   return query_num_items_left( things[0] );
}
int * query_items_left( string *names ) {
   if( !names )
      return ({ });
   return map( names, (: query_number_left($1) :) );
}
private void switch_properties(object newone, object original) {
  mixed *extra, *props, prop;
  props = ({ MAX_PROP, NUM_REMOVED, REFERENCE });
  extra = this_object()->switch_extra_properties();
  if( sizeof(extra) )
    props += extra;
  foreach( prop in props ){
    newone->add_property( prop, original->query_property( prop ) );
    original->remove_property( prop );
  }
  if (newone->query_decay_speed()) {
     original->set_decay_speed( newone->query_decay_speed() );
     newone->set_decay_speed(0);
  }
}
protected object create_real_object(object thing) {
   string name;
   object new_thing, *continv, temp_cont;
   int j, max, num;
   name = thing->query_property( REFERENCE );
   if(!name)
     return 0;
   new_thing = this_object()->create_object( name );
   if ( !new_thing )  {
      new_thing = clone_object(name);
   }
   if ( !new_thing )  {
      new_thing = ARMOURY->request_item( name, 80 + random( 20 ), _domain );
   }
  if( new_thing ){
    switch_properties( new_thing, thing );
    continv = all_inventory(_cont);
    j = member_array( thing, continv );
    temp_cont = clone_object("/std/container");
    thing->move("/room/void");
    continv[j] = new_thing;
    new_thing->move(_cont);
      for (j=sizeof(continv)-1;j>=0;j--) {
      continv[j]->move(temp_cont);
      continv[j]->move(_cont);
    }
    temp_cont->dest_me();
    max = new_thing->query_property( MAX_PROP );
    num = new_thing->query_property( NUM_REMOVED );
    if ( max ) {
      new_thing->add_property( NUM_REMOVED, num + 1 );
    }
  }
  return thing;
}
void dest_me(){
  if( _cont )
    _cont->dest_me();
}
varargs int add_armour( string name, int max_per_reset, string display_as ) {
  return add_object(name, max_per_reset, display_as);
}
varargs int add_weapon( string name, int max_per_reset, string display_as ) {
  return add_object(name, max_per_reset, display_as);
}