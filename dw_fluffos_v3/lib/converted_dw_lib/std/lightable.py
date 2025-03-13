# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/lightable.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def init(self, ) -> None:
            this_player()->add_command( "light", self )
            this_player()->add_command( "dowse", self )
            this_player()->add_command( "extinguish", self )


    def out_of_fuel(self, ) -> None:
            object env
            fuel = 0
            lit = 0
            set_lit( 0 )
            FUEL_HANDLER.remove_burner( self )
            if( !environment() ) return
            env = environment()
            if( living( env ) ) {
            await  env.send(the_short() +" goes out.\n" )
            tell_room( environment( env ),
            env.the_short() +"'s "+ short() +" goes out.\n", env )
            } else {
            tell_room( env, the_short() +" goes out.\n" )


    def delayed_light(self, ) -> None:
            lit = 1


    def hold_thing(self, ) -> int:
            if( !query_wielded() )
            return HOLD_COMMAND.cmd( [self] )
            else
            return 1


    def set_lit(self, i: int) -> int:
            if( !i ) {
            if( !query_property( "unextinguishable" ) ) {
            lit = 0
            FUEL_HANDLER.remove_burner( self )
            remove_adjective( "lit" )
            set_light( 0 )
            return 0


    def set_holder(self, ob: MudObject, pos: int) -> Any:
            if( lit && hold && !ob && environment( this_player() )
            && file_name( environment( this_player() ) ) != DEPARTURES )
            if( !set_lit( 0 ) ) {
            await  this_player().send("You extinguish "+ the_short() +".\n" )
            tell_room( environment( this_player() ), this_player()->the_short() +
            " extinguishes "+ the_short() +".\n", this_player() )


    def query_lit(self, ) -> int:
            return lit


    def do_light(self, ) -> int:
            if( lit )
            return notify_fail( the_short() +" is already lit.\n" )
            if( !fuel )
            return notify_fail( the_short() +" "+ empty_mess +"\n" )
            if( !set_lit( 1 ) )
            return notify_fail( "You cannot light "+ the_short() +".\n" )
            this_player()->add_succeeded_mess( self, "$N $V $D.\n", [}) )
            return 1


    def do_dowse(self, ) -> int:
            if( !lit )
            return notify_fail( the_short() +" is not lit.\n" )
            if( set_lit( 0 ) )
            return notify_fail( "You cannot extinguish "+ the_short() +".\n" )
            this_player()->add_succeeded_mess( self, "$N $V $D.\n", [}) )
            return 1


    def do_extinguish(self, ) -> int:
            return do_dowse()


    def set_fuel_messages(self, msgs: Any) -> None:
            fuel_messages = msgs


    def query_fuel_messages(self, ) -> Any:
            return fuel_messages


    def set_max_fuel(self, i: int) -> None:
            max_fuel = i


    def query_max_fuel(self, ) -> int:
            return max_fuel


    def set_fuel(self, i: int) -> None:
            fuel = i
            if( fuel > max_fuel )
            fuel = max_fuel


    def query_fuel(self, ) -> int:
            return fuel


    def current_fuel_message(self, ) -> str:
            mixed messages
            int fuel_percent, size, i
            string fuel_string = ""
            if( fuel < 1 )
            return "It "+ empty_mess
            messages = query_fuel_messages()
            size = sizeof( messages )
            if( !size )
            return "This item needs a creator.  It is broken and lonely."
            if( size < 2 )
            return messages[0]
            fuel_percent = fuel * 99 / max_fuel
            if( intp( messages[1] ) ) {
            for( i = 1; i < size; i += 2 ) {
            if( messages[i] > fuel_percent ) {
            fuel_string = messages[i-1]
            break


    def set_empty_mess(self, msg: str) -> None:
            empty_mess = msg


    def query_empty_mess(self, ) -> str:
            return empty_mess


    def set_brightness(self, i: int) -> None:
            brightness = i


    def query_brightness(self, ) -> int:
            return brightness


    def set_hold_required(self, hands: int) -> None:
            hold = hands


    def query_hold_required(self, ) -> int:
            return hold


    def extra_look(self, ) -> str:
            string lit_str
            if( lit )
            lit_str = "It is lit.  "
            else
            lit_str = "It is not currently lit.  "
            return lit_str + current_fuel_message() +"\n"


    def query_dynamic_auto_load(self, ) -> Any:
            return ([ "::" : ::query_dynamic_auto_load(),
            "fuel" : fuel,
            "lit" : lit,
            ])


    def init_dynamic_arg(self, arg: Any, bing: MudObject) -> None:
            fuel = arg["fuel"]
            ::init_dynamic_arg(arg["::"], bing)
            set_lit(arg["lit"])


    def consume_fuel(self, ) -> None:
            fuel -= FUEL_TIME
            if( fuel < 1 )
            out_of_fuel()


    def query_value(self, ) -> int:
            return (int)( ::query_value() * fuel / max_fuel )



class Lightable(MudObject):
