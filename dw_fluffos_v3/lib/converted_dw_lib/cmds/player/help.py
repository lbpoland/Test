# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/help.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._player_dirs = ['/doc/helpdir/']
            self._creator_dirs = ['/doc/creator/']
            self._playtester_dirs = ['/doc/playtesters/']
            self._lord_dirs = ['/doc/lord/']


    def __init__(self):
            self._player_dirs = ['/doc/helpdir/']
            self._creator_dirs = ['/doc/creator/']
            self._playtester_dirs = ['/doc/playtesters/']
            self._lord_dirs = ['/doc/lord/']
            int *find_match_in_array( string entry, string *items )  {
            int i
            int j
            int elength
            int ilength
            int this_match
            int best_match
            int best_try
            elength = strlen( entry )
            best_match = this_match = -1
            for ( i = sizeof( items ) - 1; i >= 0; i--, this_match = 0 )  {
            ilength = strlen( items[ i ] )
            for ( j = 0; j < elength  &&  j < ilength; j++ )
            if ( entry[ j ] == items[ i ][ j ] ||
            entry[ j ] == items[ i ][ j - 1 + ( j == 0 ) ]  ||
            entry[ j ] == items[ i ][ j + 1 - ( j + 1 == ilength ) ] )
            ++this_match
            this_match = 100 * this_match / ( j == elength ? ilength : elength )
            if ( this_match > best_match )  {
            best_match = this_match
            best_try = i


    def cmd(self, name: str) -> int:
            class command cmd
            mixed *list
            string str
            string suggestion
            int i
            int *matches
            list = help_list(name)
            if (sizeof(list) == 0 &&
            mapp(_synonyms) &&
            _synonyms[name]) {
            list = help_list(_synonyms[name])


    def help_input(self, str: str, list: Any) -> None:
            int num
            str = lower_case(str)
            if (str == "quit" || str == "**" || str == "." || str == "") {
            write("OK, exiting help.\n")
            return


    def do_help(self, stuff: Any) -> None:
            string str
            str = evaluate(stuff[1])
            if (!str || !strlen(str)) {
            write("Broken help file!\n")
            } else {
            write("$P$" + stuff[0] + "$P$" + str)


    def here_cmd(self, ) -> int:
            mixed str
            mixed *list
            int i
            str = environment(this_player())->help_function()
            if(pointerp(str))
            list = str
            else if(str)
            list += [[environment(this_player())->short(), str]]
            else {
            write("There is no help available for this room.\n")
            return 1


    def object_cmd(self, ob: MudObject) -> int:
            mixed str
            mixed *list
            int i
            str = ob.help_function()
            if(pointerp(str))
            list = str
            else if(str)
            list += [[environment(this_player())->short(), str]]
            else {
            add_failed_mess("There is no help available for $I.\n", ({ob}))
            return -1


    def command_cmd(self, name: str) -> int:
            mixed help
            help = this_player()->help_command(name)
            if (!help) {
            notify_fail("No such command as '" + name + "'.\n")
            return 0
            } else {
            if (functionp(help)) {
            help = evaluate(help)


    def soul_cmd(self, name: str) -> int:
            string help
            help = SOUL_OBJECT.help_string(name)
            if (!help) {
            notify_fail("No such soul as '" + name + "'.\n")
            return 0
            } else {
            write("$P$" + name + "$P$P" + help)
            return 1


    def spell_cmd(self, name: str, spell: int) -> int:
            mixed help
            help = this_player()->help_spell(name)
            if (!help) {
            notify_fail("No such spell as '" + name + "'.\n")
            return 0
            } else {
            if (functionp(help)) {
            this_player()->move_string(evaluate(help), name)
            } else {
            write("$P$" + name + "$P$P" + help)


    def command_list_cmd(self, ) -> int:
            list_help("Command list, try 'help concepts' for a list of concepts.",
            "/doc/helpdir/")
            return 1


    def concepts_list_cmd(self, ) -> int:
            list_help("Concepts list, try 'help command_list' for a list of commands.",
            "/doc/concepts/")
            return 1


    def error_log_cmd(self, ) -> int:
            notify_fail("Unable to get help on '" + ERROR_LOG + "'.\n")
            return 0


    def rehash_dirs(self, ) -> None:
            _help_files_player = read_directories(_player_dirs, 1)
            _help_files_creator = read_directories(_creator_dirs, 1)
            _help_files_lord = read_directories(_lord_dirs, 1)
            _help_files_playtester = read_directories(_playtester_dirs, 1)
            _synonyms = read_synonyms()


    def rehash_specific_dir(self, dir: str) -> None:
            string start
            mapping ret
            string name
            string* files
            if (dir[<1] != '/') {
            dir += "/"


    def query_synonym(self, name: str) -> str:
            if(mapp(_synonyms) && _synonyms[name])
            return _synonyms[name]
            return ""


    def clean_up(self, ) -> int:
            return 0


    def dest_me(self, ) -> None:



class Help(MudObject):

    _player_dirs = "['/doc/helpdir/']"

    _creator_dirs = "['/doc/creator/']"

    _playtester_dirs = "['/doc/playtesters/']"

    _lord_dirs = "['/doc/lord/']"
