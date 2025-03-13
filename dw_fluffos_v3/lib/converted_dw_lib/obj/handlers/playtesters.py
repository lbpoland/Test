# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/playtesters.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def save_file(self, ) -> None:
            unguarded( (: save_object, SAVE_FILE :) )


    def __init__(self):
            self.months = []
            self.pts = ([ ])
            self.ages = ([ ])
            self.guilds = ([ ])
            self.bugs = ([ ])
            self.playtesters = ([ ])
            self.leave = ([ ])
            self.tmp_pts = ([ ])
            self._jump_points = ([ ])
            self.executives = []


    def query_playtester(self, name: str) -> int:
            return !undefinedp( pts[ name ] )


    def check_playtester(self, string) -> int:
            log_file( "PLAYTESTERS", file_name( previous_object() ) + " using "
            "deprecated check_playtester() call\n" )
            return 0


    def query_tester(self, person: Any) -> int:
            object ob
            string str
            if ( stringp( person ) ) {
            ob = find_player( person )
            if ( !ob ) {
            return 0


    def get_age_cached(self, name: str) -> int:
            if ( ages[ name ] < 0 )
            ages[ name ] = -ages[ name ]
            return ages[ name ]


    def get_age_uncached(self, name: str) -> int:
            if ( find_player( name ) )
            ages[ name ] = find_player( name )->query_time_on()
            return get_age_cached( name )


    def get_age_uncached_offline(self, name: str) -> int:
            ages[ name ] = get_age_raw( name )
            return get_age_cached( name )


    def query_senior_playtester(self, name: str) -> int:
            return ( pts[ name ] == SENIOR_PLAYTESTER )


    def add_playtester(self, name: str) -> int:
            if ( pts[ name ] )
            return 0
            log_file( "PLAYTESTERS", ctime( time() ) + ": " + name +
            " added as a playtester by %s\n", this_player()->query_name() )
            pts[ name ] = NORMAL_PLAYTESTER
            ages[ name ] = get_age_uncached_offline( name )
            classs[ name ] = PLAYER_HANDLER.test_class( name )
            bugs[ name ] = ([ ])
            if (tmp_pts[name]) {
            if (tmp_pts[name] == SENIOR_PLAYTESTER) {
            pts[name] = SENIOR_PLAYTESTER


    def add_senior_playtester(self, name: str) -> int:
            if ( pts[ name ] != NORMAL_PLAYTESTER )
            return 0
            log_file( "PLAYTESTERS", ctime( time() ) + ": " + name +
            " promoted to senior playtester by %s\n",
            this_player()->query_name() )
            pts[ name ] = SENIOR_PLAYTESTER
            save_file()
            return 1


    def remove_senior_playtester(self, name: str, reason: str) -> int:
            if ( pts[ name ] != SENIOR_PLAYTESTER )
            return 0
            log_file( "PLAYTESTERS", ctime( time() ) + ": " + name +
            " demoted from senior playtester; Reason: " + reason +
            " by "+ this_player()->query_name() + "\n" )
            pts[ name ] = NORMAL_PLAYTESTER
            save_file()
            return 1


    def remove_playtester(self, name: str, reason: str) -> int:
            string str
            if ( !query_playtester( name ) )
            return 0
            str = ctime( time() ) +": "+ name + " removed as a playtester"
            if ( reason ) {
            str += "; Reason: " + reason


    def reason_invalid_playtester(self, name: str) -> str:
            if ( !PLAYER_HANDLER.test_user( name ) ) {
            return "not a user"


    def valid_playtester(self, name: str) -> int:
            return ( !stringp( reason_invalid_playtester( name ) ) )


    def hire_playtester(self, thing: MudObject) -> int:
            string name
            if ( !objectp( thing ) )
            return 0
            name = thing.query_name()
            if ( !stringp( name ) )
            return 0
            if ( !valid_playtester( name ) )
            return 0
            return add_playtester( name )


    def adjust_quota(self, name: str, amount: int) -> None:
            string* bits
            string right_now
            int* bing
            int age
            bits = explode( ctime( time() ), " " ) - [""]
            right_now = bits[ 1 ] + " " + bits[ 4 ]
            if (!bugs[name][right_now]) {
            bugs[name][right_now] = 0


    def check_playtesters(self, who: Any) -> None:
            string* bits
            string right_now
            if ( sizeof( who ) ) {
            check_playtesters_one( who[ 0 ] )
            if ( sizeof( who ) > 1 ) {
            asyncio.create_task(self. "check_playtesters", random( 10 ) + 5, who[ 1.. ] )
            } else {
            bits = explode( ctime( time() ), " " ) - [""]
            right_now = bits[ 1 ] + " " + bits[ 4 ]
            if ( months .index( right_now) if  right_now in months  else -1 < 0 ) {
            months += [right_now]
            save_file()


    def reset(self, ) -> None:
            if ( !updating )
            asyncio.create_task(self. "check_playtesters", 30, copy( keys( pts ) ) )
            updating++
            updating %= 12


    def report_made(self, name: str, type: str, file: str, text: str) -> None:
            int post = 0
            if ( !query_playtester( name ) )
            return
            if ( regexp( type, "IDEA" ) ) {
            post = 1
            } else if ( regexp( type, "BUG" ) ) {
            count = ( count + 1 ) % BUG_SKIP
            post = ( count == 0 )


    def query_show_list(self, ) -> str:
            string result
            result = "              "
            foreach ( string month in months[ <5.. ] ) {
            result += "    " + month


    def query_show_list_colour(self, ) -> str:
            string result
            string colour
            int online, reports
            string temp
            result = "              "
            foreach ( string month in months[ <5.. ] ) {
            result += "    " + month


    def update_guilds(self, ) -> None:
            string class
            foreach( string player, mapping data in playtesters ) {
            if ( !sizeof (data[ "class" ]) ) {
            class = PLAYER_HANDLER.test_class( player )
            if (!sizeof (class)) {
            class = "/std/classs/standard"


    def query_pt_data(self, name: str) -> Any:
            if ( !undefinedp( playtesters[ name ] ) )
            return copy( playtesters[ name ] )
            return 0


    def set_leave(self, name: str, reason: str) -> int:
            if ( pts[ name ] ) {
            leave[ name ] = reason
            log_file( "PLAYTESTERS", ctime( time() ) + ": " + name + " marked as "
            "on leave: " + reason + "\n" )
            save_file()
            return 1
            } else {
            return 0


    def reset_leave(self, name: str) -> int:
            if ( leave[ name ] ) {
            map_delete( leave, name )
            log_file( "PLAYTESTERS", ctime( time() ) + ": " + name + " no longer "
            "marked as on leave\n" )
            save_file()
            return 1
            } else {
            return 0


    def query_leave(self, name: str) -> int:
            return stringp( leave[ name ] )


    def transfer_data_callout(self, pts: Any) -> None:
            string pt
            mixed bing
            int lastage
            int nowage
            if ( sizeof( pts ) ) {
            pt = pts[ 0 ]
            nowage = get_age_uncached_offline( pt )
            lastage = nowage - playtesters[ pt ][ "age" ]
            classs[ pt ] = PLAYER_HANDLER.test_class( pt )
            ages[ pt ] = nowage
            bugs[ pt ] = ([ ])
            foreach ( string s in keys( playtesters[ pt ] ) -
            ["senior", "age", "current age", "class"] ) {
            bing = playtesters[ pt ][ s ]
            if ( arrayp( bing ) ) {
            bugs[ pt ][ s ] = [bing[ 0 ], bing[ 1 ], nowage]
            } else if ( intp( bing ) ) {
            bugs[ pt ][ s ] = [bing, lastage, nowage]


    def transfer_data_to_new_system(self, ) -> None:
            foreach ( string pt in keys( playtesters ) ) {
            if ( playtesters[ pt ][ "senior" ] )
            pts[ pt ] = SENIOR_PLAYTESTER
            else
            pts[ pt ] = NORMAL_PLAYTESTER


    def add_jump_point(self, from: str, to: str) -> None:
            if (!_jump_points[from]) {
            _jump_points[from] = [})


    def remove_jump_point_from(self, from: str) -> None:
            map_delete(_jump_points, from)
            save_file()


    def remove_jump_point(self, from: str, to: str) -> None:
            if (_jump_points[from]) {
            _jump_points[from] -= [to]
            if (!sizeof(_jump_points[from])) {
            map_delete(_jump_points, from)


    def add_pt_exec(self, name: str) -> int:
            if ( undefinedp (pts[ name ]))
            return 0
            log_file( "PLAYTESTERS", ctime( time() ) + ": " + name +
            " promoted to playtester executive by %s\n",
            this_player()->query_name() )
            executives += [name]
            save_file()
            return 1


    def remove_pt_exec(self, name: str) -> int:
            if ( !undefinedp (pts[ name ]))
            return 0
            if (member_array (name, executives) == -1) {
            return 0


    def query_pt_exec(self, name: str) -> int:
            if (member_array (name, executives) == -1) {
            return 0


    def query_exec_access(self, name: str) -> int:
            if (master()->query_senior(name)) {
            return 1



class Playtesters(MudObject):

    months = '[]'

    pts = '([ ])'

    ages = '([ ])'

    guilds = '([ ])'

    bugs = '([ ])'

    playtesters = '([ ])'

    leave = '([ ])'

    tmp_pts = '([ ])'

    _jump_points = '([ ])'

    executives = '[]'
