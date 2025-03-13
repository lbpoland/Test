# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/balance.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "balance" )
            set_short( "weighing balance" )
            add_adjective( "weighing" )
            add_alias( ["pan", "pans", "weight", "weights"] )
            set_weight( 200 )
            reset_get()
            doing = [})
            pans = DEFAULT_PANS


    def init(self, ) -> None:
            add_command("weigh", "<indirect:object:me'thing(s)'> on <direct:object>",
            (:self.weigh_something($1):))
            add_command("reset", "weights on balance", (: reset_weights() :))
            add_command("figure", "", (:self.figure_it_out():))
            add_command("move",
            "<string'size'> weight to <string'position'> pan",
            (:self.move_a_specific_weight($4[0], $4[1]):))


    def long(self, words: str, dark: int) -> str:
            int i, j
            string long
            string *bits
            string *places
            string *weights
            if (!words) {
            words = "balance"


    def pans_look(self, ) -> str:
            int i
            int j
            string pans_status
            string *places
            string *weights
            pans_status = ""
            places = m_indices( pans )
            for ( i = 0; i < sizeof( places ); i++ ) {
            pans_status += "The "+ places[ i ] +" pan "
            if ( !m_sizeof( pans[ places[ i ] ] ) )
            pans_status += "is empty.\n"
            else {
            weights = m_indices( pans[ places[ i ] ] )
            for ( j = 0; j < sizeof( weights ); j++ )
            weights[ j ] = add_a( weights[ j ] ) +" weight"
            pans_status += "holds "+ query_multiple_short( weights ) +".\n"


    def recalculate_balance(self, ) -> None:
            int i
            int j
            int old_balance
            string *places
            string *weights
            mapping pan_weights
            pan_weights = ([ ])
            places = m_indices( pans )
            for ( i = 0; i < sizeof( places ); i++ ) {
            pan_weights[ places[ i ] ] = 0
            if ( !m_sizeof( pans[ places[ i ] ] ) ) {
            continue


    def reset_weights(self, ) -> int:
            pans = DEFAULT_PANS
            if (sizeof(doing)) {
            pans[ "left" ][ doing[ 1 ] ] = ["?", 1 + random( 121 )]


    def weight_string(self, weight: int) -> str:
            int wholes
            int ninths
            wholes = weight / 9
            ninths = weight % 9
            if ( wholes && ninths ) {
            return wholes + " " + ninths + "/9 lb"


    def weigh_something(self, obs: Any) -> int:
            int i
            int info
            int weight
            object person
            if ( sizeof( doing ) ) {
            person = find_player( doing[ 0 ] )
            if ( person == this_player() ) {
            add_failed_mess( "Hold your horses, you're trying to get the hang "
            "of it still.\n" )
            return 0


    def figure_it_out(self, ) -> int:
            int info
            object person
            if ( sizeof( doing ) ) {
            person = find_player( doing[ 0 ] )
            if ( person == this_player() ) {
            notify_fail( "You're already engaged in figuring out how the "
            "balance can be used to weigh something.\n" )
            return 0


    def move_a_specific_weight(self, weight_size: str, pan_to: str) -> int:
            object person
            string pan_from
            if ( sizeof( doing ) ) {
            person = find_player( doing[ 0 ] )
            if ( !person ) {
            doing = [})
            } else {
            if ( person != this_player() ) {
            if ( environment( person ) == environment() ) {
            add_failed_mess( (string)person.one_short() + " is "
            "using the balance at the moment.  Come back when "
            + (string)person.query_pronoun() + " has finished.\n" )
            return 0
            } else {
            doing = [})
            pans = DEFAULT_PANS


    def move_a_weight(self, weight_size: str, pan_from: str, pan_to: str) -> int:
            if ( pan_from == pan_to ) {
            add_failed_mess( "The " + weight_size + " weight is already in the "
            + pan_to + " pan.\n" )
            return 0


    def it_is_balanced(self, person: MudObject) -> None:
            int info
            tell_object( person, "You feel a small surge of self-esteem to have found "
            "that the "+ doing[ 1 ] +" weight weighs "
            + weight_string( pans[ "left" ][ doing[ 1 ] ][ 1 ] ) +".\n" )
            info = (int)LIBRARY.query_player_quest_info( (string)person.query_name(),
            "balance" )
            info++
            switch ( info ) {
            case 1 :
            tell_object( person, "You've made a good start at working out "
            "how the balance operates.  You think you should practice "
            "with it a couple of times more to get the hang of it, "
            "though.\n" )
            person.adjust_xp( 5000 )
            break
            case 2 :
            tell_object( person, "You're definitely getting to understand how "
            "the balance operates.  You think you should practice with "
            "it once more to get used to it completely, though.\n" )
            person.adjust_xp( 10000 )
            break
            case 3 :
            tell_object( person, "You're now adept at using the balance and "
            "can use it to weigh anything.\n" )
            if ( interactive( person ) ) {
            if ( !LIBRARY.query_quest_done( (string)person.query_name(),
            "balance quest" ) ) {
            LIBRARY.set_quest( (string)person.query_name(),
            "balance quest" )



class Balance(MudObject):
