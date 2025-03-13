# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib//merged_cmds_global.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
from .combat import combat_handler
from .utilities import CLOTHING_HANDLER
from ..driver import MudObject, Player, driver
import asyncio

    def add_player_alias(self, name: str, value: Any) -> int:
            if (file_name(previous_object()) != ALIAS_CMD &&
            file_name(previous_object()) != EDIT_ALIAS_CMD) {
            return 0


    def remove_player_alias(self, name: str) -> int:
            if ((file_name(previous_object()) != UNALIAS_CMD) &&
            name != "" &&
            !this_player(1)->query_lord()) {
            printf("%O\n", file_name(previous_object()))
            return 0


    def alias_commands(self, ) -> None:
            add_command("END_ALIAS", "<string>", (:remove_alias_thing($4[0]):))


    def remove_all_aliases(self, ) -> int:
            if (!this_player(1)->query_lord()) {
            write("You can't do that :)\n")
            return 0


    def is_alias(self, verb: str) -> int:
            return aliases[verb] != 0


    def remove_alias_thing(self, verb: str) -> int:
            in_alias_command--
            map_delete(doing_alias, verb)
            this_player()->adjust_time_left(-DEFAULT_TIME)
            return 1


    def query_auto_loading(self, ) -> int:
            return _no_calls > 0


    def save_file(self, ) -> None:
            _save_file_call_out = 0
            unguarded((: save_object, SAVE_FILE:))


    def load_file(self, ) -> None:
            if (file_size(SAVE_FILE + ".o") > 0)
            unguarded((: restore_object, SAVE_FILE:))


    def setup(self, ) -> None:
            changes = ([])
            illegal = ([])
            load_file()
            _save_file_call_out = 0


    def clone(self, word: str) -> MudObject:
            string new_file
            object thing
            if ( changes[ word ] && new_file = changes[ word ][ 0 ] )
            word = new_file
            catch( thing = clone_object( word ) )
            return thing


    def other_file(self, word: str) -> str:
            if ( changes[ word ] )
            return changes[ word ][ 0 ]
            return word


    def add_mapping(self, from: str, to: str) -> int:
            string obj_name
            if(from[<2..] == ".c")
            from = from[0..<3]
            if(to[<2..] == ".c")
            to = to[0..<3]
            if((file_size(to) < 1) && (file_size(to+".c") < 1)) {
            write("Destination file does not exist\n")
            return 0


    def remove_mapping(self, from: str) -> int:
            string obj_name
            if ( changes && changes[ from ] ) {
            map_delete( changes, from )
            save_file()
            write( "Mapping of " + from + " removed.\n" )
            if ( !this_player() ) {
            obj_name = file_name( previous_object() )


    def list_mappings(self, str: str) -> str:
            string from, retval
            retval = ""
            foreach(from in keys(changes)) {
            if (!str ||
            strsrch(from, str) != -1 ||
            strsrch(changes[from][0], str) != -1)
            retval += from + " -> " + changes[from][0] + "\n"


    def add_illegal(self, basename: str, short: str, replacement: str) -> int:
            if(!illegal)
            illegal = ([ ])
            if(illegal[basename + ":" + short])
            return 0
            if((file_size(replacement) < 1) && (file_size(replacement+".c") < 1))
            return 0
            illegal[basename + ":" + short] = replacement
            save_file()
            return 1


    def remove_illegal(self, basename: str, short: str) -> int:
            if(!illegal)
            return 0
            if(!illegal[basename+":"+short])
            return 0
            map_delete(illegal, basename+":"+short)
            save_file()
            return 1


    def illegal_thing(self, basename: str, short: str) -> str:
            if(!illegal)
            return 0
            return illegal[basename + ":" + short]


    def clean_up(self, ) -> None:
            string from
            mixed  *to
            foreach(from, to in changes)
            if ((to[1] < time() - LIFE_TIME) ||
            ((file_size(to[0]) < 1) && (file_size(to[0] + ".c") < 1)))
            map_delete(changes, from)
            save_file()


    def __init__(self):
            self.current_verb = ""
            self.SearchPath = ['DIR_LIVING_CMDS']


    def query_current_cmd(self, ) -> str:
            protected int cmdAll(string args) {
            class command verb
            mixed tmp
            verb = new(class command)
            verb->args = args
            current_cmd = args
            if( !((int)CMD_D.GetCommand(verb, SearchPath)) ) {
            return 0


    def eventForce(self, cmd: str) -> int:
            string err
            int res
            if(member_array(call_stack(0)[1],
            [ "/cmds/creator/show_help.c",
            "/d/am/broad_way/cryer_order.c",
            "/obj/handlers/new_soul.c",
            "/std/living/force.c"
            })) == -1)
            error("illegal force")
            Forced = 1
            err = catch(res = command(cmd))
            Forced = 0
            if(err) error(err)
            return res


    def GetClient(self, ) -> str:
            ==================================================
            FILE: communicate.c
            ==================================================
            #define TELL_CMD "/cmds/player/t_ell"
            #define REMOTE_CMD "/cmds/player/rem_ote"
            class language_info {
            string cur_lang
            int mangle_accent
            string default_lang


    def communicate_commands(self, ) -> None:
            add_command("converse", "", (: converse(0) :))
            add_command("converse", "<string'person'>", (: converse($4[0]) :))
            add_command("frimble", "<string>", (: do_write($4[0]) :))
            add_command("repeat", "<string'command'>", (: do_repeat($4[0]) :))


    def query_real_max_sp(self, ) -> int:
            int ret
            ret = sqrt(self.query_time_on() / -15)
            if(ret < 50)
            return 50
            if(ret > 500)
            return 500
            return ret


    def adjust_max_sp(self, number: int) -> int:
            _sp[1] += number
            if ( _sp[1] < 0 )
            _sp[1] = 0
            number = query_real_max_sp()
            if ( _sp[1] > number )
            _sp[1] = number
            return _sp[1]


    def adjust_sp(self, number: int) -> int:
            if (_sp[0] + number < 0)
            return -1
            if (number < 0)
            adjust_max_sp(1)
            _sp[0] += number
            if ( _sp[0] > _sp[1] )
            _sp[0] = _sp[1]
            return _sp[0]


    def set_sp(self, number: int) -> int:
            return adjust_sp( number - _sp[0] )


    def do_converse(self, str: str) -> None:
            if(str == "**") {
            write("Ok.\n")
            converse_ob = 0
            return


    def add_language(self, lang: str) -> None:
            int lvl
            string skill
            if (!LANGUAGE_HAND.test_language(lang))
            return
            if (LANGUAGE_HAND.query_language_spoken(lang)) {
            skill = LANGUAGE_HAND.query_language_spoken_skill(lang)
            lvl = self.query_skill(skill)
            self.add_skill_level(skill, 100 - lvl)


    def set_language(self, str: str) -> int:
            if (!LANGUAGE_HAND.test_language(str))
            return 0
            fixup_lang_class()
            cur_lang->cur_lang = str
            return 1


    def query_current_language(self, ) -> str:
            fixup_lang_class()
            return cur_lang->cur_lang


    def set_default_language(self, def: str) -> None:
            fixup_lang_class()
            cur_lang->default_lang = def


    def query_default_language(self, ) -> str:
            fixup_lang_class()
            return cur_lang->default_lang


    def set_mangle_accent(self, flag: int) -> None:
            fixup_lang_class()
            cur_lang->mangle_accent = flag


    def query_mangle_accent(self, ) -> int:
            fixup_lang_class()
            return cur_lang->mangle_accent


    def set_tell_reply_list(self, list: Any) -> int:
            if (base_name(previous_object())[0 .. strlen(TELL_CMD) - 1] != TELL_CMD &&
            base_name(previous_object())[0 .. strlen(REMOTE_CMD) - 1] != REMOTE_CMD  &&
            !previous_object()->query_lord())
            return 0
            tell_reply_list = ({time() + (60 * 15), list]
            return 1


    def query_tell_reply_list(self, ) -> Any:
            if(base_name(previous_object())[0..strlen(TELL_CMD) - 1] != TELL_CMD &&
            base_name(previous_object())[0 .. strlen(REMOTE_CMD) - 1] != REMOTE_CMD  &&
            !previous_object()->query_lord())
            return 0
            if(tell_reply_list[0] < time())
            return 0
            return tell_reply_list[1]


    def move_player_to_start(self, bong: str, new_pl: int, c_name: str, ident: str, go_invis: int) -> None:
            if(!sscanf(file_name(previous_object()), "/secure/login#%*s") &&
            !sscanf(file_name(previous_object()), "/secure/nlogin#%*s"))
            return 0
            #ifndef NEW_DRIVER
            #endif
            ::move_player_to_start(bong, new_pl, c_name, ident, go_invis)
            write(LOGIN_HANDLER.get_message("/doc/CREATORNEWS"))
            if(query_invis()) {
            await self.send("===> You are currently INVISIBLE! <===\n")


    def query_object_type(self, object) -> str:
            if ( master()->query_senior( query_name() ) )
            return "S"
            return "C"


    def receive_snoop(self, bing: str) -> None:
            await self.send("] "+bing)


    def __init__(self):
            self._event_info = new(class event_info,
            self.my_colours = ([ ])
            self.inform_types = []


    def __init__(self):
            self._event_info = new(class event_info,
            self.my_colours = ([ ])
            self.inform_types = []
            #if !efun_defined(has_mxp)
            private int has_mxp(object ob) {
            return 0


    def query_earmuffs(self, ) -> int:
            string *query_inform_types() {
            string *types
            types = ["logon", "new-player", "birthday", "council", "friend"]
            if (self.query_creator()) {
            types += ["link-death", "message", "death",
            "class", "delete", "help", "combat-debug", "skill", "quest",
            "multiplayer", "bad-password", "club", "debug", "gag",
            "alert"]
            if (master()->query_lord((string)self.query_name())) {
            types += ["force", "enter", "dest", "cheat", "xp", "calls",
            "cpu", "ftp"]


    def query_see_octarine(self, ) -> int:
            string class
            if ( self.query_creator() )
            return 1
            if(!(class = (string)self.query_class_ob())) return 0
            return (int)class.query_see_octarine()


    def octarine_message(self, str: str) -> str:
            if (query_see_octarine())
            return str
            return ""


    def colour_event(self, event_type: str, default_colour: str) -> str:
            if (my_colours[event_type]) {
            return replace(my_colours[event_type], " ", "")


    def player_connected(self, ) -> None:
            _event_info->last_term = 0
            printf("%c%c%c", IAC, DO, TELOPT_TTYPE)
            printf("%c%c%c%c%c%c", IAC, SB, TELOPT_TTYPE, TELQUAL_SEND, IAC, SE)
            printf("%c%c%c", IAC, DO, TELOPT_NAWS)


    def set_term_type(self, str: str) -> int:
            if (!str) {
            notify_fail(sprintf("%-=*s", cols,
            "Syntax: "+query_verb()+" <term_type>\n"+
            "Where term type is one of the following: "+
            implode((string *)TERM_HANDLER.query_term_types(), ", ")+
            ".\nOr set it to \"network\", and the mud will try to "
            "figure it out itself.\n"))
            return 0


    def set_term(self, name: str) -> None:
            term_name = name
            _event_info->cur_term = 0


    def set_network_terminal_type(self, name: str) -> int:
            if (term_name != "network") return 0
            if (!name) {
            _event_info->cur_term = "dumb"
            _event_info->colour_map = 0


    def reset_colour_map(self, ) -> None:
            _event_info->colour_map = 0


    def event_commands(self, ) -> None:
            add_command("rows", self, "", (: set_our_rows(0) :))
            add_command("cols", self, "", (: set_our_cols(0, 0) :))
            add_command("rows", self, "<number>", (: set_our_rows($4[0]) :))
            add_command("cols", self, "<number>", (: set_our_cols($4[0], 0) :))
            add_command("cols", self, "test <number>", (: set_our_cols($4[0], 1) :))
            add_command("term", self, "{" +
            implode((string *)TERM_HANDLER.query_term_types() +
            ["network"], "|")+"}", (: set_term_type($4[0]) :))
            add_command("term", self, "", (: set_term_type(0) :))
            add_command("inform", self, "", (: do_inform(0) :))
            add_command("inform", self, "<string>", (: do_inform($4[0]) :))
            if (self.query_creator()) {
            add_command("busy", self, "{on|off}", (: do_busy($4[0]) :))
            add_command("busy", self, "<indirect:player>",
            (: do_busy_player($1) :))


    def do_busy(self, str: str) -> int:
            if (str == "on") {
            _event_info->busy = 1
            } else {
            _event_info->busy = 0


    def do_busy_player(self, obs: MudObject) -> int:
            write("Ok, setting you as busy with " + query_multiple_short(obs) + ".\n")
            _event_info->busy = obs
            return 1


    def query_busy(self, ) -> Any:
            if (pointerp(_event_info->busy)) {
            _event_info->busy -= [0]


    def toggle_earmuffs(self, ) -> None:
            earmuffs = !earmuffs


    def set_allow_friends_earmuffs(self, ) -> None:
            earmuffs = PLAYER_ALLOW_FRIENDS_EARMUFF


    def check_earmuffs(self, type: str, person: MudObject) -> int:
            string *on
            if (!earmuffs) {
            return 0


    def set_rows(self, i: int) -> None:
            if (i < 5) {
            return


    def query_rows(self, ) -> int:
            private int set_our_rows(int val) {
            if (!val) {
            notify_fail("Rows currently set to " + rows + ".\nrows <number> to set.\n")
            return 0


    def set_cols(self, i: int) -> None:
            if (i <= 10 || i > 999)
            return
            cols = i


    def set_my_colours(self, event_type: str, colour: str) -> None:
            if(colour == "default") {
            map_delete(my_colours, event_type)
            } else if(colour == "none") {
            my_colours[event_type] = ""
            } else {
            my_colours[event_type] = colour


    def set_looked(self, thing: MudObject) -> None:
            mixed *reform_message( string message, mixed *things ) {
            int last, number
            string before, middle, after, info
            last = -1
            if ( !things ) {
            things = [})
            } else {
            last = sizeof(things) - 1


    def add_message(self, message: str, things: Any) -> None:
            int last
            mixed *stuff
            if ( !interactive( self ) ) {
            return


    def get_pretty_short(self, thing: MudObject, dark: int) -> str:
            if (dark && environment(thing) != self) {
            if (living(thing) && thing.query_race_ob() &&
            (thing.query_race_ob())->query_humanoid()) {
            return "someone"
            } else {
            return "something"


    def get_pretty_plural(self, thing: MudObject, dark: int) -> str:
            if (dark && environment(thing) != self) {
            if (living(thing)) {
            return "people"
            } else {
            return "things"


    def my_mirror_short(self, thing: MudObject, arg: str) -> str:
            if (objectp(thing)  &&  userp(thing))
            return thing.short(0, 0)
            return arg


    def my_a_short(self, thing: MudObject, arg: str, dark: int) -> str:
            string article
            if (!thing) {
            return "something"


    def my_the_short(self, thing: MudObject, arg: str, dark: int) -> str:
            string article
            if (dark && environment(thing) != self) {
            if (living(thing) && thing.query_race_ob() &&
            (thing.query_race_ob())->query_humanoid()) {
            if (environment(thing) == environment()) {
            return "someone"


    def some_more(self, word: str) -> int:
            return sizeof( filter( all_inventory( _event_info->where ),
            (: $1.query_plural() == $(word) &&
            $1.query_visible(self) :))) > 1


    def my_one_short(self, thing: MudObject, arg: str, dark: int) -> str:
            string article, its_plural
            if (dark && environment(thing) != self) {
            if (living(thing) && thing.query_race_ob() &&
            (thing.query_race_ob())->query_humanoid()) {
            if (environment(thing) == environment()) {
            return "someone"


    def my_poss_short(self, thing: MudObject, arg: str, dark: int) -> str:
            string its_plural
            string article
            string of_whom
            if (dark && environment(thing) != self) {
            if (living(thing) && thing.query_race_ob() &&
            (thing.query_race_ob())->query_humanoid()) {
            if (environment(thing) == environment()) {
            return "someone"


    def my_the_poss_short(self, thing: MudObject, arg: str, dark: int) -> str:
            string its_plural
            string article
            string of_whom
            if (dark && environment(thing) != self) {
            if (living(thing)) {
            if (environment(thing) == environment()) {
            return "someone's"


    def indent_column(self, column: str, width: int, pad: int) -> str:
            int left
            int right
            int space
            string *parts
            string part
            mixed stuff
            string ret
            ret = ""
            if ( column[ 0 .. 2 ] != "$I$" ) {
            column = "$I$0=$C$"+ column


    def fit_message(self, message: str) -> str:
            int i
            int j
            int size
            int width
            int ok
            string* columns
            string num
            mixed* stuff
            string ret
            if ( strlen( message ) < 6 ) {
            return message


    def fix_for_mxp(self, input: str) -> str:
            return replace(input, ({
            "&", "&amp;",
            "<", "&lt;", ">", "&gt;",
            "\n", mxp_next_secure(self) + "<BR>",
            "MXP&lt;", "<", "MXP&gt;", ">"])


    def show_message(self, message: str) -> None:
            string bit
            if ( sscanf( message, "$P$%s$P$%s", bit, message ) == 2 ) {
            self.more_string( fit_message( message ), bit, 1 )
            } else {
            if (has_mxp(self)) {
            efun::await  self.send(fix_for_mxp( fit_message( message ) ))
            } else {
            efun::await  self.send(fit_message( message ) )


    def evaluate_message(self, stuff: Any) -> str:
            int i
            string message, start, finish, verb_sing, verb_plur
            message = stuff[ 0 ]
            clear_event_info_had_shorts()
            for ( i = 0; i < sizeof( stuff[ 1 ] ); i++ ) {
            message = replace_string( message, "$"+ i +"$",
            calc_shorts( stuff[ 1 ][ i ] ) )
            while ( sscanf( message, "%s$V$"+ i +"=%s,%s$V$%s", start, verb_sing,
            verb_plur, finish ) == 4 ) {
            if ( ( sizeof( stuff[ 1 ][ i ] ) == 1 ) &&
            sizeof(_event_info->had_shorts) &&
            objectp( _event_info->had_shorts[ 0 ] ) ) {
            if ( _event_info->had_shorts[ 0 ]->query_property( "party object" ) ||
            _event_info->had_shorts[ 0 ]->party_object() ) {
            message = sprintf("%s%s%s", start, verb_plur, finish)
            } else {
            message = sprintf("%s%s%s", start, verb_sing, finish)


    def print_messages(self, ) -> None:
            int i
            string message
            mixed *messages
            messages = _event_info->eemessages
            _event_info->eemessages = [})
            for ( i = 0; i < sizeof( messages ); i += 2 ) {
            message = messages[ i ]
            if ( sizeof( messages[ i + 1 ] ) ) {
            message = evaluate_message( [message, messages[ i + 1 ]] )


    def convert_message(self, message: str) -> str:
            if(message)
            message = evaluate_message( reform_message( message, [}) ) )
            _event_info->where = 0
            return message


    def event_enter(self, thing: MudObject, mess: str, object) -> None:
            if ( !stringp( mess ) )
            return
            thing.sneak_task(self)
            self.perception_task(thing)
            if ( !thing.query_visible( self ) ) {
            return


    def event_exit(self, thing: MudObject, mess: str, to: MudObject) -> None:
            ::event_exit( thing, mess, to )
            if ( !stringp( mess ) )
            return
            if ( !thing.query_visible( self ) )
            return
            enter_exit_mess( mess, thing, 1 )


    def event_say(self, caller: MudObject, str: str, avoid: Any, language: str) -> None:
            if (pointerp(avoid)) {
            if (avoid.index(self) if self in avoid else -1 != -1) {
            return


    def event_see(self, caller: MudObject, words: str, thing: MudObject, avoid: Any) -> None:
            if ( !thing.query_visible( self ) )
            return
            event_say( caller, words, avoid, 0 )


    def event_write(self, caller: MudObject, str: str, language: str) -> None:
            if (language) {
            self->add_message( LANGUAGE_HAND->garble_text_say(str,
            language, self), [}) )
            } else {
            self.add_message( str, [}) )


    def do_efun_write(self, str: str, language: str) -> None:
            event_write( 0, str, language )


    def event_emote(self, thing: MudObject, mess: str) -> None:
            if ( thing == self )
            return
            self.add_message( colour_event("emote", "%^CYAN%^") + mess + "%^RESET%^", [}) )


    def add_tell_history(self, start: str, mess: str, remote: int) -> None:
            if (!pointerp(tell_history)) {
            tell_history = [})


    def event_person_tell(self, ob: MudObject, start: str, mess: str) -> None:
            int id
            string *args
            string tmp
            if ( self.query_property( "ignoring" ) ) {
            if ( member_array( (string)ob.query_name(),
            (string *)self.query_property( "ignoring" ) ) != -1 &&
            !ob.query_creator()) {
            await ob.send(self.query_name()+" is ignoring you and "
            "will not have heard what you said.\n")
            return


    def event_newbie(self, thing: MudObject, message: str) -> None:
            string tmp
            if((this_player() == self ) ||
            check_earmuffs("newbie", this_player())) {
            return


    def event_newbiehelpers(self, thing: MudObject, message: str) -> None:
            string tmp
            if((this_player() == self ) ||
            check_earmuffs("newbiehelpers", this_player()) ||
            !NEWBIEHELPERS_HANDLER.query_helper_access(self)) {
            return 0


    def event_combat(self, thing: MudObject, message: str, exclude: MudObject, verbose: int) -> None:
            if(exclude.index(self) if self in exclude else -1 != -1)
            return
            if(verbose && !self.query_verbose("combat"))
            return
            self.add_message(colour_event("combat", "%^WHITE%^") + "$C$" +
            message + "%^RESET%^", [}))
            self.print_messages()


    def event_player_echo_to(self, ob: MudObject, mess: str, me: MudObject) -> None:
            if ( master()->query_lord( (string)self.query_name() ) )
            self->add_message( "$0$ echos to you:\n", [["my_the_short:"+
            file_name( me )]] )
            self.add_message( colour_event("echo", "") + mess + "%^RESET%^",
            [}) )


    def event_player_emote_all(self, ob: MudObject, mess: str) -> None:
            if (ob == self) {
            return


    def event_player_echo(self, ob: MudObject, mess: str) -> None:
            if (ob == self) {
            return


    def receive_snoop(self, mess: str) -> None:
            await self.send("] "+mess)


    def terminal_type(self, type: str) -> None:
            if (set_network_terminal_type(type)) {
            tell_object(self, "Setting your network terminal type to \""+
            type+"\".\n")
            } else {
            if (term_name == "network") {
            if (!_event_info->last_term || _event_info->last_term != type) {
            _event_info->last_term = type
            printf("%c%c%c%c%c%c", IAC, SB, TELOPT_TTYPE, TELQUAL_SEND, IAC, SE)
            } else
            await self.send("Unknown terminal type \""+type+"\".\n")


    def window_size(self, width: int, height: int) -> None:
            if (term_name == "network") {
            if (width > 10 && width < 256) {
            set_cols(width)


    def mxp_enable(self, ) -> None:
            efun::tell_object(self,
            sprintf("%c%c%c%c%c%c", IAC, SB, TELOPT_MXP, IAC, SE, 0) +
            sprintf("%c[1z", 27) +
            replace_string(read_file("/doc/login/mxp_setup"), "\n", "") + "\n")


    def remove_player_title(self, title: str) -> None:
            private class family_information create_family_info() {
            class family_information bing
            bing = new(class family_information)
            bing->adjectives = [})
            bing->titles = ["mr", "miss", "mrs", "ms"]
            bing->clubs = [})
            return bing


    def check_family_name(self, ) -> None:
            class family_information frog
            string bing
            if (!classp(_family_name) &&
            _family_name) {
            bing = (string)_family_name
            _family_name = create_family_info()
            set_family_name(bing)


    def set_family_name(self, name: str) -> int:
            if (name && (!CLUB_HANDLER.is_family(name) ||
            !CLUB_HANDLER.is_member_of(name, query_name()))) {
            return 0


    def query_family_name(self, ) -> str:
            if (stringp(_family_name)) {
            return (string)_family_name


    def query_player_title(self, ) -> str:
            check_family_name()
            if (_family_name && classp(_family_name) &&
            _family_name->force_title) {
            if (-self.query_time_on() > _family_name->force_timeout) {
            _family_name->force_title = 0
            } else {
            return capitalize(_family_name->force_title)


    def set_player_title(self, title: str) -> int:
            string* bits
            if (!_family_name) {
            _family_name = create_family_info()


    def set_forced_title(self, title: str, timeout: int) -> int:
            _family_name->force_title = title
            _family_name->force_timeout = -self.query_time_on() + timeout
            tell_object(self, "%^CYAN%^You feel that other peoples perception "
            "of you has changed and you title is being "
            "misinterpreted.%^RESET%^\n")
            return 1


    def query_forced_title(self, ) -> str:
            return _family_name->force_title


    def add_player_title(self, title: str) -> int:
            title = lower_case(title)
            if (!_family_name) {
            _family_name = create_family_info()


    def remove_player_title(self, title: str) -> None:
            title = lower_case(title)
            if (!_family_name) {
            _family_name = create_family_info()


    def add_player_club(self, club: str) -> int:
            class family_information frog
            if (!club) {
            return 0


    def remove_player_club(self, club: str) -> None:
            if (!club) {
            return 0


    def finger_commands(self, ) -> None:
            add_command("password", self, "", (: change_password() :))
            add_command("passwd", self, "", (: change_password() :))


    def set_desc(self, str: str) -> None:
            if (!player_info) {
            player_info = ([ ])


    def query_desc(self, ) -> str:
            if (!player_info  ||  undefinedp(player_info["desc"])) {
            return ""


    def set_zone_desc(self, zone: str, desc: str) -> None:
            if (!player_info["zone desc"]) {
            player_info["zone desc"] = ([ ])


    def query_zone_desc(self, zone: str) -> str:
            if (!player_info["zone desc"]) {
            return 0


    def query_main_zone_desc(self, wearing: Any) -> str:
            object bing
            string zone
            string type
            string eq_type
            string str
            mixed types
            mapping covered
            if (!sizeof(player_info["zone desc"])) {
            return ""


    def set_password(self, pass: str) -> None:
            if (file_name(previous_object())[0..12] == "/secure/login" ||
            file_name(previous_object())[0..13] == "/secure/nlogin") {
            password = pass


    def set_rhosts(self, ips: str) -> None:
            if(file_name(previous_object())[0..18] != "/cmds/player/access" &&
            file_name(previous_object())[0..19] != "/cmds/lord/authorise")
            return
            if(!player_info)
            player_info = ([ ])
            player_info["allowed_ips"] = ips


    def query_real_name(self, ) -> str:
            if (!player_info) {
            return 0


    def set_real_name(self, str: str) -> None:
            if (!player_info) {
            player_info = ([ ])


    def query_where(self, ) -> str:
            if (!player_info) {
            return ""


    def set_where(self, str: str) -> None:
            if (!player_info) {
            player_info = ([ ])


    def query_birthday(self, ) -> str:
            if (!player_info) {
            return UNKNOWN_BIRTHDAY


    def set_birthday(self, i: str) -> None:
            if (!player_info) {
            player_info = ([])


    def query_is_birthday_today(self, ) -> int:
            string cmonth
            string dummy
            string bmonth
            int cdate
            int bdate
            if (sscanf(ctime(time()), "%s %s %d %s", dummy, cmonth, cdate, dummy)!=4) {
            return 0


    def query_email(self, ) -> str:
            if(file_name(previous_object())[0..13] != "/secure/finger" &&
            file_name(previous_object())[0..27] != "/obj/handlers/player_handler" &&
            file_name(previous_object())[0..28] != "/obj/handlers/options_handler") {
            return ""


    def query_homepage(self, ) -> str:
            if (!player_info) {
            player_info = ([ ])


    def finger_set(self, ) -> int:
            if (!player_info ||
            player_info == ([ ]) ||
            sizeof(keys(player_info)) == 1) {
            return 0


    def __init__(self):
            self._friends = ([ ])


    def is_friend(self, person: str) -> int:
            if (!_friends) {
            _friends = ([ ])


    def query_friend_tag(self, person: str) -> str:
            if(!interactive(previous_object()))
            return _friends[person]
            if(previous_object()->query_name())
            log_file("CHEAT", "%s query_friend_tag called on %s by %s\n",
            ctime(time()), self.query_name(),
            previous_object()->query_name())
            else
            log_file("CHEAT", "%s query_friend_tag called on %s by %s\n",
            ctime(time()), self.query_name(),
            file_name(previous_object()))
            return ""


    def add_friend(self, person: str, tag: str) -> None:
            if (strlen(tag) > PLAYER_MAX_FRIEND_TAG_LEN) {
            return


    def remove_friend(self, person: str) -> None:
            map_delete(_friends, person)


    def race_guild_commands(self, ) -> None:
            string command
            string *bing
            string *paths = [})
            if (!known_commands) {
            known_commands = ["skills", "rearrange", "gp", "newbie"]


    def query_gtitle(self, ) -> str:
            string tmp
            if (class_ob)
            if (catch((tmp = (string)class_ob.query_title(self))))
            tmp = "Has a broken class"
            return tmp


    def set_race_ob(self, str: str) -> None:
            string frog
            if(sscanf(str, "/%s", frog)==1)
            str = extract(str, 1)
            if (str[0..strlen("std/races")-1]!="std/races") {
            write("Illegal path to set_race_ob.\n")
            return


    def set_guild_ob(self, str: str) -> None:
            if(str) {
            if(str[0..10] != "/std/classs") {
            tell_object(self, "Attempt to set invalid class object " +
            str + "\n")
            return
            } else if(!find_object(str)) {
            await self.send("No such object "+ str +"\n")
            return


    def query_guild_ob(self, ) -> str:
            if ( !class_ob ) {
            return 0


    def set_guild_data(self, dat: Any) -> None:
            mixed *query_class_data() {
            return class_data


    def query_race(self, ) -> str:
            if(!_race)
            _race = (string)race_ob.query_name()
            return _race


    def help_command(self, str: str) -> str:
            class command cmd = new(class command, verb : str)
            string path
            mixed func
            if ((known_commands.index(str) if str in known_commands else -1 != -1 ||
            self.query_creator()) &&
            CMD_D.HandleStars(cmd)) {
            path =  CMD_D.GetPaths(cmd->verb)[0] + "/" + cmd->verb
            func = path.help_function()
            if (func) {
            return func


    def query_known_command(self, word: str) -> int:
            return ( known_commands .index( word) if  word in known_commands  else -1 != -1 )


    def add_known_command(self, str: str) -> int:
            string *paths
            if (known_commands.index(str) if str in known_commands else -1 != -1) {
            return 0


    def remove_known_command(self, str: str) -> int:
            int i
            i = known_commands.index(str) if str in known_commands else -1
            if (i == -1) {
            return 0


    def substitute_history(self, arg: str) -> str:
            string s1, s2
            if (sscanf(arg, "%s^%s", s1, s2) != 2)
            return arg
            sscanf(s2, "%s^", s2)
            if (hoffset)
            return replace(history[hoffset-1], s1, s2)
            else
            return replace(history[sizeof(history)-1], s1, s2)


    def ignore_from_history(self, str: str) -> None:
            ignore_history = str


    def add_history(self, arg: str) -> None:
            if (ignore_history) {
            if (ignore_history == arg) {
            ignore_history = 0
            return


    def __init__(self):


    def __init__(self):
            private void print_line() {
            if (line > sizeof(cfile)) {
            line = sizeof(cfile)


    def __init__(self):
            self.editor = "menu"


    def __init__(self):
            self.editor = "menu"
            protected void editor_commands()  {
            add_command("editor", "{menu|magic|ed|command}", (: set_editor($4[0]) :))


    def end_of_edit_more(self, ) -> None:
            self.set_finish_func(0)
            main_bit("")


    def editor_exit_ed(self, ) -> None:
            string str
            str = read_file(_filename)
            if ((file_size(_filename) >= 0) && !rm(_filename))
            log_file(LOG_FILE, "ed: couldn't rm %s\n", _filename)
            _lines = explode("#" + str, "\n")
            _lines[0] = _lines[0][1..]
            main_bit("")
            return


    def editor_finish_ed(self, ) -> None:
            string str
            str = read_file(_filename)
            if ((file_size(_filename) >= 0) && (_filename == TMP_FILE) &&
            !rm(_filename)) {
            log_file(LOG_FILE, "ed: couldn't rm %s\n", _filename)


    def editor_do_quit(self, str: str) -> None:
            _lines = [})
            if ((editor == "magic") && (_filename == TMP_FILE) &&
            (file_size(_filename) >= 0) && !rm(_filename))  {
            printf("magic: couldn't remove %s\n" , _filename)
            str = 0


    def set_editor(self, str: str) -> int:
            editor = str
            printf("Editor set to %s.\n", str)
            return 1


    def append_signature(self, ) -> str:
            return PLAYER_HANDLER.query_signature(self->query_name())


    def editor_check_do_quit(self, ) -> None:
            if (_in_editor)  {
            printf("Saving what you are editing.\n")
            if (editor != "ed") {
            editor_do_quit(implode(_lines, "\n"))
            } else {
            editor_finish_ed()


    def query_editor(self, ) -> str:
            return editor


    def query_in_editor(self, ) -> int:
            return _in_editor


    def logging_commands(self, ) -> None:


    def set_last_error(self, err: Any) -> None:
            last_error = err


    def __init__(self):


    def query_creator(self, ) -> int:
            return 1


    def query_object_type(self, object) -> str:
            if (master()->query_trustee(geteuid(self)))
            return "T"
            return "D"


    def event_enter(self, me: MudObject, s1: str, from: MudObject) -> None:
            if ((!s1 || s1 == "") && interactive(me)) {
            if (environment() == environment(me))
            event_inform(me, me.query_cap_name()+" invisibly enters the room",
            "enter")
            else
            event_inform(me, me.query_cap_name()+" invisibly enters your inventory",
            "enter")


    def event_exit(self, me: MudObject, s1: str, from: MudObject) -> None:
            if ((!s1 || s1 == "") && interactive(me)) {
            if (environment() == environment(me))
            event_inform(me, me.query_cap_name()+" invisibly exits the room",
            "enter")
            else
            event_inform(me, me.query_cap_name()+" invisibly exits your inventory",
            "enter")


    def __init__(self):


    def create(self, filename: str, flag: int) -> None:
            int status
            if (undefinedp(filename))  return
            rows = this_player()->query_rows()
            cols = this_player()->query_cols()
            mode_flag = flag
            seteuid(geteuid(this_player()))
            if (!filename)  filename = ""
            else filename = implode(explode(filename, " "), "")
            if (mode_flag)
            init_settings()
            status = open_file(filename)
            if (status == 0)  {
            printf("Cannot open file \"%s\".\n", filename)
            open_file("")


    def get_command(self, action: str) -> None:
            string   *bits
            string    tmp
            string    tmp2
            string   *scrap
            int       i
            int       j
            int       amt
            int       start
            int       end
            int       index
            int       diff
            int       rexp_flag
            mixed    *rexp
            function  search_func
            bits = explode(action + " ", " ")
            if ((end  = sizeof(bits) - 1) == -1)  {
            printf(":")
            input_to("get_command")
            return


    def get_new_text(self, new_in: str, cmd: str, count: int, cmdline: int) -> None:
            string new_in2
            int len
            if ((len = strlen(new_in) - 1) > -1  &&  new_in[0] == '\\'  &&  !cmdline)  {
            new_in2 = new_in[1 .. ]
            --len


    def write_permission(self, name: str) -> int:
            return write_file(name, "")


    def rm_file(self, name): str) -> int:
            string *filter_regexp(string *incoming)  {
            string *result
            int     i
            result = allocate((sizeof(incoming) + 1) / 2)
            for (i = sizeof(incoming) - 1; i >= 0; i -= 2)
            result[i / 2] = incoming[i]
            return result


    def save_history(self, ) -> int:
            string tmp
            string *junk
            int i
            int res
            tmp = read_bytes("/w/" + this_player()->query_name() + "/.magicrc")
            if (tmp)  {
            junk = explode(tmp, "\n")
            for (i = 0; i < sizeof(junk); i++)  {
            if (junk[i][0 .. 6] == "history")  {
            junk[i] = sprintf("history %s",
            implode(open_history[<10 .. ], " "))
            break


    def get_inc_path(self, fname: str, last_file: str) -> str:
            string  ret
            string  tmp
            string *bits
            int     count
            while (fname[0] == ' ')
            fname = fname[1 .. ]
            if (sscanf(fname, "<%s>", tmp) == 1)  {
            ret = "/include/"
            fname = tmp


    def expand_macros(self, ins: str, sorted_defs: str) -> str:
            int     changed
            int    *allowed = ({' ', '\t', '+', '-', ',', '(', '\"', '[']
            int     off
            string  def
            do {
            changed = 0
            foreach (def in sorted_defs)  {
            if ((off = strsrch(ins, def)) != -1)  {
            if (off == 0  ||  allowed.index(ins[off - 1]) if ins[off - 1] in allowed else -1 >= 0)  {
            ins = replace_string(ins, def, defs[def])
            changed = 1


    def strip_junk(self, stuff: str) -> str:
            stuff = replace(stuff, [" ", "", "+", "", "(", "", ")", ""])
            return replace_string(stuff, "\"\"", "")


    def defines(self, fname: str) -> None:
            string *lines
            string  line
            string  tmp
            string  tmp2
            int     off
            string *sorted_defs
            int     i
            int     j
            int     nest
            if (fname != name)  {
            tmp = read_file(fname)
            if (tmp)
            lines = regexp(explode(tmp, "\n"), "^#[ ]*(include|define)[ \t]+")
            else
            lines = [})


    def set_mark(self, s: str) -> int:
            int i
            if (!mark_name) {
            mark_name = [})
            mark_data = [})


    def next_page(self, str: str) -> None:
            int num, noargs, i, j, k, redraw
            string s1, *s3
            if (str == 0)
            str = ""
            if (sscanf(str, "%d%s", num, str) != 2)
            noargs = 1
            s1 = extract(str, 1)
            switch (str[0 .. 0]) {
            case "":
            case " ":
            topl += real_rows
            redraw = 1
            break
            case "f":
            if (noargs)
            num = 1
            topl += ROWS * num
            redraw = 1
            break
            case "q" :
            printf("OK.\n")
            return
            case "/":
            search_flag = 0
            j = topl + 4
            if (s1[0] == '!') {
            search_flag = 1
            s1 = extract(s1, 1)


    def more_file(self, str: str) -> int:
            filenames = expand_path(str)
            if (!sizeof(filenames)) {
            notify_fail("No matching files.\n")
            return 0


    def __init__(self):


    def __init__(self):
            private void string_display_file(class more_string_info info) {
            int i
            string stuff
            info->botl = info->topl + ROWS
            stuff = ""
            for ( i = info->topl; ( i < info->botl ) && ( i < info->fsize ); i++ ) {
            stuff += info->the_bit[ i ] +"\n"


    def __init__(self):
            self._commands = ([ ])
            self._fail_mess = ([ ])
            self._succ_mess = ([ ])
            self._cur_objects = ([ ])
            self._succ_indir = _succ_mess_dir = _succ_mess_indir = ({ })


    def query_parse_command_objects(self, name: str) -> List[MudObject]:
            class command_class command
            class command_data command_data
            string pattern
            object* obs
            command = _commands[name]
            obs = [})
            if (command) {
            foreach (pattern, command_data in command->patterns) {
            obs += filter(command_data->calls, (: objectp($1) :))


    def query_succ_mess_indir(self, ) -> List[MudObject]:
            return _succ_mess_indir


    def parser_commands(self, ) -> None:
            #if efun_defined(add_action)
            add_action("new_parser", "*", -2)
            #endif
            add_command("syntax", "<word'verb'>", (:syntax_messages($4[0]):))


    def add_succeeded(self, ob: Any) -> int:
            int i
            if (!pointerp(_succ_indir)) _succ_indir = [})
            if (objectp(ob)) {
            if (_succ_indir.index(ob) if ob in _succ_indir else -1 == -1) {
            _succ_indir += [ob]
            } else {
            return 1


    def add_succeeded_mess(self, dir: MudObject, incoming_mess: Any, in_dir: MudObject) -> int:
            string my_mess, other_mess
            if (!pointerp(incoming_mess)) {
            if (stringp(incoming_mess)) {
            my_mess = MY_MESS_HEADER+incoming_mess
            other_mess = OTHER_MESS_HEADER+incoming_mess
            } else {
            write("Parameter to add_succeeded_mess() must be a string or "
            "array.\n")
            return 0


    def add_failed_mess(self, dir: MudObject, mess: str, in_dir: Any) -> None:
            int i
            class fail_mess_data fail
            if (!stringp(mess)) {
            write("Parameter to add_failed_mess() must be a string.\n")
            return


    def query_failed_message_exists(self, dir: MudObject) -> int:
            string mess
            class fail_mess_data stuff
            foreach (mess, stuff in _fail_mess) {
            if (stuff->direct.index(dir) if dir in stuff->direct else -1 != -1) {
            return 1


    def remove_object(self, ob: Any, was_env: int) -> int:
            if (objectp(ob) && !_cur_objects[ob] && !was_env) {
            return 0


    def event_dest_me(self, ob: MudObject) -> None:
            remove_object_force(ob)


    def event_exit(self, ob: MudObject, mess: str, dest: MudObject) -> None:
            if (dest == self || dest == environment()) {
            return


    def me_moveing(self, from: MudObject) -> None:
            if (from) {
            remove_object(from, 1)


    def syntax_messages(self, str: str) -> int:
            string the_mess
            int i
            string tmp
            class command_data fluff
            mixed *soul_stuff
            mixed *command_stuff
            if (!str) {
            notify_fail("Syntax: syntax <verb>\n")
            return 0


    def check_living(self, ob: MudObject) -> int:
            return living(ob)


    def check_if_creator(self, ob: MudObject) -> int:
            return (int)ob.query_creator() &&
            !(ob == this_player() || ob.query_invis())


    def check_if_allowed(self, ob: MudObject) -> int:
            return ob != this_player() && reference_allowed(ob)


    def setup_failed_mess(self, obj_match: Any) -> None:
            switch (failed_match->result) {
            case OBJ_PARSER_BAD_ENVIRONMENT :
            _failed_mess[0] += "Cannot find \""+ failed_match->text +
            "\" here, access is not allowed.\n"
            break
            case OBJ_PARSER_NOT_LIVING :
            _failed_mess[0] += "The objects \""+
            query_multiple_short(failed_match->objects) +
            "\" are not living.\n"
            break
            case OBJ_PARSER_TOO_DARK :
            _failed_mess[0] += "Cannot find \""+ failed_match->text +
            "\", it is too dark.\n"
            break
            default :
            _failed_mess[0] += match_objects_failed_mess(failed_match)
            break


    def print_special_messages(self, verb: str) -> None:
            int i, j
            string words, *messes
            string type
            mixed *stuff, *tmp
            messes = keys( _succ_mess )
            for ( i = 0; i < sizeof( messes ); i++ ) {
            if ( functionp( messes[i] ) ||
            (messes[i][0..1] == MY_MESS_HEADER &&
            strlen(messes[i]) > 2)) {
            if (functionp(messes[i])) {
            words = evaluate(messes[i], 0)
            } else {
            words = messes[i][2..]


    def get_fail_messages(self, verb: str, fail_obs: MudObject) -> str:
            string whole
            string words
            string mess
            string *str
            object ob
            class fail_mess_data data
            whole = ""
            foreach (mess, data in _fail_mess) {
            if ( !stringp( mess ) ) {
            continue


    def start_player(self, pl: MudObject) -> None:
            object ob, bucket, bottle, drink, label
            seteuid(getuid())
            bucket = ARMOURY.request_item( "bucket small", 100 )
            bucket.set_short( "champagne bucket" )
            bucket->set_long( "This metal bucket was designed for a purpose, "
            "and looks like it would fit a champagne bottle perfectly.\n" )
            bucket.add_adjective( "champagne", "wine" )
            bucket.add_alias( "cooler" )
            bucket.add_read_mess( this_player()->query_cap_name(),
            "etched characters", "general" )
            bucket.move(this_player())
            bottle = clone_object( "/obj/bottle" )
            bottle.set_max_volume( 750 )
            bottle.set_name( "bottle" )
            bottle.set_short( "champagne bottle" )
            bottle.set_main_plural( "champagne bottles" )
            bottle.add_adjective( "champagne" )
            bottle.add_alias( "champagne" )
            bottle->set_long( "An expensive-looking bottle of champagne, just right "
            "to celebrate being on " + mud_name() + ".\n" )
            bottle.set_weight( 5 )
            bottle.set_max_weight( 20 )
            bottle.set_full_weight( 25 )
            bottle.set_volume( 750 )
            bottle.set_value( 400 )
            bottle.set_leak_rate( 0 )
            drink = clone_object("/obj/reagents/generic_liquid.ob")
            drink.set_name("champagne")
            drink.set_short("fine champagne")
            drink.set_long("This is a fine champagne, $amount_size$.\n")
            drink.set_medium_alias("Champagne")
            drink.add_eat_effect("/std/effects/ingested/drunk", 500)
            drink.set_amount(750)
            drink.move(bottle)
            label = clone_object("/obj/misc/label")
            label->add_read_mess( "\n    _________________  \n"
            "   |                 | \n"
            "   |                 | \n"
            "   | Vintage Century | \n"
            "   |      of the     | \n"
            "   |    Fruit Bat,   | \n"
            "   |   Year of the   | \n"
            "   |  Midnight Frog  | \n"
            "   |                 | \n"
            "   |_________________| \n",
            "cursive lettering on the bottle's label", "general" )
            bottle.add_effect("/std/effects/object/label", label)
            bottle.move( bucket )
            ob = clone_object("/obj/armour")
            ob.set_name("sash")
            ob.set_long("A large colourful sash.\n")
            ob.add_read_mess( "Welcome to " + mud_name() + ", "+
            capitalize( (string)(pl.query_name()) ) +".", 0,
            "general")
            ob.set_type( "sash" )
            ob.set_weight(3)
            ob.set_adjective(["large", "colourful"])
            ob.setup_armour(1000)
            ob.set_damage_chance(10)
            if (ob.move(pl)) {
            if (ob.move(environment(pl)))
            ob.dest_me()


    def give_junk(self, pl: MudObject) -> None:
            asyncio.create_task(self."start_player", 2, pl)


    def logged_on_times(self, num: int) -> None:
            object ob
            int bing
            this_player()->remove_property("binky level")
            switch (num) {
            case 3 :
            ob = clone_object(CABBAGE)
            if(!environment(this_player()))
            return
            ob.move(environment(this_player()))
            ob.set_owner(this_player())
            ob.init_command("follow "+this_player()->query_name())
            tell_object(this_player(),
            "%^YELLOW%^Congratulations on logging onto " + mud_name() + " for the "
            "third time.  Please accept this cabbage as a token of our "
            "appreciation.%^RESET%^\n")
            break
            case 10 :
            ob = clone_object("/obj/clothing")
            ob.set_name("badge")
            ob.set_type("badge")
            ob.set_short("fruitbat flavoured badge")
            ob.add_adjective(["fruitbat", "flavoured"])
            ob.set_weight(1)
            ob.set_damage_chance(5)
            ob.setup_clothing(10000)
            ob->set_long("The badge is brightly fruitbat flavoured with a bit of "
            "banana around the edges.  You are very proud to own it.\n")
            ob->add_read_mess("Congratulations on being a 10 time loginer to "
            "" + mud_name() + " MUD!\n", 0,
            this_player()->query_default_language())
            if (ob.move(this_player()))
            ob.move(environment(this_player()))
            tell_object(this_player(),
            "%^CYAN%^A little fruitbat flies down out of a small "
            "non-existent black hole and gives you a badge.  The "
            "fruitbat chirps excitedly at you in fruitbat and then "
            "leaps into your badge.%^RESET%^\n")
            break
            case 42 :
            ob = clone_object("/obj/misc/paper")
            ob->add_read_mess("What do you get when you multiply 6 by nine.", 0,
            this_player()->query_default_language())
            if (ob.move(this_player()))
            ob.move(environment(this_player()))
            tell_object(this_player(),
            "%^YELLOW%^This is your 42nd login.  You suddenly discover "
            "a piece of paper in your hand, something froths up in your "
            "mind and you just have to write it on the paper.\nAfterwards "
            "you stare blankly down at the paper not remembering what "
            "you just wrote.%^RESET%^\n")
            break
            case 100 :
            ob = clone_object(LEMON)
            ob.set_owner(this_player())
            tell_object(this_player(),
            "%^YELLOW%^Congratulations!  You have now logged onto "
            "" + mud_name() + " 100 times.  You are now officially addicted.  "
            "This lemon will help you on your travels.%^RESET%^\n")
            break
            case 150 :
            ob = clone_object(STICK)
            if (ob.move(this_player()))
            ob.move(environment(this_player()))
            tell_object(this_player(),
            "%^YELLOW%^This is your 150th login!  Everybody here "
            "wishes you a good time, to help you in designs we have "
            "provided this stick for you.%^RESET%^\n")
            break
            case 200 :
            ob = clone_object(CAT)
            ob.set_owner(this_player())
            tell_object(this_player(),
            "A cat slinks in from somewhere and rubs itself up "
            "against your leg.\n")
            ob.move(environment(this_player()))
            break
            case 512 :
            ob = clone_object(BUG)
            tell_object(this_player(),
            "A strange black noise starts to slowly grow louder and "
            "louder.  Suddenly in a bunch of silvery wiggling a black "
            "bug crawls into your inventory.\n")
            ob.move(this_player())
            break
            case 990 :
            ob = clone_object(BINKY_KEY)
            ob.move(this_player())
            tell_object(this_player(),
            "You hear a tinkling noise in the distance which slowly "
            "grows closer.  Something sparkly and shiny drops out of "
            "the sky into your hands.  It appears to be some sort of "
            "key.\n")
            break
            case 1000 :
            ob = clone_object(BINKY_TOY)
            ob.move(environment(this_player()))
            tell_object(this_player(),
            "You feel a chill in your bones and turn around to see "
            "a large imposing figure wearing a black coat.  He smiles "
            "down at you in a way that makes your hair stand on end "
            "and places a small horse on the ground in front of "
            "you.\nDeath says: TREAT HIM WELL AND COMB HIM OFTEN.\n")
            break
            case 1010 :
            ob = clone_object(BINKY_COMB)
            ob.move(this_player())
            tell_object(this_player(),
            "Something black and unseen taps you on the shoulder.\n"
            "Death says: I FORGOT THIS.\n"
            "Death gives you a small ivory comb.\n")
            break
            case 1020 :
            ob = clone_object(BINKY_BRUSH)
            ob.move(this_player())
            tell_object(this_player(),
            "You feel a brush in your hands, you wonder where this "
            "came from?\n")
            break


    def nickname_commands(self, ) -> None:


    def expand_nickname(self, phrase: str) -> str:
            int i
            string new_n, *words
            if ( stringp( phrase ) )
            words = explode( phrase, " " )
            else
            return phrase
            if ( !map_nicknames )
            map_nicknames = ([ ])
            for ( i = 0; i < sizeof( words ); i++ ) {
            new_n = map_nicknames[ lower_case( words[ i ] ) ]
            if ( new_n )
            words[ i ] = new_n


    def query_property(self, string) -> Any:
            varargs void add_property(string,mixed,int)
            private class player_options_control query_player_options() {
            class player_options_control options
            options = query_property(PLAYER_OPTIONS_CONTROL_PROP)
            if (!options) {
            return new(class player_options_control)


    def query_auto_follow_group(self, ) -> int:
            class player_options_control options
            options = query_property(PLAYER_OPTIONS_CONTROL_PROP)
            if (!options) {
            return 0


    def query_auto_follow_friends(self, ) -> int:
            class player_options_control options
            options = query_property(PLAYER_OPTIONS_CONTROL_PROP)
            if (!options) {
            return 0


    def query_auto_follow_everyone(self, ) -> int:
            class player_options_control options
            options = query_property(PLAYER_OPTIONS_CONTROL_PROP)
            if (!options) {
            return 0


    def query_lead_from_behind(self, ) -> int:
            class player_options_control options
            options = query_property(PLAYER_OPTIONS_CONTROL_PROP)
            if (!options) {
            return 0


    def set_auto_follow_group(self, flag: int) -> None:
            class player_options_control options
            options = query_property(PLAYER_OPTIONS_CONTROL_PROP)
            if (!options) {
            options = new(class player_options_control)


    def set_auto_follow_friends(self, flag: int) -> None:
            class player_options_control options
            options = query_property(PLAYER_OPTIONS_CONTROL_PROP)
            if (!options) {
            options = new(class player_options_control)


    def set_auto_follow_everyone(self, flag: int) -> None:
            class player_options_control options
            options = query_property(PLAYER_OPTIONS_CONTROL_PROP)
            if (!options) {
            options = new(class player_options_control)


    def set_lead_from_behind(self, flag: int) -> None:
            class player_options_control options
            options = query_property(PLAYER_OPTIONS_CONTROL_PROP)
            if (!options) {
            options = new(class player_options_control)


    def set_mxp_disable(self, flag: int) -> None:
            class player_options_control options
            options = query_player_options()
            options->mxp_disable = 1
            add_property(PLAYER_OPTIONS_CONTROL_PROP, options)


    def query_mxp_disable(self, ) -> int:
            class player_options_control options
            options = query_player_options()
            return options->mxp_disable


    def is_mxp_enabled(self, ) -> int:
            #if efun_defined(has_mxp)
            if (has_mxp(self)) {
            return !query_mxp_disable()


    def __init__(self):


    def inform_of_call(self, ob: MudObject, argv: Any) -> None:
            string str
            int i
            str = self.query_cap_name() + " calls " + argv[0] + "("
            for (i=1; i<sizeof(argv); ) {
            str += replace(sprintf("%O", argv[i]), "\n", " ")
            if (++i < sizeof(argv)) str += ","


    def expr(self, ) -> Any:
            protected mixed bit4() {
            mixed val1, val2, val3
            if (pos < sizeof(func)) {
            if (pointerp(func[pos])) {
            return func[pos++][0]


    def expr(self, ) -> Any:
            mixed val1, val2
            val1 = bit2()
            while (pos < sizeof(func)) {
            switch (func[pos]) {
            case TOK_PLUS :
            pos ++
            val2 = bit2()
            if (pointerp(val1) && !pointerp(val2)) {
            printf("Incompatible types in addition, array and something "
            "else.\n")
            val1 = 0
            } else {
            val1 = val1 + val2


    def init_expr(self, expr: str) -> None:
            pos = 0
            force_string = 0
            func = TOKENISER.tokenise(expr)


    def finish_expr(self, ) -> None:
            func = 0


    def eval(self, ) -> Any:
            mixed *tmp, val1, val2
            int i, j
            val1 = bit2()
            while (pos < sizeof(func))
            switch(func[pos]) {
            case TOK_EQUAL :
            case TOK_GREATOR :
            case TOK_LESS :
            case TOK_GREATOREQ :
            case TOK_LESSEQ :


    def get_path(self, str: str) -> str:
            string *array
            string *array1
            string temp
            int i
            if (!str) {
            if(!home_dir) {
            home_dir = "/w/" + this_player()->query_name()


    def query_current_path(self, ) -> str:
            return current_path


    def query_home_dir(self, ) -> str:
            return home_dir


    def set_current_path(self, str: str) -> None:
            current_path = str


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


    def query_pt_area(self, ob: MudObject) -> int:
            string *file
            if (strsrch (base_name (ob), "_pt") != -1) {
            return 1


    def __init__(self):
            self._pt_data = new(class playtester_data)


    def move_player_to_start(self, bong: str, new_pl: int, c_name: str, ident: str, go_invis: int) -> None:
            if(!sscanf(file_name(previous_object()), "/secure/login#%*s") &&
            !sscanf(file_name(previous_object()), "/secure/nlogin#%*s"))
            return 0
            #ifndef NEW_DRIVER
            #endif
            ::move_player_to_start(bong, new_pl, c_name, ident, go_invis)
            AddSearchPath([DIR_PLAYTESTER_CMDS])
            if (PLAYTESTER_HAND.query_senior_playtester(query_name())) {
            AddSearchPath([DIR_SENIOR_PLAYTESTER_CMDS])


    def query_object_type(self, object) -> str:
            if (PLAYTESTER_HAND.query_pt_exec(query_name())) {
            return "E"


    def query_pt_protection(self, ) -> int:
            if (_pt_data->room_protection) {
            return 2


    def enable_pt_protection(self, ) -> int:
            if (_pt_data->room_protection != 1) {
            log_file (PROTECTION_LOG, "%s: %s had room PT "
            "protection enabled by %s.\n", ctime(time()), this_player()->query_name(),
            base_name (environment (this_player())))
            tell_object (this_player(), "%^BOLD%^You have had your playtester "
            "protection enabled by an external source.  It will last until switched "
            "off by another external source.\n%^RESET%^")
            _pt_data->room_protection = 1
            return 1


    def disable_pt_protection(self, ) -> int:
            if (_pt_data->room_protection == 1) {
            log_file (PROTECTION_LOG, "%s: %s had room PT "
            "protection disabled by %s.\n", ctime(time()), this_player()->query_name(),
            base_name (environment (this_player())))
            tell_object (this_player(), "%^BOLD%^The playtester protection enabled "
            "by an external source has been switched off.\n%^RESET%^")
            _pt_data->room_protection = 0
            return 1


    def enable_personal_pt_protection(self, ) -> int:
            if (query_pt_protection()) {
            return 0


    def disable_personal_pt_protection(self, ) -> int:
            if (query_pt_protection() != 1) {
            return 0


    def pt_set_hp(self, hp: int) -> None:
            _pt_data->hp = hp


    def pt_query_hp(self, ) -> int:
            return _pt_data->hp


    def pt_make_corpse(self, ) -> MudObject:
            object corpse
            corpse = clone_object( "/obj/corpse" )
            corpse.set_owner( 0, self )
            corpse.set_ownership( query_name() )
            corpse.set_race_name( query_race() )
            if ( !query_race_ob() ) {
            corpse.set_race_ob( "/std/races/unknown" )
            } else {
            corpse.set_race_ob( query_race_ob() )


    def pt_do_death(self, ) -> MudObject:
            object corpse, flowers
            DEATH.death_informer( self, 0, _pt_data->log_file, 1 )
            tell_object( self,
            "The Death of Playtesters sneaks up behind you and taps "
            "you on the shoulder.\n"
            "%^CYAN%^The Death of Playtesters says: MY, WE'VE BEEN A BIT "
            "CARELESS, HAVEN'T WE?%^RESET%^\n"
            "The Death of Playtesters coughs.\n"
            "%^CYAN%^The Death of Playtesters says: Sorry about the Voice.  "
            "We have to do that, you know.  Well, you should really be dead "
            "now, but the Playtesters' Union renegotiated the whole death deal "
            "with the powers that be.%^RESET%^\n" )
            call_out ("pt_set_hp", 0, query_max_hp())
            corpse = pt_make_corpse()
            corpse.move( environment( ) )
            flowers = clone_object( "/std/object" )
            flowers.set_name( "flowers" )
            flowers.set_short( "bunch of flowers" )
            flowers.add_alias( "bunch" )
            flowers.add_adjective( ["bunch", "of"] )
            flowers.set_main_plural( "bunches of flowers" )
            flowers.add_plural( ["bunches", "bunches of flowers"] )
            flowers.set_long( "This is a small bunch of nice flowers.\n" )
            flowers.set_weight( 5 + random( 10 ) )
            flowers.set_value( 0 )
            flowers.set_read_mess( "Rest In Peas", "common" )
            flowers.move( corpse )
            return corpse


    def set_pt_log_file(self, str: str) -> None:
            _pt_data->log_file = str


    def query_pt_log_file(self, ) -> str:
            return _pt_data->log_file


    def enable_death_log(self, ) -> None:
            _pt_data->log_death = 1


    def disable_death_log(self, ) -> None:
            _pt_data->log_death = 0


    def query_log_death(self, ) -> int:
            return _pt_data->log_death


    def enable_damage_log(self, ) -> None:
            _pt_data->log_damage = 1


    def disable_damage_log(self, ) -> None:
            _pt_data->log_damage = 0


    def query_log_damage(self, ) -> int:
            return _pt_data->log_damage


    def do_death(self, thing: MudObject) -> MudObject:
            if( query_pt_protection() || query_in_pt_arena())
            return pt_do_death()
            else
            return ::do_death( thing )


    def query_hp(self, ) -> int:
            if( query_pt_protection() )
            return pt_query_hp()
            else
            return ::query_hp()


    def extra_score(self, ) -> str:
            return ::extra_score() +
            "Your playtester protection is "+
            ( query_pt_protection() ? "on" : "off" ) +".\n"


    def query_in_pt_arena(self, ) -> int:
            if (!environment(self)) {
            return 0


    def advancement_restriction(self, ) -> int:
            if (query_pt_protection()) {
            return 1


    def event_move_object(self, from: Any, to: Any) -> None:
            ::event_move_object (from, to)
            if (query_pt_protection()) {
            if (query_pt_area(from) && !query_pt_area (to)) {
            _pt_data->protection_counter = MAX_COUNTER
            if (_pt_data->turn_off) {
            remove_asyncio.create_task(self._pt_data->turn_off)


    def query_player_killer(self, ) -> int:
            if (query_in_pt_arena()) {
            return 1


    def query_contractable(self, ) -> int:
            return ::query_player_killer()


    def __init__(self):
            self.time_left = ROUND_TIME
            self.tl_updated = time()
            self.last_command = time()
            self.queued_commands = []


    def no_time_left(self, ) -> None:
            time_left = -ROUND_TIME


    def soul_commands(self, ) -> None:
            #if efun_defined(add_action)
            add_action("lower_check","*", -10000)
            add_action((:drunk_check:),"*", 10000)
            #endif
            alias_commands()
            nickname_commands()
            history_commands()


    def query_queued_commands(self, ) -> int:
            return sizeof(queued_commands)


    def soul_com_force(self, str: str) -> int:
            if (file_name(previous_object()) != SOUL_OBJECT)
            return 0
            command(str)
            return 1


    def do_soul(self, str: str, bing: Any) -> None:
            say(str, bing)


    def query_time_left(self, ) -> int:
            time_left += ((time() - tl_updated) / 2) * ROUND_TIME
            if(time_left > ROUND_TIME)
            time_left = ROUND_TIME
            tl_updated = time()
            return time_left


    def adjust_time_left(self, i: int) -> int:
            return time_left += i


    def set_interupt_command(self, func: Any, ob: Any, arg: Any) -> None:
            if (!functionp(func)) {
            interrupt = [func, ob, arg]
            if ( !stringp( func ) )
            interrupt = 0
            } else {
            interrupt = func


    def set_interrupt_command(self, func: Any) -> None:
            set_interupt_command(func, 0, 0)


    def remove_queue(self, ) -> None:
            queued_commands = [})
            if ( interrupt && ( time_left < 0 ) ) {
            call_interrupt(-time_left, self)


    def interupt_command(self, interupter: MudObject) -> None:
            if (interupter) {
            call_interrupt(-time_left, interupter)


    def command_override(self, func: Any) -> None:
            if(!functionp(func))
            error("command_override needs a function!")
            cmd = func


    def lower_check(self, str: str) -> int:
            query_time_left()
            return (str == "stop")


    def query_wetness(self, ) -> int:
            {
            return 0


    def add_wetness(self, arg: int) -> None:
            {


    def dry_out(self, ) -> None:
            {


    def set_personal_temp(self, i: int) -> None:
            {
            temperature = i


    def adjust_personal_temp(self, i: int) -> None:
            {
            temperature += i


    def query_personal_temp(self, ) -> int:
            {
            return temperature


    def query_temp_str(self, ) -> str:
            {
            if (!temperature_str || temperature_str == "") {
            return "quite comfortable"


    def calc_personal_temp(self, ) -> int:
            {
            mixed tmp
            object where,
            *clothes
            string item,
            zone,
            type,
            *types,
            *zones
            int adjustment,
            room_temp,
            correction,
            *enums
            if (self.query_property("dead")) {
            temperature = 0
            return 0


    def weather_extra_look(self, ) -> str:
            {
            if (stringp(temperature_str) && strlen(temperature_str)) {
            return capitalize((string) self.query_pronoun()) + " looks " +
            temperature_str + ".\n"


    def setup(self, ) -> None:
            if ( file_name( self ) != "/global/shut" ) {
            write("This object can't be cloned.\n")
            dest_me()
            return


    def ashout(self, words: str) -> None:
            int i
            object *people
            people = users()
            for ( i = 0; i < sizeof( people ); i++ )
            tell_object( people[ i ], "Offler the Crocodile God shouts: "+
            words +"\n" )


    def heart_beat(self, ) -> None:
            int time_to_crash
            if (!time_of_crash) return
            time_to_crash = time_of_crash - time()
            if (time_to_crash < 1) {
            asyncio.create_task(self."end_it_all",0)
            set_heart_beat(0)
            return


    def shut(self, minutes: int) -> None:
            object *players
            int i
            string fname
            if (!intp(minutes)) {
            write("Bad argument\n")
            return


    def long(self, str: str, dark: int) -> str:
            ::long()
            if (time_of_crash && this_player()->query_wizard())
            return ::long(str,dark)+
            "Game reboot will be in " + ( time_of_crash - time() ) +
            " seconds.\n"
            return ::long(str,dark)


    def end_it_all(self, ) -> None:
            int i
            object *obs
            ishout("Shutdown now!")
            obs = users()
            for (i=0;i<sizeof(obs);i++)
            asyncio.create_task(self."force_quit", i, obs[i])
            asyncio.create_task(self."blue", 10)


    def force_quit(self, ob: MudObject) -> None:
            if (!objectp(ob))
            return
            if (!ob.query_property("quiting frog"))
            ob.quit_alt()


    def blue(self, ) -> None:
            if (sizeof(users()) > 0 &&
            time() - time_of_crash < 120)
            asyncio.create_task(self."blue", 10)
            else
            shutdown(0)


    def query_time_to_crash(self, ) -> int:
            if ( !time_of_crash ) {
            asyncio.create_task(self. "dest_me", 1 )
            return 9999


    def __init__(self):
            self._spell_effects = []


    def queue_commands(self, {: Any) -> int:
            int add_spell_effect(int no_rnds, string type, string name, object callee,
            string func, mixed params) {
            int i,j
            if (strsrch(file_name(self),"global")==-1)
            tell_object(find_living("olorin"),
            sprintf("add_spell_effect in %s\n",
            file_name(self)))
            if ((i=_spell_effects.index(type) if type in _spell_effects else -1) != -1)
            if ((j=_spell_effects[i+1].index(name) if name in _spell_effects[i+1] else -1) == -1)
            _spell_effects[i+1] += [name, [no_rnds, callee, func, params]]
            else
            _spell_effects[i+1][j+1] = [no_rnds, callee, func, params]
            else
            _spell_effects += [type, [name, [no_rnds, callee, func, params]]]


    def remove_spell_effect(self, name: str) -> int:
            int i, j
            if (strsrch(file_name(self),"global")==-1)
            tell_object(find_living("olorin"),
            sprintf("remove_spell_effect in %s\n",
            file_name(self)))
            for (i=0;i<sizeof(_spell_effects);i+=2)
            if ((j=_spell_effects[i+1].index(name) if name in _spell_effects[i+1] else -1) != -1) {
            _spell_effects[i+1] = delete(_spell_effects[i+1], j, 2)
            if (!sizeof(_spell_effects[i+1])) {
            _spell_effects = delete(_spell_effects, i, 2)
            i -= 2


    def query_spell_effect(self, name: str) -> Any:
            int i
            if (strsrch(file_name(self),"global")==-1)
            tell_object(find_living("olorin"),
            sprintf("query_spell_effect in %s\n",
            file_name(self)))
            if ((i=_spell_effects.index(name) if name in _spell_effects else -1) == -1)
            return 0
            if (sizeof(_spell_effects[i+1]))
            return _spell_effects[i..i]+_spell_effects[0..1]
            return 0


    def do_spell_effects(self, attacker: MudObject) -> int:
            int i, j
            self.remove_property("casting")
            for (i=0;i<sizeof(_spell_effects);i+=2)
            for (j=0;j<sizeof(_spell_effects[i+1]);j+=2) {
            asyncio.create_task(self."do_call_out_effect", 1, [_spell_effects[i+1][j+1], attacker])
            _spell_effects[i+1][j+1][SP_NO_RNDS]--
            if ( !_spell_effects[i+1][j+1][SP_NO_RNDS] || !_spell_effects[i+1][j+1][SP_OBJECT]) {
            _spell_effects[i+1] = delete(_spell_effects[i+1], j, 2)
            j -= 2
            if (!sizeof(_spell_effects[i+1])) {
            _spell_effects = delete(_spell_effects, i, 2)
            i -= 2
            break


    def do_call_out_effect(self, params: Any) -> None:
            if (params[0][SP_OBJECT])
            call_other(params[0][SP_OBJECT],
            params[0][SP_FUNC],
            params[1],
            params[0][SP_PARAM],
            params[0][SP_NO_RNDS])


    def __init__(self):
            self.starts = []


    def __init__(self):
            self.starts = []
            int *query_saved_co_ords() { return saved_co_ords; }
            protected void set_last_pos(string pos) {
            if(pos[0..4] != "/room")
            last_pos = pos


    def query_last_pos(self, ) -> str:
            return last_pos


    def query_start_pos(self, ) -> str:
            string start_pos
            if ( !sizeof( starts ) ) {
            start_pos = query_nationality_start_location()
            } else {
            start_pos = starts[ 0 ]


    def add_start(self, start_file: str, start_desc: str) -> None:
            if ( !starts ) {
            starts = [})


    def remove_start(self, start_file: str) -> None:
            int i
            if ( !starts ) {
            return


    def set_start_location(self, start_file: str) -> None:
            int i
            if ( !starts) {
            return


    def inform_reconnect_game(self, ) -> None:
            user_event( "inform",
            query_extra_login_stuff(query_cap_name() +
            " reconnects"), "link-death", self )


    def check_last_pos(self, ) -> None:
            last_pos = find_start_pos(self, environment())
            saved_co_ords = find_start_coord(self, environment())


    def telnet_suboption(self, str: str) -> None:
            switch (str[0]) {
            case TELOPT_TTYPE :
            if (str[1] != TELQUAL_IS)
            return
            check_terminal_type(str[2..1000])
            break


    def player_connected(self, ) -> None:
            printf("%c%c%c", IAC, DO, TELOPT_TTYPE)
            printf("%c%c%c%c%c%c", IAC, SB, TELOPT_TTYPE, TELQUAL_SEND, IAC, SE)


    def check_terminal_type(self, type: str) -> None:
            if (last_term == type) {
            if (!got_terminal)
            self.set_network_terminal_type(0)
            return


    def wiz_commands(self, ) -> None:
            string channel
            foreach(channel in channel_list()) {
            add_command(channel, "<string'mess'>", (: channel_cmd($4[0]) :))
            add_command(channel+"@", "<string'mess'>", (: channel_cmd("@"+$4[0]) :))
            add_command(channel+"?", "", (: channel_cmd("?") :))
            if(!INTERMUD_MAP[channel]) {
            add_command(channel+"!", "", (: channel_cmd("!") :))
            add_command("h"+channel, "", (: channel_hist() :))


    def __init__(self):
            self.allowed = []


    def is_friend(self, str: str) -> int:
            return ::is_friend(str) ||
            allowed.index(str) if str in allowed else -1 != -1


    def query_friend_tag(self, str: str) -> str:
            string womble
            if(!userp(previous_object())) {
            womble = ::query_friend_tag(str)
            if (!womble) {
            if (allowed.index(str) if str in allowed else -1 != -1) {
            return "allowed to reference"


    def query_visible(self, thing: MudObject) -> int:
            string word
            if (thing == self) {
            return 1


    def query_in_editor(self, ) -> Any:
            return _in_wiz_editor || ::query_in_editor()


    def set_in_editor(self, what: Any) -> None:
            _in_wiz_editor = what


    def query_path(self, ) -> str:
            return query_current_path()


    def query_ed_setup(self, ) -> int:
            return query_property("ed_setup")


    def set_ed_setup(self, i: int) -> None:
            add_property("ed_setup", i)


    def review(self, ) -> int:
            playtester::review()
            wiz_info_comm::review()
            return 1


    def query_last_location(self, ) -> Any:
            protected string process_input(string inp){
            int start
            start = strsrch(inp, '@')
            if(start > 0){
            int space = strsrch(inp, ' ')
            if(!(space > 0 && ((space == start+1) || space < start))){
            inp = inp[0..start] + " " + inp[start+1..]


    def add_command(self, name: str, ob: MudObject, format: str, func: Any) -> int:
            protected void wiz_commands() {
            add_command("gauge", self, "<string>", (: do_gauge($4[0]) :))
            if(clonep())
            asyncio.create_task(self."driver_version", 20)


    def driver_version(self, ) -> int:
            string old = self.query_property("driver_version")
            if(!old) {
            return self.add_property("driver_version", __VERSION__)


    def review(self, ) -> int:
            PEOPLER.review()
            return 1


    def wiz_commands(self, ) -> None:
            add_command("block", "", (:do_block(0):))
            add_command("block", "<word'name'>", (:do_block($4[0]):))
            add_command("unblock", "<word'name'>", (:do_unblock($4[0]):))


    def do_block(self, str: str) -> int:
            if (!str) {
            if (!sizeof(imud_ignored)) {
            write("Not blocking anyone.\n")
            return 1


    def do_unblock(self, str: str) -> int:
            int idx
            if (!str)
            return notify_fail("Syntax: unblock <name>|all\n")
            if (!pointerp(imud_ignored) || !sizeof(imud_ignored))
            return notify_fail("You are not blocking anyone.\n")
            if (str == "all") {
            imud_ignored = 0
            write("Okay, unblocked everyone.\n")
            return 1


    def check_not_ignored(self, who: str) -> int:
            if (!pointerp(imud_ignored))
            return 1
            return imud_ignored.index(lower_case(who)) if lower_case(who) in imud_ignored else -1 == -1


    def __init__(self):
            self.obvar = ([ ])


    def affirmative(self, s: str) -> int:
            {
            s = lower_case(s)
            return (s == "y" || s == "yes" || s == "ok" || s == "please")


    def handle_error(self, erm: str, desc: str) -> None:
            if (erm) {
            write(desc + " failed : " + erm)


    def set_obvar(self, key: str, value: MudObject) -> None:
            obvar[key] = value


    def del_obvar(self, key: str) -> None:
            map_delete(obvar, key)


    def get_obvar(self, key: str) -> MudObject:
            return obvar[key]


    def desc_object(self, o: Any) -> str:
            log_file("WIZ_PRESENT", sprintf("desc_object() called by %O.\n",
            previous_object()))
            return ""


    def desc_f_object(self, o: Any) -> str:
            log_file("WIZ_PRESENT", sprintf("desc_f_object() called by %O.\n",
            previous_object()))
            return ""


    def desc_object(self, o: Any) -> str:
            string str
            if (!o) return "** Null-space **"
            if (!catch(str = (string)o.short()) && str) return str
            if (!catch(str = (string)o.query_name()) && str) return str
            return file_name(o)


    def desc_f_object(self, o: MudObject) -> str:
            string str, tmp
            str = desc_object(o)
            if (o && str != file_name(o)) {
            if (tmp)
            str += " (" + tmp + ")"
            else
            str += " (" + file_name(o) + ")"


    def __init__(self):


    def initialize_methods(self, ) -> None:
            SERVER.add_method("c",  file_name(self), "compile_c")


    def compile_c(self, name: str, clone: int) -> MudObject:
            if (!clone) {
            name.go_ahead_make_my_womble()
            return efun::find_object(name)
            } else {
            return efun::clone_object(name)


    def create(self, ) -> None:
            {
            seteuid("Root")
            initialize_methods()
            o_funcs = O_FUN
            r_funcs = O_FUN + R_FUN
            arm_funcs = ARM_FUN + O_FUN
            clo_funcs = CLO_FUN + O_FUN
            sca_funcs = SCA_FUN + O_FUN
            wep_funcs = WEP_FUN + O_FUN
            mon_funcs = MON_FUN + O_FUN
            cont_funcs = CONT_FUN + O_FUN
            food_funcs = FOOD_FUN + CONT_FUN + O_FUN
            clotrans_funcs = O_FUN + CLO_FUN + CLOTRANS_FUN


    def query_return_ob(self, ) -> MudObject:
            {
            return return_ob


    def set_return_ob(self, ob: MudObject) -> None:
            {
            return_ob = ob


    def initialize_methods(self, ) -> None:
            {
            SERVER.add_method( "r", file_name( self ), "compile_r",
            CLONE|LOAD )
            SERVER.add_method( "ro", file_name( self ), "compile_r",
            CLONE|LOAD )
            SERVER.add_method( "ob", file_name( self ), "compile_ob" )
            SERVER.add_method( "arm", file_name( self ), "compile_arm" )
            SERVER.add_method( "clo", file_name( self ), "compile_clo" )
            SERVER.add_method( "trans", file_name( self ), "compile_clotrans" )
            SERVER.add_method( "sca", file_name( self ), "compile_sca" )
            SERVER.add_method( "wep", file_name( self ), "compile_wep" )
            SERVER.add_method( "mon", file_name( self ), "compile_mon" )
            SERVER.add_method( "food", file_name( self ), "compile_food" )
            SERVER.add_method( "cont", file_name( self ), "compile_cont" )
            SERVER.add_method( "imp", file_name( self ), "compile_imp" )


    def do_clone(self, dest: MudObject, str: str) -> None:
            {
            object  ob
            ob = clone_object( str )
            if( ob )
            ob.move( dest )


    def __init__(self):
            self.data = read_file( file )


    def strip_string(self, str: str) -> str:
            {
            int     i, j
            j = strlen( str ) - 1
            for( ; WHITESPACE( str[ i ] ) && i < j; i++ )
            for( ; WHITESPACE( str[ j ] ) && j > i; j-- )
            return str[ i..j ]


    def str_to_var(self, str: str) -> Any:
            {
            int     i
            str = strip_string( str )
            switch( str[ 0 ] )
            {
            case '{':
            {
            str = str[ 1..strlen( str ) - 2 ]
            return map_array( explode( str, "," ), "str_to_var",
            self )


    def compile_r(self, name: str, clone: int) -> MudObject:
            object r
            r = prop_to_fun( name, r_funcs, "\"/obj/virtual_room.c\"",
            "virtual_room.h", 1 )
            r.reset()
            return r


    def compile_ob(self, name: str, clone: int) -> MudObject:
            return prop_to_fun( name, o_funcs, "\"/std/object.c\"",
            "virtual.h", clone )


    def compile_arm(self, name: str, clone: int) -> MudObject:
            if (name[0 .. 19] == "/obj/armours/shield/")
            return prop_to_fun(name, arm_funcs, "\"/obj/shield.c\"",
            "virtual.h", clone )
            return prop_to_fun( name, arm_funcs, "\"/obj/armour.c\"",
            "virtual.h", clone )


    def compile_clo(self, name: str, clone: int) -> MudObject:
            return prop_to_fun( name, clo_funcs, "\"/obj/clothing.c\"",
            "virtual.h", clone )


    def compile_sca(self, name: str, clone: int) -> MudObject:
            return prop_to_fun( name, sca_funcs, "\"/obj/scabbard.c\"",
            "virtual.h", clone )


    def compile_wep(self, name: str, clone: int) -> MudObject:
            return prop_to_fun( name, wep_funcs, "\"/obj/weapon.c\"",
            "virtual.h", clone )


    def compile_mon(self, name: str, clone: int) -> MudObject:
            return prop_to_fun( name, mon_funcs, "\"/obj/monster.c\"",
            "virtual.h", clone )


    def compile_food(self, name: str, clone: int) -> MudObject:
            return prop_to_fun( name, food_funcs, "\"/obj/food.c\"",
            "virtual.h", clone )


    def compile_cont(self, name: str, clone: int) -> MudObject:
            return prop_to_fun( name, cont_funcs, "\"/obj/cont_medium.c\"",
            "virtual.h", clone )


    def compile_clotrans(self, name: str, clone: int) -> MudObject:
            return prop_to_fun( name, clotrans_funcs, "\"/obj/clothing_transport.c\"",
            "virtual.h", clone )


    def compile_imp(self, name: str, clone: int) -> MudObject:
            return prop_to_fun( name, o_funcs, "\"/obj/implement.c\"",
            "virtual.h", clone )


    def set_debug_status(self, d_stat: int) -> int:
            debug_file=d_stat
            return debug_file


    def __init__(self):


    def initialize_methods(self, ) -> None:
            SERVER.add_method("s",  file_name(self), "compile_soul", 1)
            SERVER.add_method("r_n",  file_name(self), "compile_random_name", 1)


    def compile_soul(self, name: str, int) -> MudObject:
            object ob
            if (name[0] != '/')
            name = "/"+name
            if (name[0..strlen(SOUL_DIR)-1] != SOUL_DIR) {
            return 0


    def compile_random_name(self, name: str, clone: int) -> MudObject:
            object ob
            if (name[0] != '/')
            name = "/"+name
            if (name[0..strlen(RANDOM_NAME_DATA_DIR)-1] != RANDOM_NAME_DATA_DIR) {
            return 0


    def clone_object(self, name: str) -> MudObject:
            if(name[0..2] == "/d/" || name[0..1] == "d/")
            return (object)HANDLER.clone_virtual_object(name)
            return efun::clone_object(name)


    def destruct(self, name: Any) -> None:
            object obj
            if(stringp(name)) {
            obj = find_object(name)
            if(obj.query_property("file_name"))
            HANDLER.destruct_virtual_object(obj)
            destruct(obj)
            } else if(objectp(name)) {
            if(name.query_property("file_name"))
            HANDLER.destruct_virtual_object(name)
            destruct(name)


    def file_name(self, obj: MudObject) -> str:
            string name, number, file
            name = efun::file_name(obj)
            if(sscanf(name, "%s#%s", name, number) == 2) {
            if(file = (string)obj.query_property("file_name")) {
            return file + "#" + number
            } else {
            return name + "#" + number


    def find_object(self, str: str) -> MudObject:
            object obj
            if(obj = efun::find_object(str))
            return obj
            return (object)HANDLER.find_virtual_object(str)


    def find_virtual_object(self, name: str) -> MudObject:
            string trash
            if(sscanf(name, "%s#%s", name, trash) == 2)
            name = trash
            if(cloned_objects[name])
            return (object)cloned_objects[name]
            return (object)0


    def error(self, str: str) -> int:
            write(str+"\n")
            return 1


    def str_to_int(self, str: str) -> int:
            int i, j, k
            for(i=strlen(str)-1,j=1;i>-1;k+=(str[i--]-48)*j,j*=10)
            return k


    def use_efun_clone(self, file: str) -> MudObject:
            log_file("NON_VIRTUAL", file +"\n")
            return efun::clone_object(file)


    def clone_virtual_object(self, file: str) -> MudObject:
            int i, j, k, l, m, len
            string data, *line, file_to_inherit, start, comment, rest
            object obj
            mixed *args
            if(file_size(file) > 5000)
            return use_efun_clone(file)
            data = read_file(file)
            line = explode(file, "/")
            file_to_inherit = "/" + implode(line[0..sizeof(line)-2], "/") + "/"
            line = [(string)0]
            while(sscanf(data, "%s#include \"%s\"%s", start, comment, rest) == 3) {
            if(!(line[0] = read_file(file_to_inherit + comment)))
            line[0] = read_file("/include/" + comment)
            if(line[0])
            data = start + line[0] + rest
            else {
            error("Include file not found.")
            return (object)0


    def tell_object(self, ob: MudObject, str: str) -> None:
            if (objectp(ob))
            ob.event_write(previous_object(), str)


    def find_living(self, str: str) -> MudObject:
            string nick
            object ob
            if (this_player() && (nick = (string)this_player()->expand_nickname(str)))
            str = nick
            if ((ob = efun::find_living(str)))
            if ((int)ob.query_invis() == 2) {
            if (member_array(this_player()->query_name(),
            (object *)ob.query_allowed()) == -1)
            return 0


    def find_player(self, str: str) -> MudObject:
            object ob
            if ((ob = efun::find_player(str)))
            if ((int)ob.query_invis() == 2)
            if (member_array(this_player()->query_name(),
            (object *)ob.query_allowed()) == -1)
            return 0
            return ob


    def log_file(self, name: str, mess: str) -> None:
            if (file_size("/log/"+name) > MAX_SIZE) {
            seteuid("Root")
            rm("/log/"+name+".old")
            rename("/log/"+name, "/log/"+name+".old")


    def mud_name(self, ) -> str:
            return capitalize(MUD_NAME)


    def cat(self, file: str, start_line: int, number: int) -> None:
            string bing
            seteuid(geteuid(previous_object()))
            bing = read_file(file, start_line, number)
            seteuid(0)
            if (bing)
            printf("%s", bing[0..5000])


    def clone_object(self, name: str) -> MudObject:
            seteuid(geteuid(previous_object()))
            if(name[0..2] == "/d/" || name[0..1] == "d/")
            return (object)HANDLER.clone_virtual_object(name)
            return efun::clone_object(name)


    def destruct(self, name: Any) -> None:
            object obj
            if(stringp(name)) {
            obj = find_object(name)
            if(obj.query_property("file_name"))
            HANDLER.destruct_virtual_object(obj)
            destruct(obj)
            } else if(objectp(name)) {
            if(name.query_property("file_name"))
            HANDLER.destruct_virtual_object(name)
            destruct(name)


    def file_name(self, obj: MudObject) -> str:
            string name, number, file
            name = efun::file_name(obj)
            if(sscanf(name, "%s#%s", name, number) == 2) {
            if(file = (string)obj.query_property("file_name")) {
            return file + "#" + number
            } else {
            return name + "#" + number


    def find_object(self, str: str) -> MudObject:
            object obj
            if(obj = efun::find_object(str))
            return obj
            return (object)HANDLER.find_virtual_object(str)


    def clone_virtual_object(self, name: str) -> MudObject:
            return efun::clone_object(name)


    def __init__(self):
            self.methods = ([ ])
            self.cache = ([ ])


    def add_method(self, suffix: str, ob: Any, fun: str, type: int) -> None:
            if (!type)
            type = CLONE
            if (!methods[suffix]) {
            methods[suffix] = [ob, fun, type]


    def get_mod_time(self, name: str) -> str:
            if(cache[name])
            return cache[name]
            if(file_size(name) <= 0)
            cache[name] = ""
            else
            cache[name] = stat(name)[1]
            return cache[name]


    def create_virtual_object(self, name: str, clone: int) -> MudObject:
            string *split
            mixed  *method
            object ob
            split = explode(name, ".")
            method = methods[split[sizeof(split) - 1]]
            if (method) {
            if (clone ||
            (method[TYPE]&LOAD)) {
            ob =  (object) call_other(method[OB], method[FUN], name, clone)
            if (ob)  {
            ob.add_property(VIRTUAL_NAME_PROP, name)
            if (get_mod_time(name) != "")
            ob.add_property("virtual time", get_mod_time(name))


    def reset(self, ) -> None:
            cache = ([ ])


    def __init__(self):
            self.methods = ([ ])


    def add_method(self, suffix: str, ob: MudObject, fun: str, type: int) -> None:
            if (!type)
            type = CLONE
            if (!methods[suffix]) {
            methods[suffix] = [ob, fun, type]


    def create_virtual_object(self, name: str, clone: int) -> MudObject:
            string *split
            mixed  *method
            object ob
            split = explode(name, ".")
            method = methods[split[sizeof(split) - 1]]
            if (method) {
            if (clone ||
            (method[TYPE]&LOAD)) {
            ob =  (object) call_other(method[OB], method[FUN], name, clone)
            ob.add_property("virtual name", name)
            return ob


    def __init__(self):


    def compile_virtual_room(self, filen: str) -> MudObject:
            {
            string tmp, tmp2
            object new_room
            int i
            i=3
            tmp=read_file(filen, 2, 1)
            tmp2=tmp[1..strlen(tmp)-2]
            new_room=clone_object("/"+tmp2)
            while (read_file(filen, i, 1))
            {
            tmp=read_file(filen, i, 1)
            if(tmp=="") break
            parse_object(new_room, tmp)
            i++


    def parse_object(self, room: MudObject, command: str) -> None:
            {
            string *func_call,s1,s2,s3
            int i1,i2,i3,i4
            if(!command) return
            func_call=explode(command, "#")
            if((string)func_call[0][0]==";") return
            switch (func_call[0])
            {
            case "SHORT" :
            room.set_short(func_call[1])
            break
            case "LONG" :
            room.set_long(func_call[1])
            break
            case "EXIT" :
            room.add_exit(func_call[1], func_call[2])
            break
            case "LIGHT" :
            i1=sscanf(func_call[1], "%d", i2)
            room.set_light(i2)
            break
            case "ITEM" :
            room.add_item(explode(func_call[1], ","), explode(func_call[2], ","))
            break
            case "TASTE" :
            room.add_taste(func_call[1], func_call[2])
            break
            case "SMELL" :
            room.add_smell(func_call[1], func_call[2])
            break
            case "SOUND" :
            room.add_sound(func_call[1], func_call[2])
            break
            case "TOUCH" :
            room.add_feel(func_call[1], func_call[2])
            break
            case "OBJECT" :
            room.add_object(func_call[1])
            break
            case "ACTION" :
            i2=0
            catch(i1=sscanf(func_call[3], "%d", i2))
            room.action_add(func_call[1], func_call[2], i2)
            break
            case "CODE" :
            room.set_code_module(func_call[1])
            break
            case "PROP" :
            room.add_property(func_call[1], func_call[2])
            break
            case "COORD" :
            i1=sscanf(func_call[1], "%d,%d,%d", i2,i3,i4)
            room.set_co_ord(({i2,i3,i4}))
            break


    def __init__(self):


    def initialize_methods(self, ) -> None:
            SERVER.add_method("vrm",  file_name(self), "compile_vrm")
            SERVER.add_method("vro",  file_name(self), "compile_vro")
            SERVER.add_method("vrw",  file_name(self), "compile_vrw")
            SERVER.add_method("vra",  file_name(self), "compile_vra")
            SERVER.add_method("vrc",  file_name(self), "compile_vrc")


    def prop_to_fun(self, file: str, clone: int, incfile: str) -> MudObject:
            string  data, data2, s1, *ind, dir, tmp_name
            int      i
            tmp_name = file+"-"+(tmp_file_no++)+".c"
            if (find_object(tmp_name))
            tmp_name.dest_me()
            ind = explode(file, "/")
            dir = implode(ind[0..sizeof(ind)-2], "/")
            unguarded((: rm, tmp_name :))
            unguarded((: write_file, tmp_name,
            "object MyRoom;\n"
            "#include \""+incfile+"\"\n\n"
            "object this_room() { return MyRoom; }\n" :))
            data = read_file(file)
            if (!data) {
            Error("prop_to_fun() : file " + file + " not found\n")


    def __init__(self):
            self."  MyRoom = (object)\""+SERVER+


    def compile_vrc(self, name: str, clone: int) -> MudObject:
            return prop_to_fun(name, clone, PATH+ROOMFUNCS )


    def compile_vmc(self, name: str, clone: int) -> MudObject:
            return prop_to_fun(name, clone, PATH+MON_FUNCS )


    def compile_vac(self, name: str, clone: int) -> MudObject:
            return prop_to_fun(name, clone, PATH+ARM_FUNCS )


    def compile_vwc(self, name: str, clone: int) -> MudObject:
            return prop_to_fun(name, clone, PATH+WEP_FUNCS )


    def compile_voc(self, name: str, clone: int) -> MudObject:
            return prop_to_fun(name, clone, PATH+OBJ_FUNCS )


    def __init__(self):


    def string_display_file(self, more_string_info: Any) -> None:
            int i
            string stuff
            info->botl = info->topl + ROWS
            stuff = ""
            for ( i = info->topl; ( i < info->botl ) && ( i < info->fsize ); i++ ) {
            stuff += info->the_bit[ i ] +"\n"


    def more_string_status_line(self, more_string_info: Any) -> None:
            string *frog
            string s
            int i
            int percentage
            if (!info->stat_line) {
            info->stat_line = "$N From $T to $B of $S ($%%) - h for help. "


    def string_next_page(self, str: str, more_string_info: Any) -> None:
            int num
            int noargs
            int i
            int redraw
            string s1
            if (!str) {
            str = ""


    def internal_more_string(self, ) -> int:
            string text, bity
            int noreline
            if ( sizeof( _pending_more ) ) {
            text = _pending_more[ 0 ][ 0 ]
            bity = _pending_more[ 0 ][ 1 ]
            noreline = _pending_more[ 0 ][ 2 ]
            _pending_more = _pending_more[ 1 .. <1 ]
            more_string( text, bity, noreline )



class Merged_cmds_global(MudObject):

    current_verb = '""'

    SearchPath = "['DIR_LIVING_CMDS']"

    _event_info = 'new(class event_info,'

    my_colours = '([ ])'

    inform_types = '[]'

    _friends = '([ ])'

    editor = '"menu"'

    _commands = '([ ])'

    _fail_mess = '([ ])'

    _succ_mess = '([ ])'

    _cur_objects = '([ ])'

    _succ_indir = '_succ_mess_dir = _succ_mess_indir = ({ })'

    _pt_data = 'new(class playtester_data)'

    time_left = 'ROUND_TIME'

    tl_updated = 'time()'

    last_command = 'time()'

    queued_commands = '[]'

    _spell_effects = '[]'

    starts = '[]'

    allowed = '[]'

    obvar = '([ ])'

    data = 'read_file( file )'

    methods = '([ ])'

    cache = '([ ])'

    "  MyRoom = '(object)\\""+SERVER+'
