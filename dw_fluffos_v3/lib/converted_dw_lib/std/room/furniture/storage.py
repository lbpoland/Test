# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/furniture/storage.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._drawer_mess = "a drawer in $ob_short$"
            self._drawers = []


    def add_drawer(self, type: str, amount: int) -> None:
            if ( !type || ( type == "" ) || ( amount < 1 ) ) {
            return


    def query_drawers_inside(self, ) -> int:
            varargs int move( mixed dest, string messin, string messout ) {
            int i, w
            object from
            if (!move_check(dest)) {
            write(the_short() + " resists being picked up and shocks you slightly.\n")
            return MOVE_INVALID_DEST


    def get(self, dest: Any) -> int:
            if(!move_check(dest)) {
            write("You feel it would be wrong to take " + the_short() + ".\n")
            return 2


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
            object thief
            result = ::test_remove(thing, flag, dest)
            if(result && environment() && this_player()) {
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
            int i
            if ( flag )
            return 0
            if(!environment(thing))
            return 1
            if(sizeof(_drawers)) {
            if ( !_biggest )
            for ( i = 0; i < sizeof( _drawers ); i+= 2 )
            if ( _drawers[ i + 1 ] > _biggest )
            _biggest = _drawers[ i + 1 ]
            if ( (int)thing.query_complete_weight() > _biggest )
            return write( (string)thing.the_short() +" is too big "+
            "to fit in any of "+ the_short() +"'s drawers.\n" )


    def pick_unlock(self, player: MudObject) -> int:
            if(!pick_ok(player))
            return 0
            return ::pick_unlock(player)


    def pick_lock(self, player: MudObject) -> int:
            if(!pick_ok(player))
            return 0
            return ::pick_lock(player)


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
            set_allowed_positions(map["allowed_positions"])
            if(!undefinedp(map["trap"]))
            setup_trap(map["trap"][0],
            map["trap"][1],
            map["trap"][2],
            map["trap"][3],
            map["trap"][4])
            if(!undefinedp(map["trap armed"]))
            set_trap_armed(map["trap armed"])


    def query_help_file_directory(self, ) -> str:
            return "/doc/furniture/"


    def query_dynamic_auto_load(self, ) -> Any:
            mapping junk
            junk = cont_save::query_dynamic_auto_load()
            if (!junk) {
            junk = ([ ])


    def init_dynamic_arg(self, map: Any, object) -> None:
            cont_save::init_dynamic_arg(map, 0)
            set_bonded(map["bonded"])



class Storage(MudObject):

    _drawer_mess = '"a drawer in $ob_short$"'

    _drawers = '[]'
