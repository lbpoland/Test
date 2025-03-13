# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/bastards.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.site_access = ([ ])
            self.suspended = ([ ])
            self.lockedout = ([ ])
            self.multiuser = ([ ])
            self.temp_passwords = ([ ])
            self.site_access = ([ ])


    def __init__(self):
            self.site_access = ([ ])
            self.suspended = ([ ])
            self.lockedout = ([ ])
            self.multiuser = ([ ])
            self.temp_passwords = ([ ])
            self.site_access = ([ ])
            if(!lockedout)
            lockedout = ([ ])
            if(!multiuser)
            multiuser = ([ ])
            if(!temp_passwords) {
            temp_passwords = ([ ])


    def query_player_ob(self, name: str) -> str:
            if("/secure/master"->query_administrator(name) ||
            "/secure/master"->query_lord(name))
            return "/global/lord"
            if (PLAYER_HANDLER.test_creator(name))
            return "/global/creator"
            if (PLAYTESTER_HAND.query_playtester(name))
            return "/global/playtester"
            return "/global/player"


    def query_access(self, ob: MudObject) -> int:
            string tmp
            tmp = query_ip_number(ob)
            while(strlen(tmp)) {
            if(site_access[tmp])
            return site_access[tmp][ACCESS_LEVEL]
            tmp = implode((string *)explode(tmp, ".")[0..<2], ".")


    def query_multi(self, ob: MudObject) -> int:
            string tmp
            tmp = query_ip_number(ob)
            while(strlen(tmp)) {
            if(multiuser[tmp])
            return 1
            tmp = implode((string *)explode(tmp, ".")[0..<2], ".")


    def query_reason(self, address: str) -> str:
            if(site_access[address])
            return site_access[address][ACCESS_REASON]
            return 0


    def change_access(self, address: str, level: int, reason: str, timeout: int) -> int:
            if(!master()->query_lord(previous_object(-1)) &&
            base_name(previous_object()) != "/cmds/creator/ban")
            return 0
            if(!stringp(address) || !reason)
            return notify_fail("Invalid parameters.\n")
            if (!timeout)
            timeout = time() + 100 * 24 * 60 * 60
            add_access(address, level, reason, timeout)
            save_me()
            unguarded((: write_file, "/log/ACCESS", ctime(time())[4..16] + " " +
            address+" set to " + PERM_NAMES[level] + " for " + reason +
            " until " + ctime(timeout) + " by "+
            this_player()->query_name()+".\n" :))
            return 1


    def change_multi(self, address: str, multi: int, timeout: int) -> int:
            if(!master()->query_lord(previous_object(-1)) &&
            base_name(previous_object()) != "/cmds/creator/multipl_ayer")
            return 0
            if(!stringp(address))
            return notify_fail("Invalid parameters.\n")
            if (!timeout)
            timeout = time() + 100 * 24 * 60 * 60
            add_multi(address, multi, timeout)
            save_me()
            unguarded((: write_file, "/log/ACCESS", ctime(time())[4..16] + " " +
            address+" set to " + (multi?"allow":"disallow") +
            " multiple users until " + ctime(timeout) + " by "+
            this_player()->query_name()+".\n" :))
            return 1


    def suspend_person(self, str: str, tim: int, reason: str) -> int:
            if (!master()->query_lord(previous_object(-1)) &&
            base_name(previous_object()) != "/cmds/creator/suspend") {
            return 0


    def unsuspend_person(self, str: str) -> int:
            if (!"/secure/master"->query_lord(previous_object(-1)) &&
            base_name(previous_object()) !="/cmds/creator/unsuspend") {
            return 0


    def lockout_person(self, str: str, tim: int, reason: str) -> int:
            if (!master()->query_lord(previous_object(-1)) &&
            base_name(previous_object()) != "/cmds/player/lockout") {
            return 0


    def set_temp_password(self, name: str, pass: str) -> int:
            temp_passwords[name] = [time(), pass]
            save_me()
            return 1


    def clear_temp_password(self, name: str) -> None:
            if(temp_passwords[name]) {
            map_delete(temp_passwords, name)
            save_me()



class Bastards(MudObject):

    site_access = '([ ])'

    suspended = '([ ])'

    lockedout = '([ ])'

    multiuser = '([ ])'

    temp_passwords = '([ ])'
