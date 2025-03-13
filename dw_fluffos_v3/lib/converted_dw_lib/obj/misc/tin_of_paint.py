# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/tin_of_paint.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "tin" )
            set_short( "tin of paint" )
            set_main_plural( "tins of paint")
            add_adjective( ["tin", "of"}))
            add_alias(({"paint"}))
            set_long( "A tin of paint.  It has a picture of a man with "
            "a big smile on his face painting a wall.\n")
            set_leak_rate( 0 )
            set_max_volume( VOLUME )
            set_value( 30 )
            set_weight( 10 )
            set_max_weight( 30 )


    def setup_attribs(self, ) -> None:
            set_short( "tin of " + _colour + " paint" )
            set_main_plural( "tins of " + _colour + " paint")
            add_adjective( [_colour}))
            set_long( "A tin of " + _colour + " paint.  It has a picture of a man with "
            "a big smile on his face painting a wall.\n")


    def make_tin(self, colour: str) -> None:
            object liquid
            liquid = clone_object( "/obj/reagents/generic_liquid.ob" )
            liquid.set_name( "paint" )
            liquid.set_short( colour + " paint" )
            liquid.add_adjective(({colour])
            liquid.set_amount( VOLUME )
            liquid.set_continuous()
            liquid.set_long( "This is " + colour + " paint, it's thick and gloopy.\n")
            liquid.set_pile_name( "puddle" )
            liquid.add_eat_effect( "/std/effects/ingested/poison", 10 )
            liquid.move( self )
            set_closed()
            _colour = colour
            setup_attribs()


    def init(self, ) -> None:
            ::init()
            this_player()->add_command("paint", self,
            "<indirect:object:here'cardinal direction'> with <direct:object'paint'>",
            (: do_paint( $4[0] ) :))
            this_player()->add_command("paint", self,
            "<string'part'> on <indirect:object:here> with <direct:object'paint'>",
            (: do_paint( $4[0], $1[0] ) :))
            this_player()->add_command("paint", self,
            "<indirect:object:here> help",
            (: do_paint( 0, $1[0] ) :))


    def init_static_arg(self, args: Any) -> None:
            if (args["::"])
            ::init_static_arg(args["::"])
            if (!undefinedp(args["colour"]))
            _colour = args["colour"]
            if(_colour)
            setup_attribs()



class Tin_of_paint(MudObject):
