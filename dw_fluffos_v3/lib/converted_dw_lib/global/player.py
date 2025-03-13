# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/global/player.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def __init__(self):
            living::create()
            events::create()
            psoul::create()
            line_ed::create()
            more_string::create()
            start_position::create()
            add_property("determinate", "")
            spells::create()
            time_on = time()
            start_time = time()
            seteuid("PLAYER")
            Str = 13
            Dex = 13
            Int = 13
            Con = 13
            Wis = 13
            set_max_sp(50)
            set_sp(50)
            wimpy = 20
            max_deaths = 7
            set_desc(0)
            add_ac("bing", "blunt", 15)
            add_ac("bing2", "sharp", 15)
            add_ac("bing3", "pierce", 15)
            add_property("player", 1)
            set_cols(79)
            set_rows(24)
            last_log_on = time()
            race_ob = RACE_STD
            sscanf(file_name(self), "%s#", my_file_name)
            _pinfo = new (class player_info, titles: ([ ]), save_inhibit:1)


    def dest_me(self, ) -> None:
            {
            if ((query_name() != "object") && objectp(this_player()) &&
            (this_player() != self) &&
            (file_name(this_player()) != "/obj/shut") &&
            (explode(file_name(this_player()), "#")[0] != "/secure/login") &&
            (explode(file_name(this_player()), "#")[0] != "/secure/nlogin")) {
            user_event(self, "inform",
            (string) this_player()->query_name() +
            " dests " + query_name(), "dest")
            tell_object(self, "You were destructed by " +
            capitalize((string) this_player()->query_name()) + ".\n")


    def disallow_save(self, ) -> None:
            {
            _pinfo->save_inhibit = 1


    def allow_save(self, ) -> None:
            {
            _pinfo->save_inhibit = 0


    def query_save_inhibit(self, ) -> int:
            {
            return _pinfo->save_inhibit


    def query_start_time(self, ) -> int:
            {
            return start_time


    def query_activity_counter(self, ) -> int:
            {
            return activity_counter


    def continue_start_player(self, ) -> None:
            {
            string title
            mapping news_rc
            mixed *stuff
            object book
            if (self.query_lord()) {
            creator = 1


    def check_error_count(self, ) -> None:
            string my_name
            my_name = query_name()
            DB_HANDLER->make_sql_request( "errors", "atuin", "",
            "SELECT COUNT(Id) AS idc FROM errors WHERE Directory = '/w/" +
            my_name + "' AND Status = 'OPEN'",
            (: finished_error_check, self, my_name :) )


    def start_player(self, ) -> None:
            {
            if (self.query_creator() && my_file_name != "/global/player") {
            this_player()->all_commands()
            this_player()->app_commands()
            this_player()->wiz_commands()


    def do_load_auto(self, ) -> None:
            {
            load_auto_load_alt(query_auto_load_string(), self, self,
            (: tell_object(self,
            "\n%^CYAN%^Inventory regeneration complete.%^RESET%^\n") :))
            set_auto_load_string(0)
            allow_save()


    def public_commands(self, ) -> None:
            {
            add_command("restart", self, "", (: restart_heart_beat() :))
            add_command("save", self, "", (: save() :))
            add_command("quit", self, "", (: quit_alt(-1) :))
            add_command("quit", self, "brief", (: quit_alt(0) :))
            add_command("quit", self, "verbose", (: quit_alt(1) :))
            add_command("review", self, "", (: review() :))
            add_command("wimpy", self, "", (: toggle_wimpy(0) :))
            add_command("wimpy", self, "<word'number'>",
            (: toggle_wimpy($4[0]) :))
            add_command("refresh", self, "<word'totally'>",
            (: do_refresh($4[0]) :))
            add_command("cap", self, "<word'name'>", (: do_cap($4[0]) :))


    def glance(self, str: str) -> int:
            {
            return command("glance" + (str ? " " + str : ""))


    def look_me(self, str: str) -> int:
            {
            return command(str ? "look" + str : "look")


    def review(self, ) -> int:
            {
            write("Entry  : " + query_msgin() + "\n")
            write("Exit   : " + query_msgout() + "\n")
            write("MEntry : " + query_mmsgin() + "\n")
            write("MExit  : " + query_mmsgout() + "\n")
            write("Editor : " + query_editor() + "\n")
            return 1


    def examine(self, arg: str) -> int:
            {
            return look_me(arg ? " at " + arg : "")


    def toggle_wimpy(self, str: str) -> int:
            {
            int number
            if (!str) {
            if (self.query_wimpy())
            write("You are in wimpy mode, you will run away at " +
            self.query_wimpy() +
            "% of your max hps.\n")
            else
            write("You are in brave mode.\n")
            write("Usage: wimpy <num> (caution read help wimpy)\n")
            return 1


    def extra_score(self, ) -> str:
            {
            return ""


    def save_me(self, ) -> None:
            mixed old
            #ifdef NOT_SAVEING_PLAYERS
            if (!self.query_creator()) {
            write("Not saving for players currently.\n")
            return


    def save_with_auto_load(self, al: Any) -> None:
            {
            mixed old
            #ifdef NOT_SAVEING_PLAYERS
            if (!self.query_creator()) {
            write("Not saving for players currently.\n")
            return


    def quit_alt(self, verbose: int) -> int:
            {
            object frog
            if (verbose == -1) {
            verbose = query_verbose("quit")


    def do_quit(self, ) -> int:
            {
            return quit_alt(-1)


    def quit(self, ) -> int:
            {
            if (query_auto_loading() || query_save_inhibit()) {
            tell_object(self,
            "Forced to quit whilst auto loading.  Not saving.\n")
            ::dest_me()
            return 1


    def query_title(self, ) -> str:
            {
            return implode(m_values(_pinfo->titles), ", ")


    def remove_title(self, type: str) -> None:
            {
            map_delete(_pinfo->titles, type)


    def query_deaths(self, ) -> int:
            {
            return deaths


    def adjust_deaths(self, i: int) -> None:
            {
            if (i > 0) {
            deaths += i


    def init_static_arg(self, map: Any) -> None:
            {
            return


    def init_dynamic_arg(self, mapping, object) -> None:
            return


    def second_life(self, ) -> Any:
            {
            object corpse
            string death_mess
            add_property("dead", time())
            if (!DEATH.someone_died(self)) {
            deaths++


    def remove_ghost(self, ) -> None:
            {
            if (deaths > max_deaths) {
            if (this_player() != self) {
            await self.send(this_player()->query_cap_name() +
            " tried to raise you, but you are completely dead.\n")
            await this_player().send(query_cap_name() +
            " is completely dead, you cannot raise " +
            query_objective() + ".\n")
            } else {
            tell_object(self, "You are completely dead.  You cannot " +
            "be raised.\n")
            say(query_cap_name() +
            " struggles to appear in a solid form, but fails.\n")
            return


    def net_dead(self, ) -> None:
            {
            if (!environment() || file_name(environment()) == "/room/departures") {
            return


    def idle_out(self, ) -> None:
            {
            say(cap_name + " has been idle for too long; " + query_pronoun() +
            " vanishes in a puff of boredom.\n")
            write("You idled out, sorry.\n")
            quit()


    def heart_beat(self, ) -> None:
            {
            catch {
            int idle_time
            events::print_messages()
            flush_queue()
            if (!interactive(self)) {
            idle_time = time() - last_command
            } else {
            idle_time = query_idle(self)


    def query_monitor(self, ) -> int:
            {
            return monitor


    def set_monitor(self, i: int) -> None:
            monitor = i


    def run_away(self, ) -> int:
            {
            int number
            become_flummoxed()
            number =::run_away()
            if (number)
            await self.send("Your feet run away with you!\n")
            else
            tell_object(self, "You try to run away, but no matter how "
            "you scrabble, you can't find any way out.\n")
            return number


    def query_mature(self, ) -> int:
            {
            return (MATURITY * 60 * 60 + time_on < time())


    def check_dark(self, light: int) -> int:
            {
            int i
            if (race_ob)
            if (catch(i = (int) race_ob.query_dark(light)))
            race_ob = RACE_STD
            else
            return i
            return (int) RACE_STD.query_dark(light)


    def query_level(self, ) -> int:
            {
            string tmp
            if (_pinfo->level_time < (time() - LEVEL_CACHE)) {
            if (class_ob) {
            _pinfo->level = (int) class_ob.query_level(self)
            } else {
            tmp = query_property("backup class")
            if (tmp) {
            _pinfo->level = tmp.query_level(self)
            } else
            _pinfo->level = CONFIG_DEFAULT_GUILD.query_level(self)


    def restart_heart_beat(self, ) -> int:
            {
            set_heart_beat(1)
            write("Ok, heart_beat restarted.\n")
            return 1


    def set_creator(self, i: int) -> None:
            {
            if (previous_object() != master()) {
            write("Illegal attempt to set creator!\n")
            log_file("ILLEGAL", this_player(1)->query_name() + " (" +
            file_name(this_player(1)) +
            ") Illegal attempt to set_creator " + "at " + ctime(time()) +
            " from " + file_name(previous_object()) + "\n")
            return


    def query_prevent_shadow(self, ob: MudObject) -> int:
            {
            if (function_exists("query_prevent_shadow", ob) ||
            function_exists("query_name", ob) ||
            function_exists("query_creator", ob) ||
            function_exists("query_lord", ob) ||
            function_exists("query_hidden", ob) ||
            function_exists("dest_me", ob) ||
            function_exists("query_object_type", ob) ||
            function_exists("query_lord", ob) || function_exists("save_me", ob))
            return 1
            return 0


    def query_max_deaths(self, ) -> int:
            {
            return max_deaths


    def adjust_max_deaths(self, i: int) -> int:
            {
            if (i > 0) {
            return (max_deaths += i)


    def query_object_type(self, player: MudObject) -> str:
            {
            if ("/obj/handlers/playtesters"->query_playtester(query_name())) {
            return "p"


    def do_cap(self, str: str) -> int:
            {
            if (!str)
            return notify_fail("Syntax: " + query_verb() + " <cap_name>\n")
            if (lower_case(str) != query_name())
            return
            notify_fail
            ("You must have the same letters in your capitalized name.\n")
            cap_name = str
            write("Capitalized name set to " + cap_name + ".\n")
            return 1


    def set_my_ident(self, str: str) -> None:
            {
            return


    def query_my_ident(self, ) -> str:
            {
            return 0


    def query_last_log_on(self, ) -> int:
            {
            return last_log_on


    def query_refresh_time(self, ) -> int:
            {
            return _refresh_time


    def query_no_logins(self, ) -> int:
            {
            return no_logins


    def query_creator(self, ) -> int:
            {
            return 0


    def _living(self, ) -> int:
            protected void set_invis(int level) {


    def query_player_killer(self, ) -> int:
            return _flags & PLAYER_KILLER_FLAG


    def set_player_killer(self, flag: int) -> None:
            if (flag) {
            _flags |= PLAYER_KILLER_FLAG
            } else {
            _flags &= ~PLAYER_KILLER_FLAG


    def set_role_playing(self, i: int) -> None:
            if(i)
            add_property(RPMODE, 1)
            else
            remove_property(RPMODE)


    def query_role_playing(self, ) -> int:
            return query_property(RPMODE)



class Player(MudObject):
