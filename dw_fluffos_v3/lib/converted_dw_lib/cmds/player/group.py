# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/group.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def rehash_group_sub_commands(self, ) -> None:
            mixed *files
            object cmd_object
            string dir, verb, file, pattern
            _sub_commands = ([ ])
            dir = GROUP_SUB_CMDS_DIR
            dir += GROUP_SUB_CMDS_FILE_WILDCARD
            files = get_dir( dir )
            if( !sizeof( files ) ) {
            return


    def do_help(self, on_what: str) -> int:
            int top_left
            string help, message
            object command
            on_what = lower_case( on_what )
            #if defined( IN_TESTING ) || defined( IN_STRICT_TESTING )
            if( !allowed_to_use( this_player() ) ) {
            return 0


    def make_patterns_array(self, ) -> None:
            int count, size
            string verb, pattern
            class sub_command command
            _patterns = [})
            _patterns += ({
            "help <word'sub-command'>", (: do_help( $4[ 0 ] ) :)]
            foreach( verb, command in _sub_commands ) {
            size = sizeof( command->data )
            for( count = 0; count < size; count += 2 ) {
            if( sizeof( command->data[ count ] ) ) {
            pattern = verb + " " + command->data[ count  ]


    def allowed_to_use(self, user: MudObject) -> int:
            #endif
            #ifdef IN_STICT_TESTING
            if( !user.query_creator() ) {
            tell_object( user, "You are not allowed to use this feature at this "
            "time.\n" )
            return 0



class Group(MudObject):
