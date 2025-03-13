# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/master/permission.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def add_senior(self, word: str) -> int:
            if ( !sizeof( filter( previous_object( -1 ), (: interactive( $1 ) :) ) ) ) {
            user_event( "inform", this_player()->query_name() +
            " illegally attempted to call add_senior( "+ word +
            " )", "cheat" )
            unguarded((: write_file, "/log/CHEAT", ctime( time() ) +
            ": illegal attempt to call add_senior( "+ word +
            " ).\n"+ back_trace() :))
            return 0


    def remove_senior(self, str: str) -> int:
            if (!sizeof(filter(previous_object(-1), (: interactive($1) :)))) {
            user_event( "inform", this_player()->query_cap_name()+
            " illegally attempted to call remove_senior("+str+")",
            "cheat")
            unguarded((: write_file, "/log/CHEAT", ctime(time())+": Illegal attempt "
            "to call remove_senior("+str+").\nBacktrace: "+
            back_trace() :))
            return 0


    def add_director(self, str: str) -> int:
            if (!sizeof(filter(previous_object(-1), (: interactive($1) :)))) {
            user_event( "inform", this_player()->query_cap_name()+
            " illegally attempted to call add_director("+str+")",
            "cheat")
            unguarded((: write_file, "/log/CHEAT", ctime(time())+
            ": Illegal attempt to call add_director("+str+
            ").\nBacktrace: "+ back_trace() :))
            return 0


    def remove_director(self, str: str) -> int:
            if (!sizeof(filter(previous_object(-1), (: interactive($1) :)))) {
            user_event( "inform", this_player()->query_cap_name()+
            " illegally attempted to call remove_director("+str+")",
            "cheat")
            unguarded((: write_file, "/log/CHEAT", ctime(time())+
            ": Illegal attempt to call remove_director("+str+
            ").\nBacktrace: "+ back_trace() :))
            return 0


    def add_trustee(self, str: str) -> int:
            if (!sizeof(filter(previous_object(-1), (: interactive($1) :)))) {
            user_event( "inform", this_player()->query_cap_name()+
            " illegally attempted to call add_tristee("+str+")",
            "cheat")
            unguarded((: write_file, "/log/CHEAT", ctime(time())+": Illegal attempt "
            "to call add_trustee("+str+").\nBacktrace: "+
            back_trace() :))
            return 0


    def remove_trustee(self, str: str) -> int:
            if (!sizeof(filter(previous_object(-1), (: interactive($1) :)))) {
            user_event( "inform", this_player()->query_cap_name()+
            " illegally attempted to call remove_trustee("+str+")",
            "cheat")
            unguarded((: write_file, "/log/CHEAT", ctime(time())+": Illegal attempt "
            "to call remove_trustee("+str+").\nBacktrace: "+
            back_trace() :))
            return 0


    def permission_match_path(self, m: Any, path: str) -> Any:
            string p, *bits
            int i, size
            mapping found = ([])
            if (!sizeof(m)) {
            return 0


    def valid_grant(self, euid: MudObject, path: str, mask: int) -> int:
            string domain, master, director
            int result
            object master_ob
            if (path[0] != '/')
            path = "/" + path
            result = check_permission(euid, 0, path,
            permission_match_path(permissions, path),
            GRANT_MASK)
            if (!result || (mask & (READ_MASK|WRITE_MASK)))
            return result
            if (sscanf(path, "/d/%s/%*s", domain) != 2 &&
            sscanf(path, "/d/%s", domain) != 1)
            return 0
            master = "/d/" + domain + "/master"
            if (!(master_ob = find_object(master)) && checked_master[master])
            return 0
            if (!master_ob && !checked_master[master] &&
            catch(master_ob = load_object(master))) {
            checked_master[master] = 1
            return 0


    def add_read_permission(self, euid: str, path: str) -> int:
            if ( base_name(previous_object()) != "/d/admin/room/access_control" &&
            base_name(previous_object()) != "/cmds/creator/perm_it") {
            user_event( "inform", this_interactive()->query_cap_name()+
            " illegally attempted to call add_read_permission("+euid+", "+
            path+")", "cheat")
            unguarded((: write_file, "/log/CHEAT", ctime(time())+": Illegal attempt "
            "to call add_read_permission("+euid+", "+path+").\nBacktrace: "+
            back_trace() :))
            return 0


    def add_write_permission(self, euid: str, path: str) -> int:
            if ( base_name(previous_object()) != "/d/admin/room/access_control" &&
            base_name(previous_object()) != "/cmds/creator/perm_it") {
            user_event( "inform", this_player(1)->query_cap_name()+
            " illegally attempted to call add_write_permission("+euid+", "+
            path+")", "cheat")
            unguarded((: write_file, "/log/CHEAT", ctime(time())+": Illegal attempt "
            "to call add_write_permission("+euid+", "+path+").\n"
            "Backtrace: "+ back_trace() :))
            return 0


    def add_grant_permission(self, euid: str, path: str) -> int:
            if ( base_name(previous_object()) != "/d/admin/room/access_control" &&
            base_name(previous_object()) != "/cmds/creator/perm_it") {
            user_event( "inform", this_player(1)->query_cap_name()+
            " illegally attempted to call add_grant_permission("+euid+", "+
            path+")", "cheat")
            unguarded((: write_file, "/log/CHEAT", ctime(time())+": Illegal attempt "
            "to call add_grant_permission("+euid+", "+path+").\n"
            "Backtrace: "+ back_trace() :))
            return 0


    def lock_path(self, path: str) -> int:
            if ( base_name(previous_object()) != "/d/admin/room/access_control" &&
            base_name(previous_object()) != "/cmds/creator/perm_it") {
            user_event("inform", this_player(1)->query_cap_name()+
            " illegally attempted to call lock_path("+path+")", "cheat")
            unguarded((: write_file, "/log/CHEAT", ctime(time())+": Illegal attempt "
            "to call lock_path("+path+").\nBacktrace: "+ back_trace() :))
            return 0


    def remove_read_permission(self, euid: str, path: str) -> int:
            if ( base_name(previous_object()) != "/d/admin/room/access_control" &&
            base_name(previous_object()) != "/cmds/creator/perm_it") {
            user_event( "inform", this_player(1)->query_cap_name()+
            " illegally attempted to call remove_read_permission("+euid+
            ", "+path+")", "cheat")
            unguarded((: write_file, "/log/CHEAT", ctime(time())+": Illegal attempt "
            "to call remove_read_permission("+euid+", "+path+").\n"
            "Backtrace: "+ back_trace() :))
            return 0


    def remove_write_permission(self, euid: str, path: str) -> int:
            if ( base_name(previous_object()) != "/d/admin/room/access_control" &&
            base_name(previous_object()) != "/cmds/creator/perm_it") {
            user_event( "inform", this_player(1)->query_cap_name()+
            " illegally attempted to call remove_write_permission("+euid+
            ", "+path+")", "cheat")
            unguarded((: write_file, "/log/CHEAT", ctime(time())+": Illegal attempt "
            "to call remove_write_permission("+euid+", "+path+").\n"
            "Backtrace: "+ back_trace() :))
            return 0


    def remove_grant_permission(self, euid: str, path: str) -> int:
            if ( base_name(previous_object()) != "/d/admin/room/access_control" &&
            base_name(previous_object()) != "/cmds/creator/perm_it") {
            user_event( "inform", this_player(1)->query_cap_name()+
            " illegally attempted to call remove_grant_permission("+euid+
            ", "+path+")", "cheat")
            unguarded((: write_file, "/log/CHEAT", ctime(time())+": Illegal attempt "
            "to call remove_grant_permission("+euid+", "+path+").\n"
            "Backtrace: "+ back_trace() :))
            return 0


    def unlock_path(self, path: str) -> int:
            if ( base_name(previous_object()) != "/d/admin/room/access_control" &&
            base_name(previous_object()) != "/cmds/creator/perm_it") {
            user_event("inform", this_player(1)->query_cap_name()+
            " illegally attempted to call unlock_path("+path+")", "cheat")
            unguarded((: write_file, "/log/CHEAT", ctime(time())+": Illegal attempt "
            "to call unlock_path("+path+").\nBacktrace: "+ back_trace() :))
            return 0



class Permission(MudObject):
