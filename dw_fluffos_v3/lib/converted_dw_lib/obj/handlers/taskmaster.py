# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/taskmaster.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.critical_chances = allocate(100)
            self.a = 0.93260
            self.b = 0.06978
            self.for( int i = 0; i < 100; i++ ) {
            self.critical_chances[i] = a * exp( b * ( i + 1 ) )


    def __init__(self):
            self.critical_chances = allocate(100)
            self.a = 0.93260
            self.b = 0.06978
            self.for( int i = 0; i < 100; i++ ) {
            self.critical_chances[i] = a * exp( b * ( i + 1 ) )


    def award_made(self, p_name: str, o_name: str, s_name: str, level: int) -> None:
            user_event( "inform", p_name +" gains a level in "+ s_name +" from "+
            o_name + " at level " + level, "skill" )
            #ifdef LOG_STATS
            #if LOG_STATS == 1
            query_stats( s_name )
            if ( !stats[ level ] )
            stats[ level ] = ([ ])
            stats[ level ][ explode( o_name, "#" )[ 0 ] ]++
            #else
            query_stats("summary")
            if(s_name[<7..] == ".points" || s_name[0..13] == "other.language")
            return
            s_name = explode(s_name, ".")[0]
            if(!stats[s_name])
            stats[s_name] = [[0 , 0],  [0, 0],  [0, 0] , ({0,0})})
            switch(level) {
            case 0..149:
            stats[s_name][0] = [stats[s_name][0][0], stats[s_name][0][1]+1]
            break
            case 150..299:
            stats[s_name][1] = [stats[s_name][1][0], stats[s_name][1][1]+1]
            break
            case 300..599:
            stats[s_name][2] = [stats[s_name][2][0], stats[s_name][2][1]+1]
            break
            default:
            stats[s_name][3] = [stats[s_name][3][0], stats[s_name][3][1]+1]
            break


    def skill_checked(self, s_name: str, level: int) -> None:
            query_stats("summary")
            if(s_name[<7..] == ".points" || s_name[0..13] == "other.language")
            return
            s_name = explode(s_name, ".")[0]
            if(!stats[s_name])
            stats[s_name] = [({0,0}), ({0,0}), ({0,0}), ({0,0}), ({0,0})]
            switch(level) {
            case 0..49:
            stats[s_name][0] = [stats[s_name][0][0]+1, stats[s_name][0][1]]
            break
            case 50..149:
            stats[s_name][1] = [stats[s_name][1][0]+1, stats[s_name][1][1]]
            break
            case 150..299:
            stats[s_name][2] = [stats[s_name][2][0]+1, stats[s_name][2][1]]
            break
            case 300..599:
            stats[s_name][3] = [stats[s_name][3][0]+1, stats[s_name][3][1]]
            break
            default:
            stats[s_name][4] = [stats[s_name][4][0]+1, stats[s_name][4][1]]
            break


    def clear_skill_files(self, ) -> None:
            string word
            foreach ( word in unguarded( (: get_dir, SAVE_FILES +"*.o" :) ) )
            unguarded( (: rm, SAVE_FILES + word :) )
            skill = 0


    def is_critical(self, margin: int) -> int:
            if ( margin < 0 ) {
            margin *= -1



class Taskmaster(MudObject):

    critical_chances = 'allocate(100)'

    a = '0.93260'

    b = '0.06978'

    for( int i = '0; i < 100; i++ ) {'

    critical_chances[i] = 'a * exp( b * ( i + 1 ) )'
