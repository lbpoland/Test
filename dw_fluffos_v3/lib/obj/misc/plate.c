inherit "/std/surface";
void init() {
  this_player()->add_command( "eat", this_object(),
    "<indirect:object:direct-obs> {from|on} <direct:object:me>" );
  this_player()->add_command( "eat", this_object(),
    "from <direct:object:me>" );
}
void create() {
  do_setup++;
  ::create();
  do_setup--;
  set_long( "This is a nice plate for keeping food on.\n" );
  if ( ! do_setup ) {
    this_object()->setup();
    this_object()->reset();
  }
}
int do_eat( object *obs, string dir, string indir, mixed *args ) {
  object ob;
  object *food;
  if( sizeof( obs ) )
    food = copy( obs );
  else
    food = all_inventory();
  if( sizeof( food ) ) {
    food = filter( food, (: $1->query_edible() :) );
  } else {
    this_player()->add_failed_mess( this_object(),
      "There's nothing on $D\n", ({ }) );
    return 0;
  }
  if( !sizeof( food ) ) {
    if( sizeof( obs ) )
      this_player()->add_failed_mess( this_object(),
        "You can't eat $I on $D!\n", obs );
    else
      this_player()->add_failed_mess( this_object(),
        "There's nothing edible on $D\n", ({ }) );
    return 0;
  }
  foreach( ob in food ) {
    ob->do_eat();
  }
  return 1;
}
mapping query_static_auto_load() {
  return int_query_static_auto_load();
}