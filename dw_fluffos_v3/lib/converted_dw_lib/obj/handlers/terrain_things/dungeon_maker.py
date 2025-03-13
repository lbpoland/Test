# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/terrain_things/dungeon_maker.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "box" )
            set_short( "green box" )
            add_adjective( "green" )
            set_long( "This is a green box.  It's quite featureless but, strangely "+
            "enough, something tells you it's a dungeon generator.\n" )
            reset_get()
            start = allocate( 3 )
            passages = [})
            room_entries = [})


    def dest_me(self, ) -> None:
            if ( easel )
            easel.dest_me()
            ::dest_me()


    def set_junction_clearance(self, args: Any) -> None:
            int i
            clear = allocate( sizeof( args ) )
            for ( i = 0; i < sizeof( args ); i++ )
            clear[ i ] = to_int( args[ i ] )


    def set_continue_probabilities(self, args: Any) -> None:
            int i
            c_probs = allocate( sizeof( args ) )
            for ( i = 0; i < sizeof( args ); i++ )
            c_probs[ i ] = to_int( args[ i ] )


    def set_passage_probabilities(self, args: Any) -> None:
            int i
            p_probs = allocate( sizeof( args ) )
            for ( i = 0; i < sizeof( args ); i++ )
            p_probs[ i ] = to_int( args[ i ] )


    def set_room_probabilities(self, args: Any) -> None:
            int i
            r_probs = allocate( sizeof( args ) )
            for ( i = 0; i < sizeof( args ); i++ )
            r_probs[ i ] = to_int( args[ i ] )


    def set_start_co_ord(self, args: Any) -> None:
            int i
            if ( sizeof( args ) != 3 )
            return
            for ( i = 0; i < sizeof( args ); i++ )
            start[ i ] = to_int( args[ i ] )


    def init(self, ) -> None:
            add_command( "generate", "<word'terrainname'>", (:do_generate($4[0]):))


    def mark_passage(self, co_ord: int) -> None:
            easel.add_shape( [( co_ord[ 1 ] - start[ 1 ] ) / size,
            ( start[ 0 ] - co_ord[ 0 ] ) / size], ["#"] )


    def mark_room(self, co_ord: int, room: str) -> None:
            int width
            width = (int)room.query_room_size()
            easel.add_shape( [( co_ord[ 1 ] - start[ 1 ] - width - size / 2 ) / size,
            ( start[ 0 ] - co_ord[ 0 ] - width - size / 2 ) / size],
            (string *)easel.make_block( ( 2 * width ) / size + 2 ) )


    def do_generate(self, word: str) -> int:
            int i
            string data, direc, *lines
            mixed *parameters
            if ( easel )
            return notify_fail( "The generator is working on "+
            terrain_name +".\n" )
            if ( file_size( word ) < 0 )
            return notify_fail( "File "+ word +" does not exist.\n" )
            lines = explode( read_file( word ), "\n" )
            for ( i = 0; i < sizeof( lines ); i++ ) {
            if ( lines[ i ] == "" )
            continue
            if ( lines[ i ][ 0 .. 0 ] == "#" )
            continue
            parameters = explode( lines[ i ], " " )
            if ( !stringp( parameters[ 0 ] ) ) {
            printf( "%s line %d: %O is not a string.\n", word, i,
            parameters[ 0 ] )
            continue


    def stop_working(self, ) -> None:
            tell_room( environment(), "The box stops humming as it extrudes an "+
            "easel from a slot in one side.\n" )
            easel.add_shape( [0, 0], ["@"] )
            write_file( "/open/"+ terrain_name +".map",
            implode( (string *)easel.query_lines(), "\n" ) )
            easel.move( environment() )
            easel = 0
            passages = [})
            room_entries = [})
            set_long( "This is a green box.  It's quite featureless but, strangely "+
            "enough, something tells you it's a dungeon generator.\n" )


    def process_passages(self, ) -> None:
            int i, j, k, prob, straight, *co_ord, *new_co_ord
            string direc, new_direc, type, new_type
            mixed *last
            if ( !sizeof( passages ) ) {
            tell_room( environment(), "No passages to process.\n" )
            return stop_working()



class Dungeon_maker(MudObject):
