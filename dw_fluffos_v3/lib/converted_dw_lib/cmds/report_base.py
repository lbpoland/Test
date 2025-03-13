# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/report_base.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._globals = ([ ])


    def set_error_type(self, type: str) -> None:
            {
            _error_type = type


    def set_use_last_error(self, error: int) -> None:
            {
            _use_last_error = error


    def query_use_last_error(self, ) -> int:
            {
            return _use_last_error


    def bug_room(self, ) -> int:
            {
            if (environment(this_player())) {
            _globals[this_player()] = new (class errors, type: ROOM_BUG, error: "ROOM " + _error_type, file:file_name(environment
            (this_player
            ())))
            } else {
            _globals[this_player()] = new (class errors, type: ROOM_BUG, error: "ROOM " + _error_type, file:"/d/mudlib/void")


    def bug_special(self, which: str) -> int:
            _globals[this_player()] = new (class errors,
            type: GENERAL_BUG,
            error: "GENERAL " + _error_type,
            file: "/d/special/"+which+"/BugReports")
            this_player()->do_edit(0, "end_of_edit")
            return 1


    def bug_misc(self, which: str) -> int:
            _globals[this_player()] = new (class errors,
            type: GENERAL_BUG,
            error: "GENERAL " + _error_type,
            file: "/obj/"+which+"/BugReports")
            this_player()->do_edit(0, "end_of_edit")
            return 1


    def bug_general(self, ) -> int:
            {
            string dir
            string *bits
            string file
            if (!environment(this_player())) {
            dir = "/d/am/fluff"
            } else {
            dir = file_name(environment(this_player()))


    def bug_command(self, str: str) -> int:
            {
            int i
            string dir
            string file
            string *bits
            mixed *junk,
            *coms
            class command cmd
            class errors bing
            class command_data cmd_data
            class command_class cmd_class
            mapping temp
            bing = new (class errors)
            coms = [})
            junk = actions_defined(this_player(), 0, 12)
            for (i = 0; i < sizeof(junk); i += 2) {
            if (junk[i] == str) {
            coms += [junk[i], junk[i + 1][0], junk[i + 1][1]]


    def bug_help(self, str: str) -> int:
            {
            mixed *stuff
            class errors bing
            string tmp
            bing = new (class errors)
            tmp = "/cmds/player/help"->query_synonym(str)
            if (strlen(tmp))
            str = tmp
            if (str && str != "") {
            stuff = "/cmds/player/help"->query_help_on(str)
            if (!sizeof(stuff)) {
            if (!SOUL_OBJECT.query_soul_command(str)) {
            notify_fail("Could not find the help file '" + str +
            "'.  If you wish "
            "to suggest a new command use 'idea help'\n")
            return 0
            } else {
            bing->file = "/soul/" + str


    def bug_soul(self, str: str) -> int:
            {
            class errors bing
            string tmp
            bing = new (class errors)
            if (str)  {
            tmp = sprintf("/soul/%c/%s.s", str[0], str)
            if (file_size(tmp) < 1)  {
            notify_fail("No such soul command \"" + str + "\".\n")
            return 0


    def bug_ritual(self, str: str) -> int:
            {
            mapping junk
            class errors bing
            string sname
            mixed* data
            string file
            str = this_player()->expand_nickname(str)
            bing = new (class errors)
            junk = this_player()->query_spells()
            foreach (sname, data in junk) {
            if (lower_case(sname) == lower_case(str)) {
            if (sizeof(data) <= S_OBJECT) {
            file = file_name(environment(this_player()))
            } else {
            file = data[S_OBJECT]


    def bug_web(self, url: str) -> int:
            {
            class errors bing
            bing = new (class errors)
            bing->file = "/www/fluff"
            bing->error = "OBJECT " + _error_type + " " + url
            bing->type = WEB_BUG
            _globals[this_player()] = bing
            this_player()->do_edit("Url: " + url + "\n\n", "end_of_edit")
            return 1


    def bug_spell_file(self, file: str, name: str) -> int:
            {
            class errors bing
            bing = new (class errors)
            bing->file = file
            bing->error = "SPELL " + _error_type + " " + name
            bing->type = SPELL_BUG
            _globals[this_player()] = bing
            this_player()->do_edit(0, "end_of_edit")
            return 1


    def bug_spell(self, str: str) -> int:
            {
            mapping junk
            string file
            string sname
            mixed data
            if (str == "wizards" || str == "witches") {
            file = "/obj/spells/" + str
            } else {
            str = this_player()->expand_nickname(str)
            junk = this_player()->query_spells()
            foreach (sname, data in junk) {
            if (lower_case(sname) == lower_case(str) && arrayp(data)) {
            file = data[S_OBJECT]


    def bug_object_new(self, name: str) -> int:
            {
            string info
            class errors bing
            bing = new (class errors)
            bing->file = base_name(environment(this_player()))
            bing->error = "OBJECT " + _error_type + " " + name
            bing->type = OBJECT_BUG
            bing->extra = info
            _globals[this_player()] = bing
            this_player()->do_edit(0, "end_of_edit")
            return 1


    def end_of_edit(self, body: str) -> None:
            {
            if (strlen(body)) {
            int ending
            string name,
            trace = 0
            mapping last_error
            class errors bing
            bing = _globals[this_player()]
            if (bing->extra) {
            body = bing->extra + body


    def clean_up(self, ) -> int:
            {
            return 0


    def reset(self, ) -> None:
            {



class Report_base(MudObject):

    _globals = '([ ])'
