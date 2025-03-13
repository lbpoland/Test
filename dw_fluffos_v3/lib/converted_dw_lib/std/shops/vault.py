# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/vault.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def set_vault_exit(self, direc: str, dest: Any, type: str) -> None:
            _entry = dest
            add_exit(direc, dest, type)
            modify_exit( direc, ["function", "check_done"] )
            modify_exit( direc, ["closed", 1] )


    def init_container(self, person: MudObject) -> MudObject:
            object container
            string owner
            owner = person.query_name()
            container = clone_object( "/obj/cont_save" )
            container.set_max_weight( 1000 )
            container.set_open()
            container.set_stuck( 1 )
            container.set_can_recurse(1)
            container.reset_get()
            container->set_save_file( VAULT_SAVE +_vault_name+ "/"+ owner,
            person )
            if ( !master()->file_exists( VAULT_SAVE +_vault_name+"/"+ owner +".o" ) ) {
            container.add_property( "owner", owner )
            container.do_save()


    def event_enter(self, thing: MudObject, mess: str, from: MudObject) -> None:
            string owner
            if( !userp( thing ) )
            return
            owner = thing.query_name()
            if ( _container ) {
            if((string)_container.query_property( "owner" ) == owner)
            return
            else if(thing.query_creator() &&
            find_player(_container.query_property( "owner" )) &&
            environment(find_player(_container.query_property( "owner" ))) ==
            self)
            return
            else {
            _container.dest_me()
            _container = 0


    def fix_owner(self, owner: str) -> None:
            if (_container) {
            _container.add_property( "owner", owner )
            if(_there) {
            _container.add_property("there", _there)


    def check_done(self, verb: str, thing: MudObject, special: str) -> int:
            if ( thing.query_auto_loading() ) {
            tell_room( self, "The door swings shut.\n" )
            tell_object( thing, "Your vaults's inventory is still being generated.\n"
            "Please wait until it is completed.\n" )
            return notify_fail( "" )


    def event_exit(self, thing: MudObject, message: str, to: MudObject) -> None:
            if(_container && _container.query_property("owner") == thing.query_name()) {
            _container.move("/room/void")
            asyncio.create_task(self.(: _container.dest_me() :), 1)


    def query_quit_handler(self, ) -> str:
            return _entry


    def setup_container(self, container: MudObject) -> None:
            container.set_name( "drawer" )
            container.set_short( "drawer" )
            container.add_alias( "drawer" )
            container->set_long("The single open drawer is sticking straight "
            "out of the wall like...  well, like a drawer sticking "
            "straight out of the wall.  " )


    def trap_action(self, str: str) -> int:
            string st1
            if( sscanf( str,"%s %s", str, st1 ) )
            switch(str) {
            case "circle":
            tell_object( this_player(),
            "Something tells you that drawing a circle in this location "
            "would be a bad idea.\n")
            return 1
            case "erect":
            tell_object( this_player(),
            "You can't seem to get the tent to unfold properly.  "
            "Perhaps you should try it somewhere else.\n")
            return 1
            default:
            return 0


    def event_net_dead(self, ob: MudObject) -> None:
            ob.move_with_look(_entry)


    def init(self, ) -> None:
            ::init()
            this_player()->command_override( (: trap_action :) )


    def query_vault_room(self, ) -> int:
            return 1



class Vault(MudObject):
