# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/state_changer.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def set_skill(self, _skill: str, _base_bonus: int) -> None:
            skill = _skill
            base_bonus = _base_bonus


    def init(self, ) -> None:
            ::init()
            if ( command ) {
            add_command( command, "all in <direct:object>", (: do_action( $1 ) :) )


    def do_action(self, obs: MudObject) -> int:
            int *tmp
            if ( gp_cost ) {
            if ( this_player()->query_specific_gp( gp_type ) < gp_cost )
            return notify_fail( "You are too tired to "+ command +" with the "+ self.the_short() + ".\n" )
            this_player()->adjust_gp( -gp_cost )


    def beginning(self, apparatus: MudObject, tp: MudObject, id: int) -> MudObject:
            apparatus.submit_ee(0, duration, EE_REMOVE)
            apparatus.submit_ee("show_message", [30, 30], EE_CONTINUOUS)
            return tp


    def show_message(self, apparatus: MudObject, tp: MudObject, id: int) -> MudObject:
            if ( stringp( interim_mess ) )
            tell_room(environment(), parse_message(interim_mess) )
            if ( !sizeof( all_inventory() ) )
            submit_ee( 0, 0, EE_REMOVE )
            return tp


    def end(self, apparatus: MudObject, tp: MudObject, id: int) -> MudObject:
            object ob
            int temp
            int l_bonus = base_bonus
            if ( functionp( end_func ) ) {
            if ( !evaluate( end_func ) ) {
            debug_printf( "Stopped at start_func\n" )
            return tp


    def extra_look(self, ob: MudObject) -> str:
            return ""


    def parse_message(self, message: str) -> str:
            message = replace( message, "$inventory$", query_multiple_short( all_inventory() ) )
            debug_printf( "message is: %s.\n" , message )
            return message


    def test_add(self, ob: MudObject, flag: int) -> int:
            debug_printf( "Testing add of: %O (%O) in state changer.\n", ob, environment( ob ) )
            if ( add_list .index( ob) if  ob in add_list  else -1 != -1 ) {
            return ::test_add( ob, flag )


    def test_remove(self, ob: MudObject, flag: int, dest: Any) -> int:
            if ( dest && base_name( dest ) == "/room/rubbish" )
            ::test_remove( ob, flag, dest )
            debug_printf( "Testing remove of: %O (%O) in state changer.\n", ob, environment( ob ) )
            if ( query_busy() ) {
            tell_object( this_player(), "It might not be wise to take anything from "+
            self.the_short() + " while it is in use!\n" )
            return 0


    def long(self, word: str, dark: int) -> str:
            if ( query_busy() ) {
            if ( stringp( running_inv_mess ) )
            return query_long() + parse_message( running_inv_mess )
            else
            return ::long( word, dark )


    def do_empty(self, dest: MudObject, me: str, him: str, prep: str) -> int:
            if ( query_busy() ) {
            add_failed_mess( "You can't empty "+ self.short() +" while it is being used.\n" )
            return 0


    def do_fill(self, to: MudObject, args_b: Any, args_a: Any, args: Any) -> int:
            if ( query_busy() ) {
            add_failed_mess( "You can't fill anything from "+ self.short()
            +" while it is being used.\n" )
            return 0



class State_changer(MudObject):
