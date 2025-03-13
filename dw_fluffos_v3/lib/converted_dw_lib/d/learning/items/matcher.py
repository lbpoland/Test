# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/learning/items/matcher.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "matcher" )
            set_short( "Tannah's pattern matcher" )
            add_property( "determinate", "" )
            add_alias( "pattern matcher" )
            set_long(
            "This is a very handy wossname, useful for testing patterns you "
            "might like to use in an add_command.\n"
            )
            add_adjective( ["handy", "patterned"] )
            set_weight( 1 )
            set_value( 0 )
            add_property( "no recycling", 1 )


    def init(self, ) -> None:
            add_cmds( this_player() )


    def add_cmds(self, player: MudObject) -> None:
            set_read_mess( (: read_msg :) )
            player->add_command( "add", self, "command <word'command'> "
            "with pattern <string:quoted'pattern'>",
            (: do_add( $4[0], $4[1] ) :) )
            player->add_command( "remove", self, "command <number>",
            (: do_remove( $4[0] ) :) )
            if( sizeof( cmds ) ) {
            for( int i = 0; i < sizeof( cmds ); i++ )
            player->add_command( cmds[i][CMD], self, cmds[i][PAT],
            (: do_match :) )


    def do_add(self, command: str, pattern: str) -> int:
            cmds += [[command, pattern]]
            this_player()->remove_object( self, 1 )
            add_cmds( this_player() )
            printf( "You add the command \"%s\" with the pattern \"%s\" to the "
            "pattern matcher.\n", command, pattern )
            return 1


    def do_remove(self, i: int) -> int:
            if( i >= sizeof( cmds ) || i < 0 ) {
            printf( "Invalid command number.\n" )
            return 0


    def read_msg(self, ) -> str:
            int i
            string msg
            msg = "The pattern matcher is currently set to test the following "
            "commands and patterns:\n"
            if( !sizeof( cmds ) ) msg += "  None.\n"
            else for( i = 0; i < sizeof( cmds ); i++ ) {
            msg += sprintf( "[%d] \"%s\", \"%s\"\n", i, cmds[i][CMD],
            cmds[i][PAT] )


    def list_cmds(self, ) -> None:
            printf( "Commands and patterns added:\n%O\n", cmds )



class Matcher(MudObject):
