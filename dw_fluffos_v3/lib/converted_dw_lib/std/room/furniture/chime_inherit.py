# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/furniture/chime_inherit.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def setup(self, ) -> None:
            set_name( "chime" )
            set_short( (: chimes_short() :) )
            set_long( (: chimes_long() :) )
            add_adjective( ["wind", chime_type()] )
            set_value( 420 )


    def init(self, ) -> None:
            add_command( "hang", "<direct:object'chime'> {on|from} "
            "<indirect:object'hook'>", (: do_hang( $1[0] ) :) )
            add_command( "unhang", "<direct:object'chime'>" )


    def chimes_short(self, ) -> str:
            return chime_type() + " wind chime"


    def chimes_long(self, ) -> str:
            return "This little wind chime is nothing more than bits of "
            + chime_type() + " dangling from strings tied to a "
            "ring.\n"


    def set_chime_type(self, type: str) -> None:
            remove_adjective( _chime_type )
            add_adjective( type )
            _chime_type = type


    def jingle(self, ) -> None:
            object env = environment()
            int wind
            if( !env )
            return
            if( !hung_up() )
            return
            if( !inherits( "/std/room", env ) )
            return
            wind = env.query_wind_speed()
            if( undefinedp( wind ) ) {
            if( env.query_property( "location" ) == "outside" ||
            env.query_property( "windy" ) )
            wind = WEATHER.query_windsp( self )
            else
            return


    def chime_verb(self, ) -> str:
            return " " + _chime_verbs[ random( sizeof( _chime_verbs ) ) ]


    def add_chime_verb(self, verb: str) -> None:
            _chime_verbs += [verb]


    def remove_chime_verb(self, verb: str) -> None:
            _chime_verbs -= [verb]


    def set_hung_up(self, up: int) -> None:
            remove_asyncio.create_task(self. "jingle" )
            if( up )
            asyncio.create_task(self. "jingle", 30 )
            _hung_up = up


    def init_dynamic_arg(self, arg: Any) -> None:
            set_chime_type( arg[ "type" ] )
            set_chime_verbs( arg[ "chime verbs" ] )
            set_hook( arg[ "hook" ] )
            set_hung_up( arg[ "hung up" ] )
            if( undefinedp( hook() ) || !hung_up() ||
            !sizeof( match_objects_for_existence( hook(), [environment()] ) ) ) {
            remove_property( "there" )
            set_hung_up( 0 )


    def query_dynamic_auto_load(self, ) -> Any:
            return ([ "::" : ::query_dynamic_auto_load(),
            "type" : chime_type(),
            "chime verbs" : query_chime_verbs(),
            "hung up" : hung_up(),
            "hook" : hook() ])


    def do_hang(self, hook: MudObject) -> int:
            string where = hook.a_short()
            if( hung_up() ) {
            add_failed_mess( "The chime is already hanging up.\n" )
            return 0


    def do_unhang(self, ) -> int:
            if( !hung_up() ) {
            add_failed_mess( "The chime isn't hanging from anything.\n" )
            return 0



class Chime_inherit(MudObject):
