# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/furnitures/lamps/teahouse_stone_lamp.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            fuel_left = 3600
            is_lit    = 0
            has_tealight = 0
            set_name("lamp")
            set_short("stone teahouse lamp")
            set_weight( 40 )
            set_value( 50000 )
            add_adjective( ["stone", "teahouse"] )
            add_alias( ["teahouse lamp", "stone lamp"] )
            set_long( function() {
            string str
            str = "Shaped like an Agatean teahouse, this lantern creates "
            "a peaceful ambiance of Auriental tradition in your home as "
            "it casts a beautiful soft glow through its calligraphed rice "
            "paper windows.  Exquisitely handcrafted in the shape of an "
            "Agatean teahouse, the front door of the lantern swings open "
            "to reveal the tealight inside.  "
            if(has_tealight && is_lit) {
            fuel_left = find_asyncio.create_task(self."out_of_fuel")
            return str + "The tealight is burning with a steady yellow "
            "light."


    def init(self, ) -> None:
            add_command("replace", "tealight in <direct:object:me>")
            this_player()->add_command("light", self)
            this_player()->add_command("extinguish", self)


    def dest_me(self, ) -> None:
            set_light( 0 )
            ::dest_me()


    def do_extinguish(self, ) -> int:
            if ( !has_tealight ) {
            this_player()->add_failed_mess( self, "There is no "
            "tealight in $D\n", [}) )
            return 0


    def do_light(self, ) -> int:
            if ( is_lit ) {
            this_player()->add_failed_mess( self, "$D is already "
            "lit.\n", [}) )
            return 0


    def do_replace(self, ) -> int:
            int i
            object *things
            things = all_inventory( this_player() )
            for( i = 0; i < sizeof( things ); i++ ){
            if( !has_tealight && things[ i ]->query_name() == "tealight" ) {
            fuel_left = 3600
            is_lit = 0
            has_tealight = 1
            destruct( things[ i ] )
            this_player()->add_succeeded_mess( self, "$N $V the "
            "tealight in the $D.\n", [}) )
            return 1


    def init_dynamic_arg(self, arg: Any) -> None:
            if (arg["::"]) ::init_dynamic_arg(arg["::"])
            if (arg["fuel left"]) {
            fuel_left = arg["fuel left"]


    def out_of_fuel(self, ) -> None:
            object env
            env = environment(self)
            is_lit = 0
            has_tealight = 0
            fuel_left = 0
            set_light( 45 )
            tell_room(env, "The tealight in the lamp burns out.\n" )


    def pretty_plural(self, str: MudObject) -> str:
            if ( is_lit )
            return ::pretty_plural( str) + " (lit)"
            return ::pretty_plural( str)


    def short(self, i: int) -> str:
            if ( is_lit )
            return ::short( 0 ) + " (lit)"
            return ::short( 0 )



class Teahouse_stone_lamp(MudObject):
