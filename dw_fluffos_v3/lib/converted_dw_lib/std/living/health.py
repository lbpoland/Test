# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/living/health.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.max_hp = 1
            self.max_gp = 1
            self.surrender = -1
            self.drink_info = allocate( D_SIZEOF )
            self.counts = ([ ])
            self.verbs = ([ ])
            self.callingdeath = 0
            self.runaway_callout_handles = []


    def query_hp(self, ) -> int:
            varargs int set_hp( int number, object attacker ) {
            if ( number > max_hp )
            number = max_hp
            hp = number
            if ( ( hp < 0 ) && ( find_asyncio.create_task(self. "do_death" ) == -1 ) )
            asyncio.create_task(self. "do_death", 0, attacker )
            return hp


    def reset_callingdeath(self, ) -> None:
            callingdeath = 0


    def query_callingdeath(self, ) -> int:
            return callingdeath


    def set_max_hp(self, number: int) -> int:
            int old_hp
            old_hp = hp
            if ( max_hp == hp )
            hp = number
            else
            if ( max_hp )
            hp = ( hp * number ) / max_hp
            else
            hp = number
            max_hp = number
            if ( hp > max_hp )
            hp = max_hp
            if ( ( hp < 0 ) && ( old_hp > 0 ) )
            hp = max_hp
            return max_hp


    def query_specific_gp(self, gp_type: str) -> int:
            int now
            if ( !gp_type )
            return 0
            max = (int)self->query_skill_bonus( gp_type
            +".points" ) + 50
            if ( max >= max_gp )
            max = max_gp
            now = gp + max - max_gp
            which = gp_type
            if ( find_asyncio.create_task(self. "clear_gp_info" ) == -1 )
            asyncio.create_task(self. "clear_gp_info", 1 )
            return now


    def set_gp(self, number: int) -> int:
            gp = number
            if ( gp > max_gp )
            gp = max_gp
            return gp


    def adjust_gp(self, number: int) -> int:
            int tmp, diff
            string class_ob, current_verb
            mixed *bits
            if ( gp + number < 0 )
            return -1
            gp += number
            if ( gp > max_gp )
            gp = max_gp
            tmp = number
            if((number < 0) && stringp(which)) {
            if (number > ( GP_ADVANCE_MOD * max ) / MIN_TIMES)
            number = (GP_ADVANCE_MOD * max) / MIN_TIMES
            counts[ which ] -= number
            if (counts[ which ] > GP_ADVANCE_MOD * max) {
            counts[ which ] = 0
            number = self.query_skill(which +".points")
            if(!random(to_int(exp(number/150.0))) &&
            self->add_skill_level( which +".points", 1,
            self)) {
            tell_object( self, "%^YELLOW%^You find yourself "
            "more able to concentrate on this task than you "
            "thought.%^RESET%^\n" )


    def set_max_gp(self, number: int) -> int:
            if ( max_gp ) gp = ( gp * number ) / max_gp
            else gp = number
            max_gp = number
            if ( gp > max_gp ) gp = max_gp
            return max_gp


    def query_xp(self, ) -> int:
            varargs int adjust_xp( int number, int shared ) {
            if(number > 0 && (xp > 10000000 || xp + number > 10000000))
            return xp
            if(number > 10000 && previous_object() &&
            explode(file_name(previous_object()), "/")[0] == "w")
            log_file("/d/admin/log/CHEAT", ctime(time()) + " " +
            file_name(previous_object()) +
            " gave " + number + " Xp for " + self.query_name() +
            "\n")
            xp += number
            return xp


    def set_wimpy(self, number: int) -> int:
            if ( ( number < 0 ) || ( number > 30 ) ) return -1
            return wimpy = number


    def query_surrender(self, ) -> int:
            if (surrender == -1) {
            if (wimpy > 94)
            return 100
            else
            return wimpy + 5
            } else
            return surrender


    def set_surrender(self, number: int) -> int:
            if ( ( number < 0 ) || ( number > 100 ) ) return -1
            return surrender = number


    def query_volume(self, type: int) -> int:
            if ( type >= D_SIZEOF ) return 0
            return drink_info[ type ]


    def adjust_volume(self, type: int, amount: int) -> int:
            if ( type >= D_SIZEOF ) return 0
            return drink_info[ type ] += amount


    def update_volumes(self, ) -> None:
            int i, delta
            delta = (int)self.query_con()
            for ( i = 0; i < sizeof( drink_info ); i++ ) {
            if ( drink_info[ i ] > delta ) {
            drink_info[ i ] -= delta
            if(self.query_personal_temp() >  0 && i == D_DRINK)
            self.adjust_personal_temp(-(delta/3))
            else if(self.query_personal_temp() <  0 && i == D_FOOD)
            self.adjust_personal_temp(delta/3)
            } else
            if ( drink_info[ i ] < -delta )
            drink_info[ i ] += delta
            else
            drink_info[ i ] = 0



class Health(MudObject):

    max_hp = 1

    max_gp = 1

    surrender = '-1'

    drink_info = 'allocate( D_SIZEOF )'

    counts = '([ ])'

    verbs = '([ ])'

    callingdeath = 0

    runaway_callout_handles = '[]'
