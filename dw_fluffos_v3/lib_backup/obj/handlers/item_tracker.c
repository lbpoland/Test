#include <library.h>
#include <quest_handler.h>
inherit "/std/object";
#define QUEST_INFO_IDENT  "items"
#define MAX_COPIES    10
mapping item_cache;
mapping player_items;
void create()
{
   ::create();
   item_cache = ([ ]);
}
mixed query_item_state( mixed pl_name, mixed item )
{
  if (objectp(pl_name)) {
    if (!interactive(pl_name)) return 0;
    pl_name = pl_name->query_name();
  }
  if (objectp(item)) {
    if (item->query_tracked_item_owner() != pl_name) return 0;
    item = item->query_full_tracked_item_identifier();
  }
  if (!item) return 0;
  player_items = item_cache[ pl_name ];
  if (!player_items) {
    player_items = copy(LIBRARY->query_player_quest_info( pl_name, QUEST_INFO_IDENT ));
    if (!player_items) player_items = ([ ]);
    item_cache[ pl_name ] = player_items;
  }
  return player_items[ item ];
}
int delete_item( mixed pl_name, mixed item )
{
  if (objectp(pl_name)) {
    if (!interactive(pl_name)) return 0;
    pl_name = pl_name->query_name();
  }
  if (objectp(item)) {
    if (item->query_tracked_item_owner() != pl_name) return 0;
    item = item->query_full_tracked_item_identifier();
  }
  if (!item) return 0;
  player_items = item_cache[ pl_name ];
  if (!player_items) {
    player_items = copy(LIBRARY->query_player_quest_info( pl_name, QUEST_INFO_IDENT ));
    if (!player_items) player_items = ([ ]);
    item_cache[ pl_name ] = player_items;
  }
  map_delete( player_items, item );
  return 1;
}
int query_item_copies( mixed pl_name, mixed item )
{
  int copy_number,n_copies;
  if (objectp(pl_name)) {
    if (!interactive(pl_name)) return 0;
    pl_name = pl_name->query_name();
  }
  if (objectp(item)) {
    item = item->query_tracked_item_identifier();
  }
  if (!item) return 0;
  player_items = item_cache[ pl_name ];
  if (!player_items) {
    player_items = copy(LIBRARY->query_player_quest_info( pl_name, QUEST_INFO_IDENT ));
    if (!player_items) player_items = ([ ]);
    item_cache[ pl_name ] = player_items;
  }
  n_copies = 0;
  for (copy_number = 1; copy_number < MAX_COPIES; copy_number++) {
    if (player_items[ item+"/"+copy_number ]) n_copies++;
  }
  return n_copies;
}
int set_item_state( mixed pl_name, mixed item, mixed state )
{
  if (objectp(pl_name)) {
    if (!interactive(pl_name)) return 0;
    pl_name = pl_name->query_name();
  }
  if (objectp(item)) {
    if (item->query_tracked_item_owner() != pl_name) return 0;
    item = item->query_full_tracked_item_identifier();
  }
  if (!item) return 0;
  player_items = item_cache[ pl_name ];
  if (!player_items) {
    player_items = copy(LIBRARY->query_player_quest_info( pl_name, QUEST_INFO_IDENT ));
    if (!player_items) player_items = ([ ]);
    item_cache[ pl_name ] = player_items;
  }
  player_items[ item ] = state;
  return 1;
}
mixed query_all_item_states( mixed pl_name )
{
  if (objectp(pl_name)) {
    if (!interactive(pl_name)) return 0;
    pl_name = pl_name->query_name();
  }
  player_items = item_cache[ pl_name ];
  if (!player_items) {
    player_items = copy(LIBRARY->query_player_quest_info( pl_name, QUEST_INFO_IDENT ));
    if (!player_items) player_items = ([ ]);
    item_cache[ pl_name ] = player_items;
  }
  return player_items;
}
int save_all_item_states( mixed pl_name )
{
  if (objectp(pl_name)) {
    if (!interactive(pl_name)) return 0;
    pl_name = pl_name->query_name();
  }
  player_items = item_cache[ pl_name ];
  if (!player_items) {
    return 0;
  }
  LIBRARY->set_player_quest_info( pl_name, QUEST_INFO_IDENT, player_items );
  return 1;
}
int save_all_item_states_delete_cache( mixed pl_name )
{
  if (objectp(pl_name)) {
    if (!interactive(pl_name)) return 0;
    pl_name = pl_name->query_name();
  }
  player_items = item_cache[ pl_name ];
  if (!player_items) {
    return 0;
  }
  LIBRARY->set_player_quest_info( pl_name, QUEST_INFO_IDENT, player_items );
  map_delete( item_cache, pl_name );
  return 1;
}