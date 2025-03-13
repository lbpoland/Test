# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/master/directory_assignments.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def query_leader(self, name: str) -> int:
            string* query_assigned_to_directory(string dir) {
            string *bits
            string str
            int i
            bits = explode(dir, "/") - [""]
            switch (bits[0]) {
            case "w" :
            if (sizeof(bits) > 1 && file_size("/d/" + bits[1]) == -2) {
            return [bits[1]]


    def assign_people_to_directory(self, dir: str, people: Any) -> int:
            string* new_people
            string* dirs
            if ( !sizeof( filter( previous_object( -1 ), (: interactive( $1 ) :) ) ) ) {
            user_event( "inform", this_player()->query_name() +
            " illegally attempted to call assign_person_to_directory( "+ dir +
            ", " + query_multiple_short(people) +
            " )", "cheat" )
            unguarded((: write_file, "/log/CHEAT", ctime( time() ) +
            ": illegal attempt to call assign_person_to_directory( "+ dir +
            ", " + query_multiple_short(people) +
            " ).\n"+ back_trace() :))
            return 0



class Directory_assignments(MudObject):
