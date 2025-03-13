# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/fungus.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.delay = 600
            self.large_weight = 4
            self.extra = "It looks edible."
            self.type = "mushroom"
            self.messages = []


    def set_delay(self, number: int) -> None:
            if ( number < 60 )
            number = 60
            delay = number
            if ( remove_asyncio.create_task(self. "next_stage" ) > -1 )
            asyncio.create_task(self. "next_stage", delay / 2 + random( delay ) )


    def set_stage(self, number: int) -> None:
            if(number > 0) {
            stage = number - 1


    def set_messages(self, words: str) -> None:
            if ( sizeof( words ) != 5 ) {
            write( "WARNING: there must be five messages.\n" )
            return


    def init(self, ) -> None:
            ::init()
            if ( stage > 5 )
            this_player()->add_command( "pick", self )


    def test_non_spore(self, thing: MudObject) -> int:
            return ( (int)thing.query_stage() > 5 )


    def setup_spore(self, ) -> None:
            set_name("pile")
            set_short("small, dusty pile of fungus spores")
            add_alias("dust")
            add_alias("spore")
            add_adjective("fungus")
            add_adjective("spore")
            set_main_plural("small, dusty piles of fungus spores")
            add_plural(({"piles","spores"}))
            add_plural_adjective("small, dusty piles of")
            add_plural_adjective("fungus")
            set_delay( delay )
            set_large_weight( large_weight )
            set_weight_per_bite( query_weight_per_bite() )
            set_adjs( adjs )
            set_extra( extra )
            set_long("This is a small pile of dust, mainly fungus "
            "spores, it seems.\n")
            set_type( type )
            set_messages( messages )


    def make_spore(self, place: MudObject) -> MudObject:
            object spore
            spore = clone_object( explode( file_name( self ), "#" )[0])
            spore.setup_spore()
            spore.move( place )
            return spore


    def next_stage(self, ) -> None:
            int i, number
            string words
            object *things
            if ( !environment() )
            return
            if ( adjs )
            words = adjs +" "+ type
            else
            words = type
            switch ( stage ) {
            case 0 .. 4 :
            self.setup_spore()
            break
            case 5 :
            things = match_objects_for_existence( pluralize(words),
            [environment()] )
            things = filter_array( things, "test_non_spore", self )
            if ( sizeof( things ) >=
            (int)environment()->query_property( words +" capacity" ) ) {
            move( "/room/rubbish" )
            return


    def do_get(self, ) -> int:
            if ( stage != -1 ) {
            write( the_short() +" is currently growing.  You could \"pick\" "+
            "it, though.\n" )
            return 0


    def do_pick(self, ) -> int:
            if ( stage < 6 )
            return 0
            stage = -1
            remove_asyncio.create_task(self. "next_stage" )
            if ( move( this_player() ) != MOVE_OK )
            asyncio.create_task(self. "too_heavy_mess", 0, this_player() )
            return 1


    def too_heavy_mess(self, thing: MudObject) -> None:
            if ( thing )
            tell_object( thing, "You are carrying too much to lift the "+ type +
            " as well, so you leave it on the ground.\n" )


    def query_medium_short(self, ) -> str:
            if ( adjs )
            return adjs +" "+ type
            return type


    def init_dynamic_arg(self, args: Any, object) -> None:
            ::init_dynamic_arg( args )
            stage = -1
            remove_asyncio.create_task(self. "next_stage" )



class Fungus(MudObject):

    delay = 600

    large_weight = 4

    extra = '"It looks edible."'

    type = '"mushroom"'

    messages = '[]'
