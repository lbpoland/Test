# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/admin/room/quest_room.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            int
            do_create( string quest )
            {
            if ( !quest )
            {
            write( "Syntax is: create <quest>, where <quest> will be the name of "
            + "the new quest.\n" )
            return 1


    def do_list(self, ) -> int:
            int i
            string list
            mixed *names
            if(!"/secure/master"->query_lord( geteuid( this_player() ) ))
            return 1
            list = "These are the Faerûnworld quests:\n\n"
            names = (mixed *)QUEST_HANDLER.query_quest_names()
            for ( i = 0; i < sizeof( names ); i++ ) {
            list += "Quest "+ ( i + 1 ) +"  \""+ names[ i ] +"\", level "+
            (int)QUEST_HANDLER.query_quest_level( names[ i ] ) +"\n    title: "+
            (string)QUEST_HANDLER.query_quest_title( names[ i ] ) +"\n    story: "+
            (string)QUEST_HANDLER.query_quest_story( names[ i ] ) +"\n"
            if ( i < sizeof( names ) - 1 )
            list += "\n"


    def remove_quest(self, answer: str) -> None:
            answer = lower_case( answer )
            if ( answer == "y" )
            {
            if ( QUEST_HANDLER.delete_quest( old_quest ) )
            tell_room( self , "Quest \"" + old_quest
            + "\" deleted.\n" )
            else
            tell_room( self , "Quest \"" + old_quest + "\" was not "
            + "deleted.\n" )
            return



class Quest_room(MudObject):
