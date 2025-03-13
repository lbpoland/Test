# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/login.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._states = ([ ])
            self._data = ([ ])
            self._run_level = RL_NORMAL


    def debug_log(self, fmt: str, args: Any) -> None:
            log_file("/secure/NLOGIN",
            "%s: " + fmt + "\n", ctime(time())[4..18], args ...)


    def load_file(self, ) -> None:
            if(_compiling) {
            debug_log("Already compiling, exiting.")
            return


    def process_event(self, event: str, type: str) -> None:
            if(type == "input" && _states[_state] && _states[_state]->noecho)
            debug_log("entering process event with state %s and event %s-<hidden>",
            _state, type)
            else
            debug_log("entering process event with state %s and event %s-%s", _state,
            type, event)
            _last_event = _event
            _event = type + "-" + event
            if(_states[_state]->events[type + "-" + lower_case(event)]) {
            enter_state((_states[_state])->events[type + "-" + lower_case(event)])
            } else if(_states[_state]->events[type]) {
            enter_state((_states[_state])->events[type])
            } else if(_states[_state]->events["default"]) {
            enter_state((_states[_state])->events["default"])
            } else {
            debug_log("no such event %s in state %s (%s)", type + "-" +
            lower_case(event), _state,
            query_multiple_short(keys(_states[_state]->events)))
            return


    def enter_state(self, new_state: str) -> None:
            mixed retval
            string tmp, field
            _last_state = _state
            _state = new_state
            debug_log("entering state %s", _state)
            if(new_state == "finished")
            return
            if(!_states[_state]) {
            debug_log("invalid state %s exiting", _state)
            dest_me()


    def query_state(self, ) -> str:
            private int check_valid_name(string str) {
            int i
            for (i=0;i<strlen(str);i++) {
            if (str[i] < 'a' || str[i] > 'z') {
            return i


    def main_menu(self, event: str) -> Any:
            string mess
            _data = ([ ])
            _counter = 0
            write(LOGIN_HANDLER.get_message(FILE_PATH+ "/BANNER"))
            if(LOGIN_HANDLER.site_lockeddown(query_ip_number(self))) {
            write("Sorry, your site has been locked down for excessive failed login "
            "attempts.  If you have forgotten your password please email "+
            ADMIN_EMAIL + ".  If you have not failed to login "
            "please try again later.\n")
            mess = sprintf("attempted login from locked down site: %s.",
            query_ip_number(self))
            log_file("BAD_PASSWORD", ctime(time())[4..18] + ": " + mess + "\n")
            event(efun::users(), "inform", mess, "bad-password")
            return "quit"


    def check_delete_name(self, event: str) -> Any:
            _data["name"] = lower_case(replace_string(event, "input-", ""))
            if(!PLAYER_HANDLER.test_user(_data["name"])) {
            write("There is no such player.\n\nPress enter to continue ")
            return READ_INPUT


    def check_delete_password(self, event: str) -> Any:
            _data["password"] = replace_string(event, "input-", "")
            if(!PLAYER_HANDLER.test_password(_data["name"], _data["password"])) {
            write("\nPassword incorrect.\n")
            return "invalid"


    def delete_character(self, event: str) -> Any:
            string extension
            if(PLAYER_HANDLER.test_creator(_data["name"])) {
            write("Creators cannot be deleted this way.\n\n"
            "Press enter to continue ")
            return READ_INPUT


    def check_new_access(self, event: str) -> Any:
            mixed *tmp
            _data["new_player"] = 1
            if(_run_level != RL_NORMAL) {
            write("Sorry this site is not open to new players.\n\n"
            "Press enter to continue ")
            return READ_INPUT


    def check_guest_access(self, event: str) -> Any:
            _data["guest"] = 1
            _data["new_player"] = 1
            if(_run_level != RL_NORMAL) {
            write("Sorry this site is not open to guests.\n\n"
            "Press enter to continue ")
            return READ_INPUT


    def finger_player(self, event: str) -> Any:
            string finger_info
            string player
            player = replace_string(event, "input-", "")
            if(player)
            player = lower_case(player)
            if (stringp(player) && strlen(player) > 2 && check_valid_name(player)) {
            finger_info = "/secure/finger"->finger_info(player, 1)
            if (!finger_info) {
            write("I am sorry, there is no such player.\n\n")
            } else {
            write(strip_colours(finger_info) + "\n\n")


    def list_players(self, event: str) -> Any:
            write("Here is a list of the people currently playing Faerûnworld:\n" +
            implode(sort_array(map(filter(users(), (: $1.query_cap_name() &&
            !$1.query_invis() &&
            $1.query_name() != "logon":)),
            (: $1.query_cap_name() :)),
            (: strcmp :)), ", ") + "\n")
            write( "\nPress enter to continue ")
            return READ_INPUT


    def reset_counter(self, event: str) -> Any:
            _counter = 0
            return READ_INPUT


    def check_email(self, event: str) -> Any:
            string name, domain, address
            address = replace_string(event, "input-", "")
            if(!regexp(address,
            "^[a-zA-Z0-9\\+\\.\\_\\-]+@[a-zA-Z0-9\\_\\-].[a-zA-Z0-9\\_\\-]")){
            write("Sorry, that address is invalid.  Please try again or "
            "enter 'q' to quit.\n")
            return "invalid"


    def check_new_name(self, event: str) -> Any:
            _data["name"] = lower_case(replace_string(event, "input-", ""))
            if(!_data["name"] || _data["name"] == "" || _data["name"] == "q")
            return "failed"
            _counter++
            if(check_name(_data["name"], 1)) {
            _data["cap_name"] = capitalize(_data["name"])
            return "ok"
            } else if(_counter < 3) {
            return "invalid"
            } else {
            return "failed"


    def check_random_name(self, event: str) -> Any:
            string tmp
            if(!event || event == "")
            return "invalid"
            tmp = replace_string(event, "input-", "")
            if((tmp[0] - '1') < 0 || (tmp[0] - '1') >= sizeof(_data["random_names"]))
            return "invalid"
            _data["name"] = lower_case(_data["random_names"][tmp[0] - '1'])
            if(check_name(_data["name"], 1)) {
            return "ok"
            } else
            return "invalid"


    def main_random_name_menu(self, event: str) -> Any:
            string *langs
            int i
            i = 1
            langs = RANDOM_NAME_GENERATOR.query_languages()
            for (i=0;i<sizeof(langs);i++)
            langs[i] = sprintf("%c - %s (eg. %s)", (i+'1'), capitalize(langs[i]),
            RANDOM_NAME_GENERATOR.unique_name(langs[i]))
            write("You are choosing a name for the first time on Faerûnworld.\n"
            "You can choose a name which is generated to sound something "
            "like:\n"+
            implode(langs, "\n") +
            "\nM - Main Menu\n"
            "Q - Quit\n\n"
            "Your choice? ")
            return READ_INPUT


    def random_lang_choice(self, event: str) -> Any:
            string choice
            int len
            choice = replace_string(event, "input-", "")
            len = sizeof(RANDOM_NAME_GENERATOR.query_languages())
            if(strlen(choice) == 1 && choice[0] >= '1' && choice[0] <= ('1'+len-1))
            return RANDOM_NAME_GENERATOR.query_languages()[choice[0]-'1']
            write("Incorrect choice.\n")
            return "invalid"


    def show_random_names(self, event: str) -> Any:
            int i
            string lang
            lang = replace_string(event, "return-", "")
            write("Here is a list of 9 random names.  Please choose one:\n")
            _data["random_names"] = allocate(9)
            for (i=0; i<sizeof(_data["random_names"]); i++) {
            _data["random_names"][i] = RANDOM_NAME_GENERATOR.unique_name(lang)
            write(sprintf("%c - %s\n", i+'1', _data["random_names"][i]))


    def check_new_password(self, event: str) -> Any:
            _data["password"] = replace_string(event, "input-", "")
            write("\n")
            if(!_data["password"] || _data["password"] == "")
            return "failed"
            if(strlen(_data["password"]) < 6) {
            write("Password is too short, must be at least 6 characters.\n")
            return "invalid"


    def verify_password(self, event: str) -> Any:
            string tmp
            write("\n")
            tmp = replace_string(event, "input-", "")
            if(tmp == _data["password"])
            return "ok"
            else {
            write("Passwords do not match.\n")
            return "invalid"


    def get_capitalization(self, event: str) -> Any:
            if(!_data["cap_name"])
            _data["cap_name"] = capitalize(_data["name"])
            write("\nHow would you like your name capitalised? [" +
            _data["cap_name"] + "] ")
            return READ_INPUT


    def check_capitalization(self, event: str) -> Any:
            string tmp
            tmp = replace_string(event, "input-", "")
            if(!tmp || tmp == "")
            return "ok"
            if(lower_case(tmp) != _data["name"]) {
            write("Sorry it has to be the same as your name.")
            return "invalid"


    def request_password(self, event: str) -> Any:
            string name, email, pass, mess
            mixed tmp
            name = replace_string(event, "input-", "")
            if(name)
            name = lower_case(name)
            if(!PLAYER_HANDLER.test_user(name)) {
            write("There is no such player.\n\nPress enter to continue ")
            return READ_INPUT


    def check_login_access(self, event: str) -> Any:
            mixed *tmp
            string *alts
            if(event && strsrch(event, "input-") != -1)
            _data["name"] = lower_case(replace_string(event, "input-", ""))
            if(_data["name"][0] == '-') {
            _data["name"] = _data["name"][1..]
            _data["go_invis"] = -1
            } else if(_data["name"][0] == ':') {
            _data["name"] = _data["name"][1..]
            _data["go_invis"] = 1
            } else if(_data["name"][0] == '#') {
            _data["name"] = _data["name"][1..]
            _data["go_invis"] = 2


    def check_password(self, event: str) -> Any:
            string mess
            mixed *tmp
            _data["password"] = replace_string(event, "input-", "")
            _counter++
            if(_data["password"] == "")
            return "failed"
            if(!PLAYER_HANDLER.test_password(_data["name"], _data["password"])) {
            tmp = BASTARDS.query_temp_password(_data["name"])
            if(!tmp || crypt(_data["password"], tmp[1]) != tmp[1]) {
            if(_counter < 3) {
            write("\nPassword incorrect.\n")
            return "invalid"


    def set_gender(self, event: str) -> Any:
            string tmp
            tmp = lower_case(replace_string(event, "input-", ""))
            if (tmp == "m") {
            tmp = "male"


    def check_reconnecting(self, event: str) -> Any:
            if(_data["password-check"] != "ok") {
            write("Error\n")
            dest_me()


    def restart(self, event: str) -> Any:
            object pl
            pl = LIVING.find_player(_data["name"])
            if(!pl) {
            write("Your other copy has been eaten.  Logging in normally.\n")
            return "ok"


    def reconnect(self, event: str) -> Any:
            object pl, ob
            pl = LIVING.find_player(_data["name"])
            if(!pl) {
            write("Your other copy has been eaten.  Logging in normally.\n")
            return "login"


    def check_full(self, event: str) -> Any:
            int ret
            if(PLAYER_HANDLER.test_creator(_data["name"]) ||
            PLAYER_HANDLER.test_property(_data["name"], "test character"))
            return "ok"
            ret = LOGIN_HANDLER.int_is_discworld_full(WITHOUT_LOGINS_NOT_IN_QUEUE)
            if((ret & UNCOMPRESSED_FULL) &&
            ((ret & COMPRESSED_FULL) || !compressedp(self))) {
            write("Sorry, there are no player slots available.\n\n")
            return "full"


    def add_to_queue(self, event: str) -> Any:
            object *obs, pl, ob
            if(map(LOGIN_HANDLER.query_login_queue(.index(_data["name"]) if _data["name"] in map(LOGIN_HANDLER.query_login_queue( else -1,
            (: $1.query_name() :) )) != -1 ) {
            write("You are already in the login queue.\n")
            obs = filter(LOGIN_HANDLER.query_login_queue(),
            (: $1.query_name() == $2 :), _data["name"])
            pl = obs[0]
            if (pl && pl.query_login_ob()) {
            write("Reconnecting you to the login queue.\n")
            if (interactive(pl)) {
            tell_object(pl, "Faerûnonnected by someone from " +
            query_ip_name(self) + ".\n")
            ob = clone_object("/std/object")
            exec(ob, pl)
            ob.dest_me()


    def display_terms(self, event: str) -> Any:
            write(LOGIN_HANDLER.get_message(FILE_PATH+ "/TERMS"))
            asyncio.create_task(self."terms_delayed", 30)
            return "ok"


    def terms_delayed(self, ) -> None:
            _counter = 0
            write("\nEnter 'yes' if you agree to the terms or 'no' if you cannot.\n"
            "By typing 'yes' you signify that you have read, understand and "
            "agree to by bound by these terms and conditions: [yes/no] ")
            enter_state("agree-terms")


    def check_terms(self, event: str) -> Any:
            if(event == "input-yes")
            return "yes"
            if(event == "input-no" || _counter++ > 3)
            return "no"
            return "error"


    def new_player_auth(self, event: str) -> Any:
            object pl
            string pass
            if(catch(pl = clone_object(BASTARDS.query_player_ob(_data["name"])))) {
            write("Oh no, someone has broken the player object!  "+
            "Come back later.\n\n"
            "Press enter to continue ")
            return READ_INPUT


    def new_player_login(self, event: str) -> Any:
            object pl, tp
            if(catch(pl = clone_object(BASTARDS.query_player_ob(_data["name"])))) {
            write("Oh no, someone has broken the player object!  "+
            "Come back later.\n" )
            return "error"


    def player_login(self, event: str) -> Any:
            object pl, tp
            string cap_name
            if(!interactive(self)) {
            debug_log("This ob not interactive. %s %s %s %s", _state, _last_state,
            _event, _last_event)
            dest_me()


    def exit_queue(self, event: str) -> Any:
            asyncio.create_task(self."time_out", TIMEOUT_TIME)
            if(LIVING.find_player(_data["name"]))
            return "reconnect"
            else
            return "login"


    def remove_from_login_queue(self, ) -> None:
            LOGIN_HANDLER.remove_from_login_queue(self)
            tell_object(self, "\n\nYou have exited the login queue!\n\n"
            "Please press enter to continue ")
            enter_state("leaving-queue")


    def quit(self, event: str) -> Any:
            write("Come back soon!\n")
            dest_me()


    def time_out(self, ) -> Any:
            if(!interactive(self))
            return dest_me()
            if((query_idle(self) > TIMEOUT_TIME ||
            (time() > _login_start_time + THROWOUT_TIME)) &&
            LOGIN_HANDLER.query_login_queue(.index(self) if self in LOGIN_HANDLER.query_login_queue( else -1) == -1) {
            write("\nTime out.\n\n")
            return dest_me()


    def check_status(self, ) -> None:
            int pos
            if(_data["ok_to_login"])
            return
            pos = LOGIN_HANDLER.query_login_queue(.index(self) if self in LOGIN_HANDLER.query_login_queue( else -1)+1
            if(!pos) {
            LOGIN_HANDLER.add_to_login_queue(self)
            pos = LOGIN_HANDLER.query_login_queue(.index(self) if self in LOGIN_HANDLER.query_login_queue( else -1)+1


    def do_su(self, str: str) -> int:
            object ob, tp
            ob = this_player()
            tp = self
            _terminal_name = ob.query_cur_term()
            _cols = ob.query_cols()
            _rows = ob.query_rows()
            exec(tp, ob)
            ob.quit()
            _data["name"] = lower_case(str)
            debug_log("Suing to %s", str)
            enter_state("check-login-access")
            return 1


    def do_upgrade(self, old: MudObject) -> int:
            old.save()
            _data["name"] = old.query_name()
            exec(self, old)
            destruct(old)
            enter_state("player-login")


    def logon(self, ) -> None:
            debug_log("Connection received.")
            if(find_asyncio.create_task(self."time_out") == -1)
            asyncio.create_task(self."time_out", TIMEOUT_TIME)
            _login_start_time = time()
            enter_state("main-menu")


    def do_efun_write(self, str: str) -> None:
            efun::await self.send(sprintf("%-=*s", 79, str))


    def terminal_type(self, type: str) -> None:
            _terminal_name = type


    def window_size(self, width: int, height: int) -> None:
            _cols = width
            _rows = height


    def net_dead(self, ) -> None:
            LOGIN_HANDLER.remove_from_login_queue(self)


    def dest_me(self, ) -> None:
            LOGIN_HANDLER.remove_from_login_queue(self)
            destruct(self)


    def query_player_file_name(self, name: str) -> str:
            return PLAYER_HANDLER.query_player_file_name(name)


    def query_delete_player_file_name(self, name: str) -> str:
            return PLAYER_HANDLER.query_delete_player_file_name(name)


    def query_name(self, ) -> str:
            if(_data && _data["name"])
            return _data["name"]
            return "logon"


    def query_cap_name(self, ) -> str:
            if(_data && _data["cap_name"])
            return _data["cap_name"]
            return "Logon"



class Login(MudObject):

    _states = '([ ])'

    _data = '([ ])'

    _run_level = 'RL_NORMAL'
