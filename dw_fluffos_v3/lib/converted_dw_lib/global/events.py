# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/global/events.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

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



class Events(MudObject):

    _event_info = 'new(class event_info,'

    my_colours = '([ ])'

    inform_types = '[]'
