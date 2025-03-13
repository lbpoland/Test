# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/lantern.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def short(self, i: int) -> str:
            if ( is_lit )
            return ::short( 0 ) + " (lit)"
            return ::short( 0 )


    def do_extinguish(self, ) -> int:
            if ( !is_lit ) {
            this_player()->add_failed_mess(self, "$D is not lit.\n", [}))
            return 0


    def do_dowse(self, ) -> int:
            return do_extinguish()


    def do_light(self, ) -> int:
            if ( is_lit ) {
            this_player()->add_failed_mess( self, "$D is already lit.\n",
            [}) )
            return 0


    def init(self, ) -> None:
            this_player()->add_command("light", self)
            this_player()->add_command("extinguish", self)
            this_player()->add_command("dowse", self)


    def out_of_fuel(self, ) -> None:
            object env
            is_lit    = 0
            fuel_left = 0
            env = environment( self )
            FUEL_HANDLER.remove_burner( self )
            set_light( 0 )
            if ( interactive( env ) ) {
            write( poss_short() +" burns out.\n" )
            await driver.tell_room( environment(env), poss_short() +" burns out.\n", exclude=env )
            } else
            say( poss_short() +" burns out.\n" )


    def consume_fuel(self, ) -> None:
            fuel_left -= FUEL_PER_TICK
            switch ( fuel_left ) {
            case -10000 .. 0:
            out_of_fuel()
            break
            default:


    def pretty_plural(self, thing: MudObject) -> str:
            if ( is_lit )
            return ::pretty_plural(thing) + " (lit)"
            return ::pretty_plural(thing)


    def dest_me(self, ) -> None:
            set_light( 0 )
            FUEL_HANDLER.remove_burner( self )
            ::dest_me()


    def init_dynamic_arg(self, arg: Any) -> None:
            fuel_left = arg["fuel left"]
            if ( arg[ "is lit" ] ) {
            FUEL_HANDLER.add_burner( self )
            is_lit = 1
            set_light(BRIGHTNESS)


    def query_fuel_left(self, ) -> int:
            return fuel_left


    def set_fuel_left(self, i: int) -> None:
            if ( i > MAX_FUEL ) {
            i = MAX_FUEL


    def query_max_fuel(self, ) -> int:
            return MAX_FUEL



class Lantern(MudObject):
