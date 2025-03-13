# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/rooftop.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def init(self, ) -> None:
            ::init()
            add_command( "jump", "<word'direction'>",
            (: self.do_roofjump( $4[0] ) :) )


    def __init__(self):
            self.weak_messages = []
            self.slope_messages = []
            self.step_messages = []
            self.jump_tm_messages = []
            self.jump_success_messages = []
            self.jump_failure_messages = []
            self.ghost_fall_messages = []
            self.item_slope_messages = []
            self.corpse_slope_messages = []
            self.damages = ([ ])
            self.damage_types = ['weak', 'slope', 'step', 'jump']
            self.translations = ([ ])
            self.jump_info = ([ ])


    def set_weak_messages(self, player: str, from: str, to: str, warn: str) -> None:
            weak_messages = [player, from, to, warn]


    def set_slope_messages(self, player: str, from: str, to: str) -> None:
            slope_messages = [player, from, to]


    def set_step_messages(self, player: str, from: str, to: str) -> None:
            step_messages = [player, from, to]


    def set_jump_tm_messages(self, : str) -> None:
            jump_success_messages = messages


    def set_jump_success_messages(self, player: str, from: str, to: str) -> None:
            jump_success_messages = [player, from, to]


    def set_jump_failure_messages(self, player: str, from: str, to: str) -> None:
            jump_failure_messages = [player, from, to]


    def set_ghost_fall_messages(self, player: str, from: str, to: str) -> None:
            ghost_fall_messages = [player, from, to]


    def set_corpse_slope_messages(self, from: str, to: str) -> None:
            corpse_slope_messages = [from, to]


    def set_item_slope_messages(self, from: str, to: str) -> None:
            item_slope_messages = [from, to]


    def set_fall_damage(self, type: str, damage: int) -> None:
            if( damage < 0 )
            damage = -damage
            if( type == "all" ) {
            foreach( type in damage_types )
            damages[type] = damage
            } else if( damage_types .index( type) if  type in damage_types  else -1 >= 0 ) {
            damages[type] = damage
            } else
            return


    def query_fall_damage(self, type: str) -> Any:
            if( type == "all" )
            return damages
            else
            return damages[type]


    def calc_fall_damage(self, type: str) -> int:
            if( type == "all" )
            return 0
            return query_fall_damage( type ) + random( query_fall_damage( type ) )


    def set_weak_roof(self, maxweight: int, dest: str) -> None:
            roof_max_weight = maxweight
            weak_roof_dest = dest


    def set_slope(self, angle: int, loc: str, dest: str) -> None:
            gradient = ( angle * 100 ) / 90
            place = loc
            slope_dest = dest


    def set_jump(self, dir: Any, dest: str, fall_dest: str, distance: int) -> int:
            string * dirs
            mixed foo
            string bar
            if( stringp( dir ) ) {
            dirs = [dir]
            } else if( arrayp(dir) ) {
            foreach( foo in dir )
            if( !stringp( foo ) )
            return 0
            dirs = sort_array( dir, 1 )


    def event_enter(self, obj: MudObject, from: MudObject) -> None:
            int totalweight, objectweight, i
            float encum, diff
            int fall
            object * contents
            object destination
            if( !obj ) return
            if( obj.query_property( "demon" )
            || obj.query_property( "floating" ) ) {
            return


    def gradient_check(self, obj: MudObject, destination: str, diff: int) -> None:
            object destob
            #ifdef DEBUG
            debug_printf( "gradient_check( %s, \"%s\", %d )",
            obj.query_name(), destination, diff )
            #endif
            obj.remove_property( TOO_SOON )
            switch( TASKER.perform_task( obj, ROCK, diff + 1, TM_FIXED ) ) {
            case AWARD:
            tell_object( obj, "%^YELLOW%^" + ({
            "You balance more confidently on the " + place + ".",
            "Climbing becomes easier."
            })[ random(2) ] + "%^RESET%^\n" )
            case SUCCEED:
            tell_object( obj, "The " + place + " is steep, but you manage "
            "not to fall.\n" )
            break
            case FAIL:
            if( !( destob = load_object( destination ) ) ) {
            tell_object( obj, "Error loading room " + destination +
            ", moving you to the void.\nPlease contact a creator.\n" )
            obj.move_with_look( "/room/void" )
            } else
            do_fall( obj, destob, "slope", slope_messages, 0 )
            break
            default:
            write( "Gnaaaaaaaaaaaah! You should not be getting this message.  "
            "Please contact a creator.\n" )
            break


    def do_roofjump(self, dir: str) -> int:
            mixed * info
            int distance
            float weight, max_weight
            object destination, fall_destination
            string key
            if( !( key = translations[dir] ) || !( info = jump_info[key] ) ) {
            add_failed_mess( "You can't jump there!\n" )
            return 0


    def query_death_reason(self, ) -> str:
            asyncio.create_task(self. (: death_reason = 0 :), 2 )
            if( death_reason )
            return "/global/player"->convert_message( death_reason )
            return "a rooftop (" + file_name( self )
            + ") with an incorrectly set death message"


    def set_death_reason(self, str: str) -> None:
            death_reason = str


    def process_string(self, str: str, transforms: Any) -> str:
            string foo, bar
            foreach( foo, bar in transforms )
            if( bar ) str = replace_string( str, foo, bar )
            return "/global/player"->convert_message( str )


    def process_mess(self, str: str, ob: MudObject, direction: str) -> str:
            string opp_dir
            string * directions = ["north", "northeast", "east", "southeast",
            "south", "southwest", "west", "northwest"]
            if( !str || ( str == "" ) )
            return ""
            if( stringp( direction ) ) {
            if( directions .index( direction) if  direction in directions  else -1 < 0 ) {
            opp_dir = 0
            } else {
            opp_dir =
            directions[ ( directions .index( direction) if  direction in directions  else -1 + 4 ) % 8 ]


    def test_remove(self, ob: MudObject, flag: int, dest: Any) -> int:
            if( !living(ob) ) {
            return ::test_remove( ob, flag, dest )



class Rooftop(MudObject):

    weak_messages = '[]'

    slope_messages = '[]'

    step_messages = '[]'

    jump_tm_messages = '[]'

    jump_success_messages = '[]'

    jump_failure_messages = '[]'

    ghost_fall_messages = '[]'

    item_slope_messages = '[]'

    corpse_slope_messages = '[]'

    damages = '([ ])'

    damage_types = "['weak', 'slope', 'step', 'jump']"

    translations = '([ ])'

    jump_info = '([ ])'
