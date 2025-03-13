# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/admin/obj/inv_check.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def save_me(self, ) -> None:
            unguarded ((: save_object (FILENAME) :))


    def dest_me(self, ) -> None:
            destruct( self )
            save_me()


    def __init__(self):


    def log_it(self, ) -> None:
            if( sizeof( to_log ) > 0 ) {
            log_file( "ILLEGAL_OBJECT",
            "Illegal objects removed %s\n%s\n",
            ctime( time() ),
            to_log )


    def check_sub_inv(self, things: MudObject, owner: str, owner_ob: MudObject) -> None:
            string *pre_filename, filename, *switcher
            object *obs, thing
            object *contents, *fragile
            string mess = ""
            object bag
            obs = [})
            foreach ( thing in things ) {
            if ( thing.query_property( "virtual name" ) ) {
            filename = thing.query_property( "virtual name" )
            } else {
            pre_filename = explode( file_name( thing ),"#" )
            filename = pre_filename[ 0 ]


    def check_obs(self, obs: Any) -> None:
            object thing
            foreach( thing in obs ) {
            if( thing ) {
            thing.dest_me()


    def check_inv(self, player: MudObject) -> None:
            object *things
            things = deep_inventory( player )
            check_sub_inv( things, (string)player.query_name(), player )


    def do_seek(self, ) -> int:
            object user
            to_log = ""
            foreach ( user in users() ) {
            if( user && !user.query_property( "guest" ) &&
            !user.query_creator() &&
            !PLAYTESTER_HAND->query_tester (user) &&
            !user->query_property ("test character") ) {
            check_inv( user )


    def parse_filename(self, str: str) -> str:
            if (strsrch (str, ".wep") != -1 ||
            strsrch (str, ".clo") != -1 ||
            strsrch (str, ".ob") != -1 ||
            strsrch (str, ".arm") != -1 ||
            strsrch (str, ".food") != -1 ||
            strsrch (str, ".sca") != -1) {
            if (file_size(str) <= 0) {
            return 0


    def ban_object(self, filename: str) -> int:
            if (!master()->query_lord(previous_object(-1))) {
            printf ("Please get a lord to ban your object for you.\n")
            return 0


    def unban_object(self, filename: str) -> int:
            if (!master()->query_lord(previous_object(-1))) {
            printf ("Please get a lord to unban your object for you.\n")
            return 0


    def list_banned(self, ) -> str:
            if (sizeof (forbidden)) {
            return sprintf ("Objects cloned from the following filenames "
            "will be confiscated by the dwarves:\n%s\n",
            implode (forbidden, "\n"))


    def stats(self, ) -> Any:
            {
            return ({
            ["Time until next tick", query_num (find_call_out ("do_seek"))
            + " seconds"}),
            })



class Inv_check(MudObject):
