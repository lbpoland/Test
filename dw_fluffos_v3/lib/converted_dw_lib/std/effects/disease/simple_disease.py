# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/disease/simple_disease.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.shadow_ob = 0
            self.infection_chance = 0
            self.infection_check = 0
            self.cure_rate = 0


    def beginning(self, person: MudObject, arg: int, id: int) -> int:
            id = person.sid_to_enum( id )
            arg = self.disease_start( person, arg, id )
            if ( !arg ) {
            person.submit_ee( 0, 0, EE_REMOVE )
            return 0


    def merge_effect(self, person: MudObject, old_arg: int, new_arg: int, id: int) -> int:
            if ( old_arg < new_arg ) {
            old_arg = new_arg
            self.disease_worse( person, old_arg, id )


    def end(self, person: MudObject, arg: int, id: int) -> None:
            self.disease_end( person, arg, id )


    def disease_tick(self, person: MudObject, arg: int, id: int) -> None:
            object *things
            int i
            if ( arg > 100000 )
            arg = 10000
            arg -= ( cure_rate*( (int)person.query_con() + 7 ) ) / 20
            person.set_arg_of( (int)person.sid_to_enum( id ), arg )
            if ( arg < 0) {
            person.submit_ee( 0, 0, EE_REMOVE )
            return


    def test_remove(self, object, int, int, int) -> int:
            #ifdef DEBUG
            log_file( "OLD_CURE", file_name( previous_object() ) +" "+
            file_name( self ) +"\n" )
            #endif



class Simple_disease(MudObject):

    shadow_ob = 0

    infection_chance = 0

    infection_check = 0

    cure_rate = 0
