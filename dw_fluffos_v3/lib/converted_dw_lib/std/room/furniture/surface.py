# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/furniture/surface.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def init(self, ) -> None:
            string alias
            if(_aliases)
            foreach(alias in _aliases) {
            add_command(alias, "<indirect:object:me> {in|on|into} <indirect:object>",
            (: "/cmds/living/put"->cmd($1, $3, $4) :) )


    def set_put_aliases(self, aliases: str) -> None:
            _aliases = aliases


    def set_allow_use_internals(self, allow: int) -> None:
            _use_internals = allow


    def query_allow_use_internals(self, ) -> int:
            return _use_internals


    def get(self, dest: Any) -> int:
            if(!move_check(dest)) {
            write("You feel it would be wrong to take " + the_short() + ".\n")
            return 2


    def test_remove(self, thing: MudObject, flag: int, dest: Any) -> int:
            mixed *stuff
            object thief
            if(environment() && this_player()) {
            thief = this_player()
            if(thief.query_caster())
            thief = find_player(thief.query_caster())
            else if(thief.query_owner())
            thief = thief.query_owner()
            stuff = thing.query_property("dropped")
            if(function_exists("test_occupier", environment()) &&
            !environment()->test_occupier(thief.query_name()) &&
            (!sizeof(stuff) || stuff[0] != thief.query_name()) &&
            thief && environment(thief)) {
            event(environment(thief), "theft", thief, self, [thing])


    def test_add(self, thing: MudObject, flag: int) -> int:
            if(environment())
            event(environment(), "save")
            #ifdef DEBUG
            if(environment() && base_name(environment()) != "/room/rubbish")
            log_file(base_name(environment()) + ".log",
            "%s %s put on %s by %s.\n", ctime(time())[4..18],
            thing.query_short(), self.query_short(),
            this_player() ? this_player()->query_name() : "Unknown")
            #endif
            return 1


    def update_loc_weight(self, ) -> None:
            int i
            object *contents
            _loc_weight = 0
            contents = all_inventory( self )
            for ( i = 0; i < sizeof( contents ); i++ )
            _loc_weight += (int)contents[ i ]->query_complete_weight()


    def query_complete_weight(self, ) -> int:
            return ::query_complete_weight() + query_loc_weight()


    def add_weight(self, n: int) -> int:
            if ( !_max_weight ) return 1
            if ( n + _loc_weight > _max_weight ) return 0
            if ( !environment() ) {
            _loc_weight += n
            return 1


    def transfer_all_to(self, dest: MudObject) -> int:
            object *ob
            int i
            ob = all_inventory(self)
            for (i=0;i<sizeof(ob);i++)
            ob[i]->move(dest)
            if (first_inventory(self)) return 0
            return 1


    def long(self, word: str, dark: int) -> str:
            object *things
            things = (object *)self.find_inv_match( "all", this_player() )
            if ( !sizeof( things ) )
            return object::long( word, dark ) +"There is nothing on "+
            the_short() +".\n"
            return object::long( word, dark ) + query_contents( "On " +
            the_short() +" "+ ( sizeof( things ) == 1 ? "is " :
            "are " ), things )


    def stats(self, ) -> Any:
            return ::stats() + ({
            ["loc_weight", query_loc_weight(),],
            ["max_weight", query_max_weight(),],
            })


    def handle_restore_inventory(self, ob: MudObject) -> int:
            return (int)ob.move(self)


    def init_dynamic_arg(self, bing: Any) -> None:
            function f
            if ( bing[ "::" ] ) {
            ::init_dynamic_arg( bing[ "::" ] )


    def init_static_arg(self, bing: Any) -> None:
            if (bing["::"]) {
            ::init_static_arg(bing["::"])


    def query_static_auto_load(self, ) -> Any:
            if ( base_name(self) + ".c" == __FILE__ )
            return int_query_static_auto_load()
            return ([ ])


    def dest_me(self, ) -> None:
            int i
            object shadow
            for ( i = 0; i < sizeof( _shadows ); i++ ) {
            if ( shadow = find_object( _shadows[ i ] ) ) {
            shadow.destruct_shadow( shadow )


    def query_help_file_directory(self, ) -> str:
            return "/doc/furniture/"



class Surface(MudObject):
