# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/basic/item_chat.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def init(self, ) -> None:
            check_chat()


    def item_chat(self, args: Any) -> None:
            if ( !args || sizeof(args) < 3 || !sizeof(args[2]) ){
            write( "Incorrect args to item_chat.\n" )
            return


    def chat_on(self, ) -> None:
            _off = 0
            check_chat()


    def chat_off(self, ) -> None:
            _off = 1


    def make_chat(self, ) -> None:
            int saying
            string stuff
            object env, *targets
            _already_added = 0
            if( !(env = environment()) || _off )
            return
            saying = random( sizeof(_chats[ 2 ]) )
            if( saying == _chats[ 3 ] )
            saying = ( saying + 1 ) % sizeof( _chats[ 2 ] )
            _chats[ 3 ] = saying
            stuff = _chats[ 2 ][ saying ]
            if( env.query_is_room() ||
            ( interactive(env) && (env = environment(env)) && env.query_is_room() ) ){
            targets = filter( all_inventory(env), (: interactive($1) :) )
            if( !sizeof(targets) )
            return
            if( stuff[0..0] == "#" )
            call_other( self, stuff[ 1 .. ] )
            else
            tell_room( env, stuff + "\n" )
            _already_added = 1
            ROOM_HANDLER->add_chatter( self, _chats[ 0 ] +
            random( _chats[ 1 ] - _chats[ 0 ] + 1 ) )


    def check_chat(self, ) -> None:
            if( !_off && !_already_added && arrayp(_chats) && environment() ){
            if( interactive(environment()) ||
            ( environment(environment()) &&
            interactive(environment(environment()))
            )
            ){
            _already_added = 1
            ROOM_HANDLER->add_chatter( self,
            ( _chats[ 0 ] + random( _chats[ 1 ] - _chats[ 0 ] + 1 ) ) / 2 )


    def fix_saved_chat(self, chat: str) -> str:
            string old_ob
            if( !chat )
            return 0
            sscanf( chat, "%*s$%*s_short:%s$%*s", old_ob )
            if( old_ob )
            chat = replace( chat, old_ob, file_name(self) )
            return chat


    def init_dynamic_arg(self, map: Any) -> None:
            mixed info
            if( !map )
            return
            if( (info = map["_chats"]) && arrayp(info) && sizeof(info) > 2 ){
            info[2] = map( info[2], "fix_saved_chat", self )
            item_chat( info )



class Item_chat(MudObject):
