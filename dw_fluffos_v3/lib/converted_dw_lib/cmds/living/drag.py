# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/living/drag.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, indirect_obs: MudObject, direction: str) -> Any:
            string owner
            object owner_ob
            string *words, word
            if( this_player()->query_property( "dead" ) )
            return add_failed_mess( "You're dead.  You can't drag anything.\n" )
            if( objectp( (object)this_player()->query_dragging() ) )
            return add_failed_mess( "You're already dragging something.\n" )
            if( sizeof( indirect_obs ) > 1 )
            return add_failed_mess( "You can only drag one thing at a time.\n" )
            if( indirect_obs[0] == this_player() )
            return add_failed_mess( "You try and drag yourself away from the keyboard, "
            "but you cannot.  Oh no!\n")
            if( living( indirect_obs[ 0 ] ) ) {
            if( !indirect_obs[ 0 ]->query_property( PASSED_OUT_PROP )
            || pk_check( indirect_obs[ 0 ], this_player() ) )
            return add_failed_mess( (string)indirect_obs[ 0 ]->the_short() +
            " doesn't want to be dragged away, thank you very much.\n" )
            } else
            if( base_name(indirect_obs[0]) == "/obj/corpse" ) {
            owner = indirect_obs[ 0 ]->query_owner()
            words = explode( lower_case( owner ),  " " )
            words = filter( words, (: PLAYER_HANDLER.test_user($1) :) )
            foreach( word in words ) {
            owner_ob = find_player( lower_case( word ) )
            if( owner_ob && userp( owner_ob ) &&
            pk_check( owner_ob, this_player() ) &&
            member_array ( this_player()->query_name(), indirect_obs[0]->
            query_permitted() ) == -1 )
            return add_failed_mess( "For some reason, you can't get hold of "+
            (string)indirect_obs[ 0 ]->the_short() +".\n" )



class Drag(MudObject):
