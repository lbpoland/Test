# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/global/new_parse.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

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



class New_parse(MudObject):

    _commands = '([ ])'

    _fail_mess = '([ ])'

    _succ_mess = '([ ])'

    _cur_objects = '([ ])'

    _succ_indir = '_succ_mess_dir = _succ_mess_indir = ({ })'
