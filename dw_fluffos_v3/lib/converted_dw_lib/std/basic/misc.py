# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/basic/misc.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.weight = 1
            self.value_info = ([ ])


    def adjust_weight(self, w: int) -> None:
            if (environment()) {
            environment()->add_weight(w)


    def set_weight(self, w: int) -> None:
            if (environment())
            environment()->add_weight(w-weight)
            weight = w


    def query_complete_weight(self, {: Any) -> int:
            varargs int adjust_money(mixed amt, string coin) {
            if (pointerp(amt)) {
            value += (int)MONEY_HAND.query_total_value(amt)
            if (value < 0) {
            value = 0


    def adjust_value(self, i: int) -> int:
            value += i
            return value


    def query_money(self, type: str) -> int:
            int i
            mixed *m_a
            m_a = (mixed *)MONEY_HAND.create_money_array(value)
            i = m_a.index(type) if type in m_a else -1
            if (i == -1) {
            return 0


    def set_value_info(self, word: str, number: int) -> None:
            value_info[ word ] = number


    def remove_value_info(self, word: str) -> None:
            if ( undefinedp( value_info[ word ] ) )
            return
            value_info = m_delete( value_info, word )


    def query_base_value(self, ) -> int:
            return value


    def query_value_at(self, place: MudObject) -> int:
            int i, total
            string *info
            mixed how
            if ( !value_info ) {
            value_info = ([ ])


    def query_value_real(self, place: str) -> int:
            int i
            int total
            string *info
            if ( !value_info ) {
            value_info = ([ ])


    def dest_me(self, ) -> None:
            if ( environment() ) {
            environment()->add_weight( -(int)self.query_complete_weight() )
            if ( query_my_light() )
            adjust_light( -query_my_light() )


    def check_log_status(self, parray: MudObject) -> None:
            if ( self.query_property( WATCH_DEFINE ) &&
            clonep( self ) &&
            arrayp( parray ) &&
            parray.index(load_object("/secure/cmds/creator/cl_one")) if load_object("/secure/cmds/creator/cl_one") in parray else -1 != -1){
            log_file( "WATCH", "%s TO: %s. TP: %s.\n", ctime(time()),
            base_name( self ), parray[2]->query_name() )
            self.add_property( "CT", time() )
            user_event( "inform", sprintf( "[Restricted] %s cloned %s.",
            parray[2]->query_cap_name(),
            base_name( self ) ), "cheat" )



class Misc(MudObject):

    weight = 1

    value_info = '([ ])'
