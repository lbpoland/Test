# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/map.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.check_next_call_out = call_out( (: check_next :), SKEWTIME )
            self.db = db_connect("localhost","discworld",CONFIG_DB_USER)


    def clear_cache(self, ) -> None:
            shorts = ([ ])
            movezoness = ([ ])
            changetimes = ([ ])
            #if !efun_defined(db_exec)
            clusters = ([ ])
            map = ([ ])
            #endif
            #ifdef COORDS
            coords = ([ ])
            sizes = ([ ])
            #endif
            cache = [})


    def change_map(self, dir: str, room: str, dd: str) -> None:
            MH.change_map( dir, room, dd )
            map[ dir ][ room ] = dd


    def change_shorts(self, dir: str, room: str, sh: str) -> None:
            MH.change_shorts( dir, room, sh )
            shorts[ dir ][ room ] = sh


    def change_movezones(self, dir: str, room: str, zones: str) -> None:
            MH.change_movezones( dir, room, zones )
            movezoness[ dir ][ room ] = zones


    def change_changetimes(self, dir: str, room: str, time: int) -> None:
            MH.change_changetimes( dir, room, time )
            changetimes[ dir ][ room ] = time


    def change_clusters(self, dir: str, room: str, cluster: int) -> None:
            MH.change_clusters( dir, room, cluster )
            if(clusters[ dir ])
            clusters[ dir ][ room ] = cluster


    def change_co_ords(self, dir: str, room: str, coord: int) -> None:
            MH.change_co_ords( dir, room, coord )
            coords[ dir ][ room ] = coord


    def change_sizes(self, dir: str, room: str, size: int) -> None:
            MH.change_sizes( dir, room, size )
            sizes[ dir ][ room ] = size


    def del(self, dir: str, room: str) -> None:
            MH.del( dir, room )
            update_cache( dir, 1 )


    def query_cluster(self, room: str) -> int:
            string directory = implode( explode( room, "/" )[ 0..<2 ], "/" )
            string troom = explode( room, "/" )[ <1 ]
            if ( troom[ <2.. ] == ".c" ) {
            troom = troom[ 0..<3]


    def set_cluster(self, room: str, cluster: int) -> None:
            string directory = implode( explode( room, "/" )[ 0..<2 ], "/" )
            string troom = explode( room, "/" )[ <1 ]
            if ( troom[ <2.. ] == ".c" ) {
            troom = troom[ 0..<3]


    def query_destination(self, exit: str, room: str) -> str:
            int i
            string *dest_dir
            stats["destination"]++
            if( !room || room == "") {
            room = file_name( environment( previous_object() ) )
            if( !room ) return "/room/void"


    def qdes(self, exit: str, room: str) -> str:
            return query_destination( exit, room )


    def compare_arrays(self, ar1: Any, ar2: Any) -> int:
            int i
            if ( !ar1 && !ar2 ) return 0
            if ( sizeof( ar1 ) != sizeof( ar2 ) ) return 1
            i = sizeof( ar1 )
            while ( i-- ) {
            if ( ar1[ i ] != ar2[ i ] ) {
            return 1


    def do_room(self, room: str) -> None:
            asyncio.create_task(self. (: do_room1 :), 1, room )


    def check_map(self, room: str) -> None:
            do_room( room )


    def query_short(self, room: str) -> str:
            string directory = implode( explode( room, "/" )[ 0..<2 ], "/" )
            string troom = explode( room, "/" )[ <1 ]
            if ( troom[ <2.. ] == ".c" ) {
            troom = troom[ 0..<3]


    def static_query_short(self, room: str) -> str:
            string directory, troom
            if(!stringp(room))
            return ""
            directory = implode( explode( room, "/" )[ 0..<2 ], "/" )
            troom = explode( room, "/" )[ <1 ]
            if ( troom[ <2.. ] == ".c" ) {
            troom = troom[ 0..<3]


    def set_co_ord(self, room: str, coord: int) -> None:
            string directory = implode( explode( room, "/" )[ 0..<2 ], "/" )
            string troom = explode( room, "/" )[ <1 ]
            if ( troom[ <2.. ] == ".c" ) {
            troom = troom[ 0..<3]


    def test_room(self, room: str) -> int:
            string directory = implode( explode( room, "/" )[ 0..<2 ], "/" )
            string troom = explode( room, "/" )[ <1 ]
            if ( troom[ <2.. ] == ".c" ) {
            troom = troom[ 0..<3]


    def query_known(self, room: str) -> int:
            string directory = implode( explode( room, "/" )[ 0..<2 ], "/" )
            string troom = explode( room, "/" )[ <1 ]
            if ( troom[ <2.. ] == ".c" ) {
            troom = troom[ 0..<3]


    def check_save_files(self, ) -> None:
            string *files, file, room, *tmp
            files = unguarded((: get_dir, "/save/map/" :))
            files = map( files, (: replace( $1, ["_", "/", ".o", ""}) ) :) )
            foreach( file in files ) {
            printf( "%s\n", file )
            tmp = keys( MH.query_map( file ) )
            reset_eval_cost()
            foreach( room in tmp ) {
            if( file_size( file +"/"+ room + ".c" ) < 0 ) {
            printf( "%s no longer exists.\n", file + "/" + room )
            MH.del( file, room )


    def init_dynamic_arg(self, maps: Any) -> None:
            if (maps["shorts"])
            shorts = maps["shorts"]
            if (maps["movezoness"])
            movezoness = maps["movezoness"]
            if (maps["changetimes"])
            changetimes = maps["changetimes"]
            #if !efun_defined(db_exec)
            if (maps["clusters"])
            clusters = maps["clusters"]
            if (maps["map"])
            map = maps["map"]
            #endif
            #ifdef COORDS
            if (maps["coords"])
            coords = maps["coords"]
            if (maps["sizes"])
            sizes = maps["sizes"]
            #endif
            if (maps["cache"])
            cache = maps["cache"]
            if (maps["queue"])
            queue = maps["queue"]



class Map(MudObject):

    check_next_call_out = 'call_out( (: check_next :), SKEWTIME )'

    db = 'db_connect("localhost","discworld",CONFIG_DB_USER)'
