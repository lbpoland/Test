# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/fire_cracker.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "firecracker" )
            add_alias( "cracker" )
            add_adjective( "fire" )
            add_plural( "crackers" )
            set_short( "fire cracker" )
            set_long( "This is a large red fire cracker of Auriental manufacture"
            ".  It's the sort of thing that is thrown at weddings.  You may "
            "'light' it, and 'throw' it.\n" )
            set_weight( 2 )
            set_value( 500 )
            set_read_mess("ACME Firecracker", "agatean")


    def explosion(self, ) -> None:
            object victim
            if( !environment() )
            return
            if( living( environment() ) ) {
            victim = environment()
            await  environment().send("%^BOLD%^%^RED%^$C$"+ the_short()
            +" explodes in your face!\nMeep meep!%^RESET%^\n" )
            environment()->add_effect (EFFECT, DURATION)
            if( environment( environment() ) ) {
            tell_room( environment( environment() ), "%^BOLD%^%^RED%^$C$"+
            the_short() +" explodes in "+
            environment()->the_short() +"'s face!\nMeep meep!%^RESET%^\n",
            environment() )


    def do_light(self, ) -> int:
            asyncio.create_task(self. (: explosion :), 10 )
            add_succeeded_mess( "$N $V $D and smoke begins to pour out.\n",
            [}) )
            return 1


    def do_throw(self, ) -> int:
            if( environment() && environment( environment() ) ) {
            add_succeeded_mess( "$N $V $D on the ground.\n", [}) )
            move( environment( environment() ) )
            return 1
            } else {
            add_failed_mess( "There is no ground to $V $D on.  How very odd\n",
            [}) )
            return 0


    def init(self, ) -> None:
            add_command( "light", "<direct:object:me>", (: do_light :) )
            add_command( "throw", "<direct:object:me>", (: do_throw :) )


    def query_death_reason(self, ) -> str:
            return "being blown up by a fire cracker, in true Road Runner Style.\n"
            "%^BOLD%^Meep meep!%^RED%^"



class Fire_cracker(MudObject):
