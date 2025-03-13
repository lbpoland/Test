# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/furniture/furniture.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._drawer_mess = "a drawer in $ob_short$"
            self._drawers = []
            self._on_top = []


    def add_drawer(self, type: str, amount: int) -> None:
            if ( !type || ( type == "" ) || ( amount < 1 ) ) {
            return


    def query_drawers_inside(self, ) -> int:
            varargs int move( mixed dest, string messin, string messout ) {
            int i, w
            object from
            w = (int)self.query_complete_weight() * 5
            if ( from = environment() ) {
            from.add_weight( -w )


    def long(self, word: str, dark: int) -> str:
            int i
            string ret, *sizes
            mapping types
            ret = ::long( word, dark )
            if ( sizeof( _drawers ) && !dark &&
            (!query_closed() || !_drawers_inside)) {
            types = ([ ])
            for ( i = 0; i < sizeof( _drawers ); i += 2 ) {
            types[ _drawers[ i ] ]++


    def test_remove(self, thing: MudObject, flag: int, dest: Any) -> int:
            int result
            mixed *stuff
            result = ::test_remove(thing, flag, dest)
            if(result) {
            stuff = thing.query_property("dropped")
            if(environment() &&
            dest == this_player() &&
            function_exists("test_occupier", environment()) &&
            !environment()->test_occupier(this_player()->query_name()) &&
            (!sizeof(stuff) || stuff[0] != this_player()->query_name())) {
            event(environment(this_player()), "theft", this_player(), self,
            [thing])


    def test_add(self, thing: MudObject, flag: int) -> int:
            int i
            int result
            if ( flag )
            return 0
            if(!environment(thing))
            return 1
            result = ::test_add(thing, flag)
            if(!result)
            return 0
            if("/cmds/living/put"->query_con() == "on" && _has_surface) {
            _on_top += [thing]
            thing.add_property("_on_top", 1)
            } else if(sizeof(_drawers)) {
            if ( !_biggest )
            for ( i = 0; i < sizeof( _drawers ); i+= 2 )
            if ( _drawers[ i + 1 ] > _biggest )
            _biggest = _drawers[ i + 1 ]
            if ( (int)thing.query_complete_weight() > _biggest )
            return write( (string)thing.the_short() +" is too big "+
            "to fit in any of "+ the_short() +"'s drawers.\n" )


    def pick_unlock(self, player: MudObject) -> int:
            mixed owner
            if(!environment())
            return ::pick_unlock(player)
            if(!environment() || !function_exists("query_owner", environment()))
            return ::pick_unlock(player)
            owner = environment()->query_owner()
            if(stringp(owner) && pk_check(player, owner, 1)) {
            write("You feel it would be wrong to try to break into "+
            self.query_short() + ".\n")
            return 0


    def init_static_arg(self, map: Any) -> None:
            if ( !mapp( map ) )
            return
            if ( map[ "::" ] )
            ::init_static_arg( map[ "::" ] )
            if ( !undefinedp( map[ "drawer mess" ] ) )
            _drawer_mess = map[ "drawer mess" ]
            if ( !undefinedp( map[ "drawers" ] ) )
            _drawers = map[ "drawers" ]
            if(!undefinedp(map["allowed_positions"]))
            set_allowed_positions( map["allowed_positions"])
            if(!undefinedp(map["trap"]))
            setup_trap(map["trap"][0],
            map["trap"][1],
            map["trap"][2],
            map["trap"][3],
            map["trap"][4])
            if(!undefinedp(map["trap armed"]))
            set_trap_armed(map["trap armed"])


    def init_dynamic_arg(self, bing: Any) -> None:
            object item
            ::init_dynamic_arg(bing)
            foreach(item in all_inventory(self)) {
            if(item.query_property("_on_top"))
            _on_top += [item]


    def query_help_file_directory(self, ) -> str:
            return "/doc/furniture/"



class Furniture(MudObject):

    _drawer_mess = '"a drawer in $ob_short$"'

    _drawers = '[]'

    _on_top = '[]'
