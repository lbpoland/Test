# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/player_handler.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.player_ob = "/global/player"
            self.player_cache = ([ ])


    def my_find_player(self, player: str) -> MudObject:
            string *funs, stack = ""
            object *obs
            int i
            if(prev_name == player)
            return find_player(player)
            prev_name = player
            if (base_name(previous_object()) == prev_find && delay > time() - 60 &&
            prev_name == player) {
            prev_finds++
            } else {
            prev_finds = 1
            delay = time()
            prev_find = base_name(previous_object())


    def clean_cache(self, ) -> None:
            string name
            foreach(name in keys(player_cache)) {
            if (player_cache[name]->cached < time() - CACHE_TIMEOUT) {
            map_delete(player_cache, name)


    def remove_cache_entry(self, name: str) -> None:
            map_delete(player_cache, name)


    def query_player_file_name(self, name: str) -> str:
            #ifdef USE_RAMDISK
            if(PLAYER_RAM_DIR) {
            if(file_size(PLAYER_RAM_DIR + name[0..0] + "/" + name + ".o.gz") == -1) {
            if(file_size(PLAYER_SAVE_DIR + name[0..0] + "/" + name + ".o.gz") > -1) {
            unguarded((: cp,
            PLAYER_SAVE_DIR + name[0..0] + "/" + name + ".o.gz",
            PLAYER_RAM_DIR + name[0..0] + "/" + name + ".o.gz" :))
            } else if((file_size(PLAYER_SAVE_DIR+name[0..0]+"/"+name+".o") >-1)) {
            unguarded((: cp,
            PLAYER_SAVE_DIR + name[0..0] + "/" + name + ".o",
            PLAYER_RAM_DIR + name[0..0] + "/" + name + ".o" :))
            unguarded((: compress_file,
            PLAYER_RAM_DIR + name[0..0] + "/" + name + ".o" :))


    def query_player_ram_file_name(self, name: str) -> str:
            return PLAYER_RAM_DIR + name[0..0] + "/" + name


    def query_player_disk_file_name(self, name: str) -> str:
            return PLAYER_SAVE_DIR + name[0..0] + "/" + name


    def query_delete_player_file_name(self, name: str) -> str:
            return PLAYER_SAVE_DIR + DELETE_DIR + "/" + name


    def query_appeal_player_file_name(self, name: str) -> str:
            return PLAYER_SAVE_DIR + APPEAL_DIR + "/" + name


    def load_player(self, name: str) -> int:
            class player_record tmp
            mixed *file
            int diff, deleting, appealing
            string tstr, fname
            object loaded_class_ob
            if (!validate_name(name)) {
            return 0


    def make_string(self, al: Any, max: int) -> str:
            string str
            int i
            int lines
            str = ALIAS_CMD.alias_string(al)
            sscanf(str, "%s $*$", str)
            str = replace(str, sprintf("%c", 7), "^G")
            str = replace(str, ["@@", "@ @ ", "\\;", "$escaped$", ";", "\n",
            "$escaped$", ";"])
            for (i = lines = 0; i < sizeof(str) && i < max*80 && lines < max; i++) {
            if (str[i] == '\n' || str[i] == ';') {
            lines++


    def test_user(self, str: str) -> int:
            if (player_cache[str])
            return 1
            if (!validate_name(str))
            return 0
            return file_size(query_player_disk_file_name(str) + ".o.gz") > 0 ||
            file_size(query_player_disk_file_name(str) + ".o") > 0 ||
            file_size(PLAYER_RAM_DIR + str[0..0] + "/" + str + ".o.gz") > 0 ||
            file_size(PLAYER_RAM_DIR + str[0..0] + "/" + str + ".o") > 0 ||
            file_size(query_delete_player_file_name(str) + ".o.gz") > 0 ||
            file_size(query_delete_player_file_name(str) + ".o") > 0 ||
            file_size(query_appeal_player_file_name(str) + ".o.gz") > 0 ||
            file_size(query_appeal_player_file_name(str) + ".o") > 0


    def test_deleting(self, str: str) -> int:
            if (player_cache[str])
            return player_cache[str]->deleting
            if (!validate_name(str))
            return 0
            if (file_size(query_delete_player_file_name(str) + ".o") > 0)
            return stat(query_delete_player_file_name(str) + ".o")[1]
            if(file_size(query_delete_player_file_name(str) + ".o.gz") > 0)
            return stat(query_delete_player_file_name(str) + ".o.gz")[1]
            return 0


    def test_appealing(self, str: str) -> int:
            if (player_cache[str])
            return player_cache[str]->appealing
            if (!validate_name(str))
            return 0
            if (file_size(query_appeal_player_file_name(str) + ".o") > 0)
            return stat(query_appeal_player_file_name(str) + ".o")[1]
            if(file_size(query_appeal_player_file_name(str) + ".o.gz") > 0)
            return stat(query_appeal_player_file_name(str) + ".o.gz")[1]
            return 0


    def test_gender(self, str: str) -> int:
            if (find_player(str)) {
            map_delete(player_cache, str)
            return find_player(str)->query_gender()


    def query_cap_name(self, str: str) -> str:
            if (find_player(str)) {
            map_delete(player_cache, str)
            return find_player(str)->query_cap_name()


    def test_level(self, str: str) -> int:
            if (find_player(str)) {
            map_delete(player_cache, str)
            return find_player(str)->query_level()


    def query_guild_data(self, ) -> Any:
            return class_data


    def query_skill(self, skill: str) -> int:
            if (mapp(new_skills)) {
            return new_skills[skill]


    def test_banished(self, name: str) -> int:
            return file_size(BANISH_DIR + name[0..0] + "/" + name + ".o") != -1


    def test_real_name(self, str: str) -> str:
            if (find_player(str)) {
            map_delete(player_cache, str)
            return find_player(str)->query_real_name()


    def test_email(self, str: str) -> str:
            if(file_name(previous_object())[0..13] != "/secure/finger" &&
            file_name(previous_object())[0..12] != "/secure/login" &&
            file_name(previous_object())[0..13] != "/secure/nlogin")
            return ""
            if (find_player(str)) {
            map_delete(player_cache, str)
            return find_player(str)->query_email()


    def test_birthday(self, str: str) -> str:
            if (find_player(str)) {
            map_delete(player_cache, str)
            return find_player(str)->query_birthday()


    def test_location(self, str: str) -> str:
            if (find_player(str)) {
            map_delete(player_cache, str)
            return find_player(str)->query_where()


    def test_homepage(self, str: str) -> str:
            if (find_player(str)) {
            map_delete(player_cache, str)
            return find_player(str)->query_homepage()


    def test_desc(self, str: str) -> str:
            if (find_player(str)) {
            map_delete(player_cache, str)
            return find_player(str)->query_desc()


    def test_player_killer(self, word: str, str: str) -> Any:
            if (find_player(word)) {
            map_delete(player_cache, word)
            return find_player(word)->query_player_killer()


    def test_property(self, word: str, str: str) -> Any:
            if (find_player(word)) {
            map_delete(player_cache, word)
            return find_player(word)->query_property(str)


    def special_add_property(self, pname: str, prop: str, val: Any) -> None:
            if(player_cache[pname])
            player_cache[pname]->map_prop[prop] = val


    def test_deity(self, word: str) -> str:
            if (find_player(word)) {
            map_delete(player_cache, word)
            return find_player(word)->query_deity()


    def test_guild(self, word: str) -> str:
            if (find_player(word)) {
            map_delete(player_cache, word)
            return find_player(word)->query_class_ob()


    def test_age(self, word: str) -> int:
            if (find_player(word)) {
            map_delete(player_cache, word)
            return find_player(word)->query_time_on()


    def test_last(self, word: str, noload: int) -> int:
            mixed *file
            if (find_player(word)) {
            map_delete(player_cache, word)
            return find_player(word)->query_last_log_on()


    def test_last_on_from(self, word: str) -> str:
            if (find_player(word)) {
            map_delete(player_cache, word)
            return query_ip_name(find_player(word)) + " (" +
            query_ip_number(find_player(word)) + ") "


    def test_start_time(self, word: str) -> int:
            if (find_player(word)) {
            map_delete(player_cache, word)
            return find_player(word)->query_start_time()


    def test_creator(self, str: str) -> int:
            str = lower_case (str)
            if (find_player(str)) {
            map_delete(player_cache, str)
            return find_player(str)->query_creator()


    def test_home_dir(self, str: str) -> str:
            if (find_player(str)) {
            map_delete(player_cache, str)
            return find_player(str)->query_home_dir()


    def test_family(self, str: str) -> str:
            if (find_player(str)) {
            map_delete(player_cache, str)
            return find_player(str)->query_family_name()


    def test_player_title(self, str: str) -> str:
            if (find_player(str)) {
            map_delete(player_cache, str)
            return find_player(str)->query_player_title()


    def test_password(self, name: str, pass: str) -> int:
            if (!load_player(name)) {
            return 0


    def get_password(self, name: str) -> str:
            if(file_name(previous_object()) != "/secure/ftp_auth")
            return "x"
            if(!load_player(name))
            return "x"
            if(find_player(name) && player_cache[name]->password == "") {
            unguarded((: restore_object,
            query_player_disk_file_name(name), 1 :))


    def query_signature(self, name: str) -> str:
            string sig
            if (find_player(name)) {
            map_delete(player_cache, name)
            sig =
            make_string(find_player(name)->query_player_alias(".signature"),
            3)
            } else {
            if (!load_player(name))
            return ""
            sig = make_string(player_cache[name]->signature, 3)


    def query_project(self, name: str, unused: int) -> str:
            if (find_player(name)) {
            map_delete(player_cache, name)
            if (find_player(name)->query_player_alias(".project"))
            return make_string(find_player(name)->query_player_alias(".project"), 5)
            else
            return ""


    def query_plan(self, name: str, unused: int) -> str:
            if (find_player(name)) {
            map_delete(player_cache, name)
            if (find_player(name)->query_player_alias(".plan"))
            return make_string(find_player(name)->query_player_alias(".plan"),
            5)
            else
            return ""


    def query_reference(self, name: str) -> str:
            if (find_player(name)) {
            map_delete(player_cache, name)
            if (find_player(name)->query_player_alias(".reference"))
            return make_string(find_player(name)->
            query_player_alias(".reference"), 20)
            else
            return ""


    def test_nationality(self, str: str) -> str:
            if (find_player(str)) {
            map_delete(player_cache, str)
            return find_player(str)->query_nationality()


    def test_nationality_region(self, str: str) -> str:
            if (find_player(str)) {
            map_delete(player_cache, str)
            return find_player(str)->query_nationality_region()


    def test_nationality_data(self, str: str) -> str:
            if (find_player(str)) {
            map_delete(player_cache, str)
            return find_player(str)->query_nationality_data()


    def test_ip_allowed(self, name: str, ip: str) -> int:
            string *ips
            if(ip == "127.0.0.1")
            return 1
            if(find_player(name)) {
            map_delete(player_cache, name)
            ips = find_player(name)->query_rhosts()
            } else if (load_player(name))
            ips = player_cache[name]->player_info["allowed_ips"]
            if(!ips || !sizeof(ips))
            return 1
            while(strlen(ip)) {
            if(ips.index(ip) if ip in ips else -1 != -1)
            return 1
            ip = implode((string *)explode(ip, ".")[0..<2], ".")



class Player_handler(MudObject):

    player_ob = '"/global/player"'

    player_cache = '([ ])'
