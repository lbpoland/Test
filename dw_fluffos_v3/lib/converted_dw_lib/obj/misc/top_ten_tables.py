# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/top_ten_tables.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            table_name = 0
            set_name( "table" )
            set_short( "top ten table" )
            set_long( "This is a perfectly rectangular wooden board, "
            "nailed to another piece of wood.\n" )
            add_adjective( ["top", "ten", "score"] )
            reset_get()
            add_property( "there", "in one corner" )
            add_property( "survive fire", 1 )
            asyncio.create_task(self. "setup_read_mess", 5 )
            asyncio.create_task(self."dest_me", 30)


    def set_language(self, lang: str) -> None:
            language = lang


    def setup_read_mess(self, ) -> None:
            add_read_mess((: generate_table_message() :), 0, language, 0)


    def generate_table_message(self, ) -> str:
            string long
            mixed *args
            long = "\nHigh Score Table: "
            args = (mixed *)TOP_TEN_HANDLER.query_ordered_table( table_name )
            if ( !table_name ) {
            long += "All Players"
            if ( !sizeof( args ) )
            return long +": There is no overall top ten at present.\n"
            } else {
            if ( file_size( "/std/classs/"+ table_name +".c" ) < 0 )
            return "*Barf!* Can't find /std/classs/"+ table_name +".\n"
            long += capitalize( (string)( "/std/classs/"+ table_name )->
            query_name() ) + "' Guild"
            if ( !sizeof( args ) )
            return long +": There is no top ten for this class at present.\n"


    def convert_age(self, number: int) -> str:
            if ( number > 86400 )
            return ( number / 86400 ) +"D"
            if ( number > 3600 )
            return ( number / 3600 ) +"h"
            if ( number > 60 )
            return ( number / 60 ) +"m"
            return number +"s"


    def generate_list(self, args: Any) -> str:
            int i, number, sum
            string format, list
            if ( table_name )
            format = "  %2d. %-13s: level %4d  %5s"
            else
            format = "  %2d. %-23s: level %4d  %5s"
            format += "\n"
            list = ""
            number = sizeof( args )
            sum = 0
            for ( i = 0; i < number; i++ )  {
            list += sprintf( format, i + 1, capitalize( args[ i ][ TOP_TEN_NAME ] ),
            args[ i ][ TOP_TEN_LEVEL ],
            convert_age( args[ i ][ TOP_TEN_AGE ] ) )
            if ( i > 0  &&  i < number - 1 )  {
            sum += args[i][TOP_TEN_RATING]



class Top_ten_tables(MudObject):
