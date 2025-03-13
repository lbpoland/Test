# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/basic/cute_look.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def there_check(self, ob): MudObject) -> Any:
            varargs string query_contents( string start, object *things,
            int ignore_living) {
            object *livings = [}), *non_livings = [})
            mixed *bits
            string return_string = ""
            int partys
            if( undefinedp( ignore_living ) )
            ignore_living = ignore_livings_in_inventory()
            if ( stringp( start ) ) return_string = start
            if ( !arrayp( things ) ) {
            things = self.find_inv_match( "", this_player() )
            things -= [this_player()]
            things = filter_array( things, "env_check", self)


    def process_non_living(self, non_livings: MudObject, start: int) -> str:
            mapping positions
            string position
            object *items, item, *bulk
            string here
            string *room_items
            int i
            if(!sizeof(non_livings))
            return ""
            here = self.query_property( "here" )
            if (!here)
            return query_multiple_short( non_livings ) + ".\n"
            positions = unique_mapping( non_livings, "there_check", self)
            if ( positions[ 0 ] ) {
            positions[ here ] = positions[ 0 ]
            map_delete( positions, 0 )


    def query_last(self, ) -> int:
            log_file( "CUTELAST", "(%s) %s called query_last.\n",
            ctime( time() ), file_name( self ) )
            return 0


    def adjust_last(self, wibble: int) -> None:
            log_file( "CUTELAST", "(%s) %s called adjust_last.\n",
            ctime( time() ), file_name( self ) )
            return


    def set_ignore_livings_in_inventory(self, ignore: int) -> None:
            _ignore_livings = !!ignore



class Cute_look(MudObject):
