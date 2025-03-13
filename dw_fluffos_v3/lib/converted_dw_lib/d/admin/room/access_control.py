# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/admin/room/access_control.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_light(100)
            set_short("file-access control room")
            add_property("determinate", "the ")
            set_long(
            "You are in a room full of filing cabinets.  There are filing "
            "cabinets everywhere, they are all packed full of papers and look "
            "in a horrible mess.\n"
            "Available commands:\n"
            "  read    <euid> <path>     : add read permission to the path.\n"
            "  write   <euid> <path>     : add write permission to the path.\n"
            "  grant   <euid> <path>     : add granting privileges to the path.\n"
            "  lock           <path>     : restrict access to the path.\n"
            "  noread  <euid> <path>     : remove read permission from the path.\n"
            "  nowrite <euid> <path>     : remove write permission from the path.\n"
            "  nogrant <euid> <path>     : remove granting privileges to the path.\n"
            "  unlock         <path>     : remove restrictions to path.\n"
            "  summary [path|euid]       : give a list of all the read/write perms.\n"
            "  tidy                      : tidy away unnecessary perms.\n" )
            add_exit("east", ROOM+"domain_control", "corridor")


    def init(self, ) -> None:
            ::init()
            this_player()->add_command("read",    self,
            "<string'euid'> <string'path'>", (: do_read($4[0], $4[1]) :) )
            this_player()->add_command("write",   self,
            "<string'euid'> <string'path'>", (: do_write($4[0], $4[1]) :) )
            this_player()->add_command("grant",   self,
            "<string'euid'> <string'path'>", (: do_grant($4[0], $4[1]) :) )
            this_player()->add_command("lock",    self,
            "<string'path'>",                (: do_lock($4[0]) :) )
            this_player()->add_command("noread",  self,
            "<string'euid'> <string'path'>", (: do_noread($4[0], $4[1]) :) )
            this_player()->add_command("nowrite", self,
            "<string'euid'> <string'path'>", (: do_nowrite($4[0], $4[1]) :) )
            this_player()->add_command("nogrant", self,
            "<string'euid'> <string'path'>", (: do_nogrant($4[0], $4[1]) :) )
            this_player()->add_command("unlock",  self,
            "<string'path'>",                (: do_unlock($4[0]) :) )
            this_player()->add_command("summary", self,
            "<string'path or euid'>",        (: do_summary($4[0]) :) )
            this_player()->add_command("tidy",    self,
            "",                              (: do_tidy() :) )


    def do_read(self, euid: str, path: str) -> int:
            if (!sizeof(filter(previous_object(-1), (: interactive($1) :)))) {
            event(users(), "inform", "Illegal attempt to call do_read("+euid+", "+path+") by "+
            this_player()->one_short(), "cheat")
            unguarded((: write_file, "/log/CHEAT", ctime(time())+": Illegal attempt "
            "to call do_read("+euid+", "+path+").\nBacktrace: "+ back_trace() :))
            return 0


    def do_write(self, euid: str, path: str) -> int:
            if (!sizeof(filter(previous_object(-1), (: interactive($1) :)))) {
            event(users(), "inform", "Illegal attempt to call do_write("+euid+", "+path+") by "+
            this_player()->one_short(), "cheat")
            unguarded((: write_file, "/log/CHEAT", ctime(time())+": Illegal attempt "
            "to call do_write("+euid+", "+path+").\nBacktrace: "+ back_trace() :))
            return 0


    def do_grant(self, euid: str, path: str) -> int:
            if (!sizeof(filter(previous_object(-1), (: interactive($1) :)))) {
            event(users(), "inform", "Illegal attempt to call do_grant("+euid+", "+path+") by "+
            this_player()->one_short(), "cheat")
            unguarded((: write_file, "/log/CHEAT", ctime(time())+": Illegal attempt "
            "to call do_grant("+euid+", "+path+").\nBacktrace: "+ back_trace() :))
            return 0


    def do_lock(self, path: str) -> int:
            if (!sizeof(filter(previous_object(-1), (: interactive($1) :)))) {
            event(users(), "inform", "Illegal attempt to call do_lock("+path+") by "+
            this_player()->one_short(), "cheat")
            unguarded((: write_file, "/log/CHEAT", ctime(time())+": Illegal attempt "
            "to call do_lock("+path+").\nBacktrace: "+ back_trace() :))
            return 0


    def do_noread(self, euid: str, path: str) -> int:
            if (!sizeof(filter(previous_object(-1), (: interactive($1) :)))) {
            event(users(), "inform", "Illegal attempt to call do_noread("+euid+", "+path+") by "+
            this_player()->one_short(), "cheat")
            unguarded((: write_file, "/log/CHEAT", ctime(time())+": Illegal attempt "
            "to call do_noread("+euid+", "+path+").\nBacktrace: "+ back_trace() :))
            return 0


    def do_nowrite(self, euid: str, path: str) -> int:
            if (!sizeof(filter(previous_object(-1), (: interactive($1) :)))) {
            event(users(), "inform", "Illegal attempt to call do_nowrite("+euid+", "+path+") by "+
            this_player()->one_short(), "cheat")
            unguarded((: write_file, "/log/CHEAT", ctime(time())+": Illegal attempt "
            "to call do_nowrite("+euid+", "+path+").\nBacktrace: "+ back_trace() :))
            return 0


    def do_nogrant(self, euid: str, path: str) -> int:
            if (!sizeof(filter(previous_object(-1), (: interactive($1) :)))) {
            event(users(), "inform", "Illegal attempt to call do_nogrant("+euid+", "+path+") by "+
            this_player()->one_short(), "cheat")
            unguarded((: write_file, "/log/CHEAT", ctime(time())+": Illegal attempt "
            "to call do_nogrant("+euid+", "+path+").\nBacktrace: "+ back_trace() :))
            return 0


    def do_unlock(self, path: str) -> int:
            if (!sizeof(filter(previous_object(-1), (: interactive($1) :)))) {
            event(users(), "inform", "Illegal attempt to call do_unlock("+path+") by "+
            this_player()->one_short(), "cheat")
            unguarded((: write_file, "/log/CHEAT", ctime(time())+": Illegal attempt "
            "to call do_unlock("+path+").\nBacktrace: "+ back_trace() :))
            return 0


    def list_before(self, first: str, second: str) -> int:
            if ( first < second )
            return -1
            if ( first > second )
            return 1
            return 0


    def do_summary(self, str: str) -> int:
            mapping perms
            string *paths, *euids, ret, creator
            int i, j, k
            perms = (mapping)master()->query_permissions()
            if (str) {
            if (!perms[str]) {
            if (!LOGIN.test_user(str) && !master()->valid_euid(str)) {
            write("There are no permissions for "+str+".\n")
            return 1
            } else {
            creator = str


    def do_tidy(self, ) -> int:
            int i, j, perm, same
            string path, creator, *bits
            mapping perms, euids, others
            if (!sizeof(filter(previous_object(-1), (: interactive($1) :)))) {
            event( users(), "inform", "illegal attempt to call do_tidy() by "+
            (string)this_player()->query_name(), "cheat" )
            unguarded((: write_file, "/log/CHEAT", ctime( time() ) +": illegal "
            "attempt to call do_tidy() by "+
            (string)this_player()->query_name() +"\n" :))
            return notify_fail( "Failed.\n" )



class Access_control(MudObject):
