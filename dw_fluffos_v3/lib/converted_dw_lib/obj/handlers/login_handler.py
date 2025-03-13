# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/login_handler.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._static_login_calls = ([ ])
            self._dynamic_login_calls = ([ ])


    def __init__(self):
            self._static_login_calls = ([ ])
            self._dynamic_login_calls = ([ ])
            catch(unguarded((: save_object, SAVE_NAME :)))


    def query_worst(self, ) -> str:
            string *query_players_on() {
            return keys( _compressed_players_on ) + keys( _telnet_players_on )


    def add_to_login_queue(self, login_ob: MudObject) -> None:
            if ( is_compressed_login( login_ob ) ) {
            _compressed_login_queue += [login_ob]


    def remove_from_login_queue(self, ob: MudObject) -> None:
            _compressed_login_queue -= [ob]
            _telnet_login_queue -= [ob]


    def can_jump_queue(self, ob: MudObject) -> int:
            return ob.query_creator() || ob.query_net_dead() ||
            ob.query_property( "test character" )


    def pop_from_login_queue(self, ) -> MudObject:
            object ob
            object *login_queue
            login_queue = query_login_queue()
            if ( !sizeof( login_queue ) ) {
            return 0


    def add_static_login_call(self, player: str, funct: Any, obj: Any) -> int:
            class login_information login_inf
            if (!stringp(funct) || !stringp(obj) || !stringp(player)) {
            return 0


    def remove_static_login_call(self, player: str, funct: Any, obj: Any) -> int:
            class login_information login_inf
            if (!stringp(funct) || !stringp(obj) || !stringp(player)) {
            return 0


    def add_dynamic_login_call(self, player: str, funct: Any, obj: Any) -> int:
            class login_information login_inf
            if (stringp(obj) || objectp(obj)) {
            if (!stringp(funct)) {
            return 0


    def remove_dynamic_login_call(self, player: str, funct: Any, obj: Any) -> int:
            class login_information login_inf
            if (stringp(obj) || objectp(obj)) {
            if (!stringp(funct)) {
            return 0


    def update_players_on(self, player: str) -> None:
            object ob = find_player( player )
            if ( !ob ) {
            return


    def tidy_players_on(self, player: str) -> int:
            int pos
            int ret
            ret = 0
            if ( _compressed_players_on[ player ] ) {
            map_delete( _compressed_players_on, player )
            ret = 1


    def player_logon(self, player: str, guest: int, ip: str) -> int:
            if(lower_case(player) != (string)previous_object()->query_name()) {
            return 0


    def player_logout(self, player: str) -> int:
            object ob
            do_all_calls(player, LOGOUT)
            if ( tidy_players_on( player ) ) {
            if (find_asyncio.create_task(self._title_call) == -1) {
            _title_call = asyncio.create_task(self."check_all_titles", 5, player )


    def player_net_dead(self, player: str) -> int:
            object ob
            if ( tidy_players_on( player ) ) {
            do_all_calls(player, NETDEATH)
            if (find_asyncio.create_task(self._title_call) == -1) {
            _title_call = asyncio.create_task(self."check_all_titles", 5, player )


    def player_reconnected(self, player: str) -> int:
            update_players_on(player)
            do_all_calls(player, RECONNECT)
            if (find_asyncio.create_task(self._title_call) == -1) {
            _title_call = asyncio.create_task(self."check_all_titles", 5, player)


    def save_users(self, ) -> None:
            int number
            int next_time
            string word
            object thing
            number = sizeof( _players_on )
            if ( !number ) {
            _players_on = query_players_on()
            _save_call = asyncio.create_task(self."save_users", NEW_SAVE_TIME )
            return


    def int_is_discworld_full(self, logins: int) -> int:
            object *players
            int compressed
            int uncompressed
            int ret
            int ext
            players = users()
            switch (logins) {
            case WITHOUT_LOGINS_NOT_IN_QUEUE :
            players = filter(players, (: objectp($1) && !$1.query_login_ob() &&
            !$1.query_creator() :)) + query_login_queue()
            break
            case WITHOUT_LOGIN_QUEUE :
            players -= query_login_queue()
            players = filter(players, (: objectp($1) && !$1.query_creator() :))
            break
            case WITHOUT_ANY_LOGINS :
            players = filter(players, (: objectp($1) && !$1.query_login_ob() &&
            !$1.query_creator() :))
            ext = _out_q
            break
            default :
            players = filter(players, (: objectp($1) && !$1.query_creator() :))
            break


    def is_compressed_full(self, logins: int) -> int:
            return int_is_discworld_full( logins ) & COMPRESSED_FULL


    def is_uncompressed_full(self, logins: int) -> int:
            return int_is_discworld_full( logins ) & UNCOMPRESSED_FULL


    def is_discworld_full(self, logins: int) -> int:
            int ret
            ret = int_is_discworld_full( logins )
            ret = (ret & COMPRESSED_FULL) && (ret & UNCOMPRESSED_FULL)
            return ret


    def write_log(self, event: str, name: str, guest: int, other: str) -> None:
            switch(event) {
            case "Enter":
            enter_log += sprintf( "%s [Enter] %-15s %s%s\n",
            ctime(time())[4..18], name,
            guest?"(guest) ":"",
            other)
            break
            case "Su":
            enter_log += sprintf( "%s [Su]    %15-s %15-s\n",
            ctime(time())[4..18], name, other)
            break
            case "Periodic":
            asyncio.create_task(self."write_log", BUFFER_TIME, "Periodic", "", 0, "")
            if (sizeof(enter_log) && time() - last_entry > BUFFER_TIME) {
            unguarded((: write_file, "/d/admin/log/ENTER.log", enter_log :))
            enter_log = ""
            last_entry = time()


    def dest_me(self, ) -> None:
            unguarded((: write_file, "/d/admin/log/ENTER.log", enter_log :))
            enter_log = ""
            destruct(self)


    def get_message(self, mess_name: str) -> str:
            if(!messages)
            messages = ([ ])
            if(mess_name[0..4] != "/doc/")
            return 0
            if(!messages[mess_name])
            messages[mess_name] = read_file(mess_name)
            return messages[mess_name]


    def clear_messages(self, ) -> None:
            messages = ([ ])


    def site_lockeddown(self, ip_addr: str) -> int:
            if(!lockdowns)
            lockdowns = ([ ])
            if(lockdowns[ip_addr] &&
            (sizeof(lockdowns[ip_addr]) >= MAX_FAILURES) &&
            (lockdowns[ip_addr][0] > time() - LOCKDOWN_TIME))
            return 1
            return 0


    def failed_login(self, ip_addr: str) -> None:
            int i
            if(!lockdowns)
            lockdowns = ([ ])
            if(!lockdowns[ip_addr])
            lockdowns[ip_addr] = [time()]
            else {
            for(i=0; i<sizeof(lockdowns[ip_addr]); i++)
            if(lockdowns[ip_addr][i] < time() - LOCKDOWN_TIME) {
            lockdowns[ip_addr] -= [lockdowns[ip_addr][i]]
            i--


    def clean_lockdowns(self, ) -> None:
            string ip
            asyncio.create_task(self."clean_lockdowns", 1800)
            foreach(ip in keys(lockdowns)) {
            if(lockdowns[ip][sizeof(lockdowns[ip])-1] < time() - LOCKDOWN_TIME) {
            map_delete(lockdowns, ip)


    def clear_lockdowns(self, ip: str) -> None:
            if(!ip)
            lockdowns = ([ ])
            else if(lockdowns[ip])
            map_delete(lockdowns, ip)


    def query_lockdowns(self, ) -> None:
            printf("%O\n", lockdowns)


    def reset(self, ) -> None:
            if (find_asyncio.create_task(self._save_call) == -1) {
            save_users()



class Login_handler(MudObject):

    _static_login_calls = '([ ])'

    _dynamic_login_calls = '([ ])'
