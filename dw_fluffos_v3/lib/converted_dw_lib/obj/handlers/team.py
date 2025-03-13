# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/team.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.members = ([ ])
            self.groups = ([ ])


    def dest_me(self, ) -> None:
            destruct(self)


    def leaving(self, p_name: str, type: str) -> None:
            class party record
            string g_name
            if((type != "logout") || (!members[p_name]))
            return
            g_name = members[p_name]
            record = (class party)partys[g_name]
            map_delete(members, p_name)
            if(!record)
            return
            if((record->leader == 0) || ((record->leader)->query_name() == p_name)) {
            disband_party(g_name, p_name)
            #ifdef LOG_FILE
            log_file(LOG_FILE, sprintf("%s %s has left the game, the %s has been "
            "disbanded.\n", ctime(time()), p_name, g_name))
            #endif
            } else {
            #ifdef LOG_FILE
            log_file(LOG_FILE, sprintf("%s %s left the game while a member of the %s\n",
            ctime(time()), p_name, g_name))
            #endif
            record->members = delete(record->members,
            record->members.index(0) if 0 in record->members else -1, 1)


    def new_group(self, g_name: str, leader: MudObject, policy: int) -> int:
            class party record
            if(!undefinedp(partys[g_name]))
            return 0
            record = new(class party)
            record->leader = leader
            record->policy = policy
            record->members = [leader]
            partys[g_name] = record
            members[leader.query_name()] = g_name
            leader.set_title( "TEAM", "Team Leader of "+ g_name )
            clone_object( SHADOW )->setup_shadow( leader )
            #ifdef LOG_FILE
            log_file(LOG_FILE, sprintf("%s %s created by %s\n", ctime(time()),
            g_name, leader.query_name()))
            #endif
            return 1


    def end_group(self, g_name: str) -> int:
            class party record
            object player
            if(undefinedp(partys[g_name]))
            return 0
            record = partys[g_name]
            foreach( player in record->members )
            if ( player ) {
            map_delete( members, player.query_name() )
            player.remove_title( "TEAM" )
            player.destruct_team_shadow()


    def join_group(self, g_name: str, player: MudObject) -> int:
            class party record
            if(undefinedp(partys[g_name]))
            return 0
            record = partys[g_name]
            record->members += [player]
            members[player.query_name()] = g_name
            player.set_title( "TEAM", "Team Member of "+ g_name )
            clone_object( SHADOW )->setup_shadow( player )
            #ifdef LOG_FILE
            log_file(LOG_FILE, sprintf("%s %s joined by %s\n", ctime(time()),
            g_name, player.query_name()))
            #endif
            return 1


    def leave_group(self, g_name: str, player: MudObject) -> int:
            class party record
            if(player) {
            map_delete(members, player.query_name())
            player.remove_title( "TEAM" )
            player.destruct_team_shadow()
            #ifdef LOG_FILE
            log_file(LOG_FILE, sprintf("%s %s left by %s\n", ctime(time()), g_name,
            player.query_name()))
            #endif


    def query_owner(self, g_name: str) -> MudObject:
            class party record
            if(undefinedp(partys[g_name]))
            return 0
            record = (class party)partys[g_name]
            return record->leader


    def query_policy(self, g_name: str) -> int:
            class party record
            if(undefinedp(partys[g_name]))
            return 0
            record = partys[g_name]
            return (int)record->policy


    def query_group(self, player: MudObject) -> str:
            if(undefinedp(members[player.query_name()]))
            return 0
            return members[player.query_name()]


    def test_group(self, g_name: str) -> int:
            if(undefinedp(partys[g_name]))
            return 0
            return 1


    def query_full(self, g_name: str) -> int:
            class party record
            object member
            if(undefinedp(partys[g_name]))
            return 0
            tidy_members(g_name)
            record = (class party)partys[g_name]
            if(sizeof(record->members) >= MAX_GROUP_SIZE)
            return 1
            return 0


    def query_locked(self, g_name: str) -> int:
            class party record
            if(undefinedp(partys[g_name]))
            return 0
            record = (class party)partys[g_name]
            return (record->locked)


    def set_locked(self, g_name: str, lock: int) -> int:
            class party record
            if(undefinedp(partys[g_name]))
            return 0
            record = (class party)partys[g_name]
            record->locked = lock
            return 1



class Team(MudObject):

    members = '([ ])'

    groups = '([ ])'
