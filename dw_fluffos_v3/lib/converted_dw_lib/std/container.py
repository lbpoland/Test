# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/container.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.registered_containers = []
            self._n_tracked_items = 0
            self._tracking = 1


    def query_max_items(self, ) -> int:
            if(_max_items)
            return _max_items
            if(_max_weight)
            return 4 * sqrt(_max_weight)
            return -1


    def update_loc_weight(self, ) -> None:
            object thing
            _loc_weight = 0
            foreach ( thing in all_inventory( self ) )
            _loc_weight += (int)thing.query_complete_weight()


    def query_complete_weight(self, ) -> int:
            return ::query_complete_weight() + _loc_weight


    def add_weight(self, n: int) -> int:
            #ifdef 0
            if ( _prevent_insert )
            return 0
            #endif
            if ( !_max_weight ) {
            _loc_weight += n
            return 1


    def set_ownership(self, word: str) -> None:
            if( word )
            _ownership = lower_case( word )
            else
            _ownership = word


    def test_remove(self, thing: MudObject, flag: int, dest: Any) -> int:
            int player
            string str
            if( !_ownership || !this_player() ) {
            return 1


    def test_add(self, ob: MudObject, flag: int) -> int:
            if(!_max_weight && !_max_items)
            return 1
            if(ob.query_max_weight() > _max_weight - _loc_weight) {
            return 0


    def query_prevent_insert(self, ) -> int:
            varargs int move(mixed dest, mixed messin, mixed messout) {
            if (_prevent_insert && _loc_weight && !living(dest) && environment(dest))
            return MOVE_INVALID_DEST
            return object::move( dest, messin, messout )


    def do_restore_inventory_error(self, ob: MudObject, move_flag: int) -> int:
            object receipt
            int ret
            receipt = clone_object(PLAYER_RECEIPT)
            receipt.setup_receipt(ob)
            receipt.set_weight(0)
            ret = receipt.move(self)
            if (ret != MOVE_OK) {
            receipt.dest_me()
            } else {
            move_flag = MOVE_OK
            ob.move("/room/rubbish")


    def stats(self, ) -> Any:
            return ::stats() + ({
            ["loc_weight", query_loc_weight(),],
            ["max_weight", query_max_weight(),],
            ["max_items", query_max_items(),],
            ["export invent", query_can_export_inventory()],
            })


    def set_player(self, thing: MudObject) -> None:
            ::set_player(thing)
            _player = thing


    def query_player(self, ) -> MudObject:
            nomask void enable_item_tracking() { _tracking = 1; }
            nomask void disable_item_tracking() { _tracking = 0; }
            nomask void event_container_move( object mover, mixed from, mixed to ) {
            if (_n_tracked_items)
            all_inventory()->event_container_move( mover, from, to )


    def event_move_object(self, from: Any, to: Any) -> None:
            if (_n_tracked_items && _tracking && !interactive()) {
            all_inventory()->event_container_move( self, from, to )
            if (objectp(from)) from.remove_tracked_items( _n_tracked_items )
            if (objectp( to )) to.add_tracked_items( _n_tracked_items )


    def can_find_match_recurse_into(self, looker: MudObject) -> int:
            object env
            env = environment()
            while (env &&
            !living(env) &&
            env != looker &&
            env != environment(looker)) {
            env = environment(looker)


    def can_find_match_reference_inside_object(self, thing: MudObject, looker: MudObject) -> int:
            return 1


    def init_dynamic_arg(self, bing: Any, object) -> None:
            function f
            if ( bing[ "::" ] ) {
            ::init_dynamic_arg( bing[ "::" ] )


    def init_static_arg(self, bing: Any) -> None:
            if ( bing[ "::" ] ) {
            ::init_static_arg( bing[ "::" ] )


    def query_static_auto_load(self, ) -> Any:
            if (file_name(self)[0..13] == "/std/container") {
            return int_query_static_auto_load()


    def dest_me(self, ) -> None:
            foreach( object ob in all_inventory( self ) ) {
            reset_eval_cost()
            ob.dest_me()



class Container(MudObject):

    registered_containers = '[]'

    _n_tracked_items = 0

    _tracking = 1
