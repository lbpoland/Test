# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/perm_it.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, command: str, euid: str, path: str) -> Any:
            string* euids
            string* bing
            if (this_player() != this_player(1)) {
            return 0


    def do_directory_summary(self, dir: str) -> int:
            mapping assignments
            mapping new_assignments
            string* paths
            string path
            string ret
            string domain
            assignments = master()->query_directory_assignments()
            foreach (domain in master()->query_domains()) {
            ret = catch(new_assignments = ("/d/" + domain + "/master")->query_directory_assignments())
            if (sizeof(new_assignments)) {
            assignments += new_assignments


    def do_directory_update(self, dir: str) -> int:
            mapping assignments
            mapping new_assignments
            string* paths
            string path
            string ret
            string domain
            string* bits
            assignments = master()->query_directory_assignments()
            foreach (domain in master()->query_domains()) {
            ret = catch(new_assignments = ("/d/" + domain + "/master")->query_directory_assignments())
            if (sizeof(new_assignments)) {
            assignments += new_assignments


    def do_summary(self, str: str) -> int:
            mapping perms
            string *paths, *euids, ret, creator
            int i, j, k
            perms = (mapping)master()->query_permissions()
            if (str) {
            if (!perms[str]) {
            if (!PLAYER_HANDLER.test_user(str) && !master()->valid_euid(str)) {
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


    def help(self, ) -> int:
            write("Available commands:\n"
            "  read    <euid> <path>     : add read permison to the path.\n"
            "  write   <euid> <path>     : add write permission to the path.\n"
            "  grant   <euid> <path>     : add granting privileges to the path.\n"
            "  lock           <path>     : restrict access to the path.\n"
            "  noread  <euid> <path>     : remove read permission from the path.\n"
            "  nowrite <euid> <path>     : remove write permission from the path.\n"
            "  nogrant <euid> <path>     : remove granting privileges to the path.\n"
            "  unlock         <path>     : remove restrictions to path.\n"
            "  summary [path|euid]       : give a list of all the read/write perms.\n"
            "  tidy                      : tidy away unnecessary perms.\n"
            "  assign <euid> <path>      : assigns someone to look after a directory.\n"
            "  assignment summary        : summary of directory assignments.\n" )
            return 1



class Perm_it(MudObject):
