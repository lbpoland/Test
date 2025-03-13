# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/playtester/jumps.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def do_list(self, ) -> int:
            mapping jumps
            string str
            string start
            string tmp
            string* dest
            object there
            object to_there
            object* theres
            jumps = PLAYTESTER_HAND.query_jump_points()
            if (!sizeof(jumps)) {
            add_failed_mess("No current jumps.\n")
            return 0


    def do_list_from_here(self, ) -> int:
            string* dest
            string here
            string str
            string tmp
            object to_there
            int pos
            here = file_name(environment(this_player()))
            dest = PLAYTESTER_HAND.query_jump_destination(here)
            if (sizeof(dest)) {
            str = ""
            foreach (tmp in dest) {
            if ( !( to_there = find_object( tmp ) ) ) {
            catch(load_object(tmp))
            to_there = find_object( tmp )
            if ( !to_there ) {
            str += sprintf( "$I$3=%s will not load, please contact %s.\n",
            tmp, "Someone happy" )
            return 1


    def do_jump(self, id: str) -> int:
            string here
            string* dest
            string real_dest
            object to_there
            int pos
            if (strlen(id) > 1) {
            add_failed_mess("The id to jump to must be a single letter.\n")
            return 0


    def do_armoury(self, ) -> int:
            string env
            string ret
            object ob
            env = file_name(environment(this_player()))
            if (environment(this_player())->query_armoury()) {
            ret = this_player()->query_property("pt return")
            if (ret) {
            if (strsrch(ret, "#") != -1) {
            if (!find_object(ret)) {
            ret = 0



class Jumps(MudObject):
