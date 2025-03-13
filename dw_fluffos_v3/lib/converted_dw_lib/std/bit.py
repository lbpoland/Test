# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/bit.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.corpse_weight = STD_CORPSE_WEIGHT


    def init(self, ) -> None:
            add_command("eat", "<direct:object>")


    def query_edible(self, ) -> int:
            string bit
            if(!race_ob.query_eat(bit_data[BIT_NAME])) {
            return 0


    def do_eat(self, ) -> int:
            if(!query_edible())
            return 0
            move( "/room/rubbish" )
            return 1


    def no_decay(self, ) -> int:
            if( race_ob && bit_data ) {
            return race_ob.query_unrottable(bit_data[BIT_NAME])


    def set_race_ob(self, s: MudObject) -> None:
            race_ob = s


    def set_race_name(self, s: str) -> None:
            race_name = s


    def setup_long(self, ) -> None:
            if ( !bit_data ) {
            return


    def extra_look(self, ) -> str:
            if(sizeof(bits_gone))
            return "It appears to be missing the " + query_multiple_short(bits_gone) + ".\n"
            return ""


    def set_bit(self, s: str, dec: int) -> None:
            int temp
            bit_data = (mixed *)race_ob.query_bit(s)
            if (!bit_data || !sizeof(bit_data)) {
            return


    def do_decay(self, ) -> int:
            int rate
            if (!environment()) {
            move( "/room/rubbish" )
            return 0


    def dest_me(self, ) -> None:
            BIT_CONTROLLER.remove_bit(self)
            ::dest_me()


    def query_static_auto_load(self, ) -> Any:
            return int_query_static_auto_load()


    def query_dynamic_auto_load(self, ) -> Any:
            return [bit_data, race_ob, corpse_weight, race_name,
            decay, cured, bits_gone, ::query_dynamic_auto_load()]


    def init_dynamic_arg(self, arg: Any, object) -> None:
            if (mapp(arg)) {
            ::init_dynamic_arg(arg)
            return


    def do_cure(self, ) -> None:
            if ( cured ) {
            return


    def query_cured(self, ) -> int:
            int *query_vect() { return bit_data[BIT_EXTRA][EXTRA_VALUE]; }
            string *query_possible_bits( string word ) {
            int i, j
            string *possibles
            possibles = [})
            for ( i = sizeof( bits ) - 3; i > -1; i -= 3 ) {
            if ( ( bits[ i ] == word ) ||
            ( bits[ i + 1 ] == word ) ||
            !word) {
            if (arrayp( bits[i+2][2] )) {
            for ( j = 0; j < bits[ i + 2][2][1]; j++ ) {
            possibles += [bits[ i ]]


    def query_bit_left(self, s: str) -> str:
            string *poss_bits
            poss_bits = query_possible_bits(s)
            if (!poss_bits || !sizeof(poss_bits)) {
            return 0


    def make_bit(self, which_bit: str) -> MudObject:
            mixed *bit
            object bitobj
            int i,j
            bit = race_ob.query_bit(which_bit)
            if ((sizeof(bit[2][2]) > 1) && stringp(bit[2][2][1])) {
            bitobj = clone_object( bit[2][2] )
            } else if (bit[2][2] == 0) {
            bitobj = clone_object("/std/bit")
            } else {
            bitobj = clone_object("/std/bit")


    def set_bits_gone(self, bits: str) -> None:
            int i
            bits_gone = [})
            for ( i = 0; i < sizeof( bits ); i++ ) {
            add_bit_gone( bits[ i ] )


    def set_bits(self, ) -> None:
            int i, j
            mixed *these_bits, *all_bits
            bits = [})
            these_bits = bit_data
            all_bits = race_ob.query_bits()
            for (i=3; i<sizeof(these_bits[2]); i++) {
            for (j=0; j<sizeof(all_bits); j = j+3) {
            if ((these_bits[0] == all_bits[j+2][0]) && (these_bits[2][i] == all_bits[j])) {
            bits += all_bits[j..j+2]
            delete(all_bits, j, 2)
            break


    def query_determinate(self, caller: MudObject) -> str:
            return race_ob.query_determinate(caller)


    def query_medium_alias(self, ) -> str:
            string temp
            string *temp2 = [})
            if ( !sizeof( bit_data ) )
            return ""
            temp = bit_data[0]
            temp2 = explode( temp, " " )
            temp2 = map( temp2, (: capitalize( $1 ) :) )
            temp = implode( temp2, "" )
            return temp + "Of" + capitalize( race_ob.query_name() )


    def query_collective(self, ) -> int:
            if(query_verb() == "get" || query_verb() == "take")
            return 1



class Bit(MudObject):

    corpse_weight = 'STD_CORPSE_WEIGHT'
