# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/npc/vampirebite_effect.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def beginning(self, person: MudObject, extent: int, id: int) -> int:
            int con, time
            tell_object( person, "Pain shoots through your veins, exploding inside "
            "your head, making you scream in agony as the effect of the vampire's "
            "bite fills your body.\n" )
            person.add_extra_look( self )
            person.adjust_bonus_int(-2)
            person.adjust_bonus_wis(-2)
            person.adjust_bonus_str(-2)
            person.adjust_bonus_dex(-2)
            person.submit_ee( "bite_pain", [10, 60], EE_CONTINUOUS )
            con = person.query_con()
            if( con < 1 ) con = 1
            time = 2 * extent / con
            person.submit_ee( 0, time, EE_REMOVE )
            return time


    def merge_effect(self, person: MudObject, old_time: int, new_extent: int, id: int) -> int:
            int con, new_time
            con = person.query_con()
            if( con < 1 ) con = 1
            new_time = ( 2 * new_extent / con ) + person.expected_tt()
            person.submit_ee( 0, new_time, EE_REMOVE )
            return new_time


    def restart(self, person: MudObject, time: int, id: int) -> None:
            person.adjust_bonus_int(-2)
            person.adjust_bonus_wis(-2)
            person.adjust_bonus_str(-2)
            person.adjust_bonus_dex(-2)


    def end(self, person: MudObject, time: int, id: int) -> None:
            if( person.query_property( PASSED_OUT_PROP ) )
            come_around( person )
            person.adjust_bonus_int(2)
            person.adjust_bonus_wis(2)
            person.adjust_bonus_str(2)
            person.adjust_bonus_dex(2)
            tell_object( person, "The firey pain screaming through your veins and "
            "incessant pounding inside your head finally wear off, leaving you "
            "with a mild headache.\n" )


    def bite_pain(self, person: MudObject, time: int, id: int) -> None:
            int timeleft, selector
            timeleft = (int)person.expected_tt()
            if( person.query_property( PASSED_OUT_PROP ) ) {
            switch( random(3) ) {
            case 0 :
            tell_room( environment(person), person.one_short() + " shakes "
            "slightly in silent agony.\n", person )
            break
            case 1 :
            tell_room( environment(person), person.one_short() + " moans, "
            "writhing on the ground.\n", person )
            break
            case 2 :
            tell_room( environment(person), person.one_short() + " opens " +
            person.query_possessive() + " eyes, stares around wildly as if "
            "in a fever, and passes out again with a groan.\n", person )
            break


    def come_around(self, person: MudObject) -> None:
            tell_object( person, "You feel a pounding headache coming on and realise "
            "you are finally conscious.\n" )
            tell_room( environment( person ), person.the_short() + " groans "
            "painfully, opens " + person.query_possessive() + " eyes and slowly "
            "picks " + person.query_objective() + "self up.\n", person )
            person.remove_property( PASSED_OUT_PROP )


    def wander_about(self, person: MudObject, time: int, id: int) -> None:
            int i, flag
            string *direcs
            if( person.query_property( PASSED_OUT_PROP ) || !environment( person ) )
            return
            if( random( 4 ) )
            person.submit_ee( "wander_about", [8, 8], EE_ONCE )
            direcs = (string *)environment( person )->query_direc()
            while( sizeof( direcs ) && !flag ) {
            i = random( sizeof( direcs ) )
            if(
            !environment( person )->query_door_open( direcs[ i ] ) ) {
            direcs = delete( direcs, i, 1 )
            continue


    def extra_look(self, player: MudObject, args: Any) -> str:
            return capitalize(player.query_pronoun()+" looks rather pale with cold,"
            " clammy skin and a look of dizziness.\n")



class Vampirebite_effect(MudObject):
