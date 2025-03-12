#include <weather.h>
#include <tasks.h>
#define INIT_FILE "/obj/gatherables/handler.dat"
class item_data {
    string skill;
    int    difficulty;
    string *season;
    mixed  quant;
    string ob;
}
mapping items = ([ ]);
void create() {
    seteuid("/secure/master"->creator_file(file_name(this_object())));
    items = "/obj/handlers/data"->compile_data(({ INIT_FILE }));
}
mixed query_item( string name ) {
    class item_data h;
    if (!(items[name])) {
        return 0;
    }
    h = (class item_data)items[name];
    return ({ h->skill, h->difficulty, h->season, h->quant, h->ob });
}
void add_item( string name, string skill, int diff,
               string *season, mixed quant, string ob ) {
    class item_data h;
    h = new( class item_data );
    h->skill = skill;
    h->difficulty = diff;
    h->season = season;
    h->quant = quant;
    h->ob = ob;
    items[name] = h;
}
mapping query_items() {
    return items;
}
object *gather_item( string word, object player ) {
object *basket = ({ });
object *matched = ({ });
object item;
mixed  *current_item;
class item_data info;
string temp_name;
int temp_scarcity;
int result;
int quantity;
   if ( !objectp( player ) || !environment( player ) )
      return ({ });
   matched = match_objects_for_existence( word, ({ environment( player ) }) );
   if ( !sizeof( matched ) )
      return ({ });
   foreach( object temp in matched ) {
      if ( environment( temp ) == environment( player ) )
         basket += ({ temp });
      current_item = temp->query_gather();
      temp_name = "";
      temp_scarcity = 0;
      if ( !sizeof( current_item ) )
         continue;
      if ( sizeof( current_item ) != 1 ) {
         error( "When Terano recoded this, he assumed that this array would "
            "only contain one array inside it. This turned out to be "
            "wrong.\n" );
      }
      for ( int x = 0; x < sizeof( current_item[0] ); x = x + 2 ) {
         switch ( current_item[ 0 ][ x ] ) {
           case "item name":
           case "item_name":
                  temp_name = evaluate( current_item[ 0 ][ x+1 ],
               environment( player ), player );
              if ( !stringp( temp_name ) )
                    temp_name = 0;
                  break;
           case "scarcity":
                    temp_scarcity = evaluate(current_item[0][ x+1 ],
                  environment( player ), player, temp_name);
                    if ( !intp( temp_scarcity ) )
                        temp_scarcity = 0;
                    break;
         }
      }
      tell_creator( player, "Started to check for %s.\n", temp_name );
       if ( random( 100 ) >= temp_scarcity) {
         tell_creator( player, "Not found %s due to scarcity (%d).\n",
            temp_name, temp_scarcity );
         continue;
      }
      if (!items[temp_name]) {
         tell_creator( player, "Not found %s due to no info!\n",
            temp_name );
         continue;
        }
      info = items[ temp_name ];
      if ( sizeof( info->season ) ) {
          if (member_array( WEATHER->query_season(), info->season ) == -1) {
         tell_creator( player, "Not found %s: Out of season!\n",
            temp_name );
         continue;
        }
      }
      if ( stringp( info->skill ) && strlen( info->skill ) ) {
         result = TASKER->perform_task( player, info->skill ,info->difficulty, TM_FREE );
      switch( result ) {
         case FAIL:
         case BARF:
            tell_creator( player, "Not found %s: Skillcheck failed!\n",
               temp_name );
            continue;
         case AWARD:
            tell_object(player,
                  "%^YELLOW%^You have learned something new about gathering!%^RESET%^\n" );
         case SUCCEED:
         }
      }
      quantity = evaluate( info->quant, environment( player ), player,
         temp_name );
      if ( !quantity || !intp( quantity ) )
         continue;
      item = clone_object( info->ob );
        if (item->query_continuous()) {
         item->set_amount( quantity );
            basket += ({ item });
        }
        else {
         item->dest_me();
         basket += allocate( quantity, (: clone_object( $(info->ob) ) :) );
      }
      continue;
   }
   return basket;
}