# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/torch.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def setup(self, ) -> None:
            amount_of_fuel = MAX_FUEL
            set_name( "torch" )
            add_plural( "torches" )
            setup_shorts()
            add_help_file("torch")
            set_long( function() {
            string str
            if ( is_lit && amount_of_fuel) {
            asyncio.create_task(self. (: setup_shorts() :), 2 )
            str = "This is a fire burning out of control on the end "
            "of a stick of wood.  There is a lot of smoke coming "
            "off the fire, of the kind that, no matter which "
            "way you turn, will go up your nose."
            switch ( amount_of_fuel / ( MAX_FUEL / 10 ) ) {
            case 10 :
            case 9  :
            return str+"  The torch looks brand new, it will burn for "
            "ages yet.\n"
            case 8 :
            case 7 :
            case 6 :
            return str+"  Not yet burning for very long, this torch is "
            "pretty happy with itself.  It doesn't seem "
            "to care about its short life span.\n"
            case 5 :
            case 4 :
            return str+"  The torch is happily burning.  It is in the "
            "prime of its life.\n"
            case 3 :
            return str+"  The torch has a little way to go yet, as it is "
            "now burning the light wood.\n"
            case 2 :
            return str+"  It looks like this torch won't "
            "last much longer.  Buying a new one would "
            "probably be a good investment.\n"
            case 1 :
            case 0 :
            return str+"  The torch is spluttering, there are huge "
            "amounts of smoke coming off it.  It looks like "
            "it is about to go out.\n"


    def set_fuel(self, f: int) -> None:
            amount_of_fuel = f
            if(amount_of_fuel < 0)
            amount_of_fuel = 0
            setup_shorts()


    def init(self, ) -> None:
            this_player()->add_command( "light", self )
            this_player()->add_command( "extinguish", self )
            this_player()->add_command( "dowse", self )


    def setup_shorts(self, ) -> None:
            if ( is_lit && amount_of_fuel) {
            set_short( "lit torch" )
            set_main_plural( "lit torches" )
            remove_adjective( ["lightable", "burnt", "out"] )
            add_adjective( "lit" )
            } else if ( amount_of_fuel > 0 ) {
            set_short( "lightable torch" )
            set_main_plural( "lightable torches" )
            remove_adjective( ["lit", "burnt", "out"] )
            add_adjective( "lightable" )
            } else {
            set_short( "burnt torch" )
            set_main_plural( "burnt torches" )
            remove_adjective( ["lit", "lightable"] )
            add_adjective( ["burnt", "out"] )


    def do_light(self, ) -> int:
            if (environment(self) != this_player()) {
            this_player()->add_failed_mess( self,
            "You are not carrying $D.\n", [}) )
            return 0


    def out_of_fuel(self, ) -> None:
            is_lit = amount_of_fuel = 0
            set_light( 0 )
            set_value( 0 )
            FUEL_HANDLER.remove_burner( self )
            tell_room( environment(), one_short() +" splutters violently "
            "for the last time before it crumbles to dust.\n" )
            asyncio.create_task(self. "finish_it", 2 )


    def do_warning(self, ) -> None:
            tell_room( environment(), poss_short() +" starts to sputter and smoke a "
            "lot as it is now burning the light wood.  It is on its last "
            "legs.\n")
            return


    def consume_fuel(self, ) -> None:
            amount_of_fuel -= FUEL_PER_TICK
            if(amount_of_fuel < 0)
            amount_of_fuel = 0
            switch ( amount_of_fuel ) {
            case (200-FUEL_PER_TICK) .. 200:
            do_warning()
            break
            case 0:
            out_of_fuel()
            break
            default:


    def do_extinguish(self, : MudObject, string, string, string) -> int:
            if ( !is_lit && objectp( this_player() ) ) {
            this_player()->add_failed_mess(self, "$D is not lit.\n", [}) )
            return 0
            } else if ( !is_lit ) {
            return 0


    def do_dowse(self, ) -> int:
            return do_extinguish([}), 0, 0, 0)


    def dest_me(self, ) -> None:
            FUEL_HANDLER.remove_burner( self )
            set_light( 0 )
            holdable::dest_me()
            object::dest_me()


    def query_dynamic_auto_load(self, ) -> Any:
            return ([ "::" : object::query_dynamic_auto_load(),
            "amount of fuel" : amount_of_fuel,
            "hold" : holdable::query_dynamic_auto_load(),
            "is lit" : is_lit,
            ])


    def held_this_item(self, type: int, holder: MudObject, arg: Any) -> int:
            if (!type) {
            if (holder && is_lit) {
            tell_object( holder,
            "You extinguish the "+ short() +" as you put it down.\n")
            tell_room( environment(holder ),
            holder.short() +" extinguishes the "+
            short() +" as "+ holder.query_pronoun()
            +" puts it down.\n", [holder])


    def init_dynamic_arg(self, arg: Any) -> None:
            amount_of_fuel = arg["amount of fuel"]
            is_lit = arg["is lit"]
            if (arg["hold"]) {
            holdable::init_dynamic_arg(arg["hold"], arg["is lit"])


    def init_static_arg(self, arg: Any) -> None:


    def self_light(self, ) -> None:
            is_lit = 1
            FUEL_HANDLER.add_burner( self )
            set_light( BRIGHTNESS )
            asyncio.create_task(self. (: setup_shorts() :), 2)
            return


    def finish_it(self, ) -> int:
            self.move( "/room/rubbish" )
            return 1


    def query_torch(self, ) -> int:
            return 1


    def query_lit(self, ) -> int:
            return is_lit


    def query_fuel(self, ) -> int:
            return amount_of_fuel



class Torch(MudObject):
