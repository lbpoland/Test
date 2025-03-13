# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/errors.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._user_query = ([ ])


    def find_index(self, person: MudObject, id: int) -> int:
            int i
            class error_summary* errors
            if (!_user_query[person.query_name()]) {
            return 0


    def max_index(self, person: MudObject) -> int:
            if (!_user_query[person.query_name()]) {
            return 0


    def id_at(self, person: MudObject, index: int) -> int:
            if (!_user_query[person.query_name()] || index < 0 ||
            index >= sizeof(_user_query[person.query_name()]->errors)) {
            return 0


    def menu_line(self, person: MudObject) -> str:
            string ret
            ret = "[" + (_user_query[person.query_name()]->pos + 1) + " of " +
            sizeof(_user_query[person.query_name()]->errors) + "] "
            "STFCOLHA-+PNGQ : "
            return ret


    def finish_more_details(self, ) -> int:
            object ob
            ob = this_player()
            write(menu_line(ob))
            input_to("menu_response")


    def finish_forward(self, person: MudObject, pos: int, new_dir: str, type: int, mess: Any) -> int:
            class user_data data
            data = _user_query[person.query_name()]
            if (type != DB_SUCCESS) {
            tell_object(person, "Unable to forward bug #" +
            data->errors[data->pos]->id +
            " to " + new_dir + " (" + mess + ")")
            } else {
            tell_object(person, "Forwarded bug #" +
            data->errors[data->pos]->id +
            " from " + data->errors[data->pos]->directory +
            " to " + new_dir)
            data->errors[data->pos]->directory = new_dir


    def query_subject_from_type(self, type: str, error_summary: Any) -> str:
            switch (type) {
            case "THANKS" :
            return "Thanks for " + error->category + " " + error->type
            case "NOTPOSSIBLE" :
            return "Not possible to fix " + error->category + " " + error->type
            case "NOTREPRODUCIBLE" :
            return "Not able to reproduce " + error->category + " " + error->type
            case "FIXED" :
            return "Fixed bug #" + error->id
            case "DENIED" :
            return "Denied bug #" + error->id
            default :
            return "Change status of bug #" + error->id + " to " +
            type


    def finish_change_type(self, person: MudObject, new_type: str, type: int, mess: Any) -> None:
            class user_data data
            data = _user_query[person.query_name()]
            if (type != DB_SUCCESS) {
            await person.send("Sql Error: " + mess)
            await person.send(menu_line(person))
            return


    def finish_change_category(self, person: MudObject, new_category: str, type: int, mess: Any) -> None:
            class user_data data
            data = _user_query[person.query_name()]
            if (type != DB_SUCCESS) {
            await person.send("Sql Error: " + mess)
            await person.send(menu_line(person))
            return


    def finish_assign_bug(self, person: MudObject, assigner: str, type: int, mess: Any) -> None:
            class user_data data
            data = _user_query[person.query_name()]
            if (type != DB_SUCCESS) {
            await person.send("Sql Error: " + mess)
            await person.send(menu_line(person))
            return


    def finish_adding_comment(self, person: MudObject, type: int, mess: Any) -> None:
            if (type != DB_SUCCESS) {
            await person.send("SQL Error: " + mess)
            await person.send(menu_line(person))


    def finish_comment(self, person: MudObject, id: int, comment: str) -> None:
            if (!comment) {
            write("Aborted adding the comment.\n")
            write(menu_line(person))
            input_to("menu_response")
            return


    def do_bug_details(self, person: MudObject, id: int, verbose: int) -> int:
            if (!ERROR_HANDLER->do_query_bug_details(id, (: finish_details, person,
            verbose :))) {
            await person.send("Error doing stuff.")


    def do_forward(self, person: MudObject, new_dir: str) -> int:
            class user_data data
            data = _user_query[person.query_name()]
            if (!ERROR_HANDLER->do_forward(data->errors[data->pos]->id,
            person.query_name(), new_dir,
            (: finish_forward, person, data->pos, new_dir :))) {
            write("A horrible error occured.\n")
            return 0


    def do_change_type(self, person: MudObject, type: str) -> int:
            class user_data data
            data = _user_query[person.query_name()]
            if (!ERROR_HANDLER->do_change_type(data->errors[data->pos]->id, type,
            (: finish_change_type, person, type :))) {
            await person.send("Error doing stuff.\n")


    def do_change_category(self, person: MudObject, category: str) -> int:
            class user_data data
            data = _user_query[person.query_name()]
            if (!ERROR_HANDLER->do_change_category(data->errors[data->pos]->id, category,
            (: finish_change_category, person, category :))) {
            await person.send("Error doing stuff.\n")


    def do_assign_bug(self, person: MudObject, assigner: str) -> int:
            class user_data data
            data = _user_query[person.query_name()]
            if (!ERROR_HANDLER->do_assign_bug_to(data->errors[data->pos]->id, assigner,
            (: finish_assign_bug, person, assigner :))) {
            await person.send("Error doing stuff.\n")


    def do_comment(self, person: MudObject) -> int:
            class user_data data
            data = _user_query[person.query_name()]
            this_player()->do_edit("", (: finish_comment, person,
            data->errors[data->pos]->id :))


    def do_help(self, player: MudObject) -> int:
            string str
            str = NROFF_HAND.cat_file("/doc/creatornr/errors", 1)
            if (!str) {
            NROFF_HAND.create_nroff("/doc/creator/commands/errors", "/doc/creatornr/errors")
            str = NROFF_HAND.cat_file("/doc/creatornr/errors", 1)


    def do_list_errors(self, ) -> int:
            class user_data data
            class error_summary error
            string str
            int i
            data = _user_query[this_player()->query_name()]
            str = ""
            i = 1
            str += sprintf("ndx: #<num> %5-s %4-s %4-s by %11-s %15-s [%s]\n",
            "Status", "Cat", "Type", "Reporter", "Filename", "Directory")
            foreach (error in data->errors) {
            str += sprintf("$I$3=%3d: #%d %5-s %4-s %4-s by %11-s %15-s [%s]\n",
            i++, error->id, error->status[0..4], error->category[0..3],
            error->type, error->reporter, error->filename[<15..],
            error->directory[<15..])


    def show_current_bug(self, player: MudObject, verbose: int) -> int:
            class user_data data
            data = _user_query[player.query_name()]
            if (verbose == -1) {
            verbose = player.query_verbose("errors")


    def expand_short_type(self, name: str) -> str:
            string str
            str = upper_case(name)
            switch (str) {
            case "F" :
            return ERROR_STATUS_FIXED
            case "D" :
            return ERROR_STATUS_DENIED
            case "I" :
            return ERROR_STATUS_FIXING
            case "C" :
            return ERROR_STATUS_CONSIDERING
            case "O" :
            return ERROR_STATUS_OPEN
            case "U" :
            return "CUSTOM"
            case "R" :
            return "NOTREPRODUCIBLE"
            case "R" :
            return "NOTPOSSIBLE"
            case "N" :
            return "NONE"
            case "T" :
            return "THANKS"
            case "M" :
            return "NOTENOUGHINFORMATION"
            case "E" :
            return "TEMPORARY"
            default :
            return str


    def menu_response(self, str: str) -> None:
            string* bits
            class user_data data
            int print_menu_line
            class error_summary error
            string mess
            string subject
            int id
            bits = explode(str, " ")
            if (!sizeof(bits)) {
            bits = ["n"]


    def finish_query(self, player: MudObject, type: int, data: Any) -> None:
            if (type != DB_SUCCESS) {
            await player.send("Error: " + data + "\n")
            return


    def setup_query(self, player: MudObject, error_query: Any) -> int:
            if (!ERROR_HANDLER.do_query_bug_summary(query, (: finish_query, player :))) {
            add_failed_mess("Unable to setup the query.\n")
            return 0


    def errors_change_status(self, id: int, status: str, messtype: str) -> int:
            class error_query query
            query = new (class error_query)
            query->id = id
            if (!ERROR_HANDLER->do_query_bug_summary(query,
            (: finish_change_status_command, this_player(), id, status,
            messtype :))) {
            add_failed_mess("Unable to setup the query.\n")
            return 0


    def errors_this_dir(self, recursive: int) -> int:
            class error_query query
            query = new (class error_query)
            query->dir = this_player()->query_path()
            query->recursive = recursive
            query->status = [ERROR_STATUS_OPEN, ERROR_STATUS_CONSIDERING,
            ERROR_STATUS_FIXING]
            return setup_query(this_player(), query)


    def errors_by_person(self, person: str) -> int:
            class error_query query
            query = new (class error_query)
            query->reporter = lower_case(person)
            query->status = [ERROR_STATUS_OPEN, ERROR_STATUS_CONSIDERING,
            ERROR_STATUS_FIXING]
            return setup_query(this_player(), query)


    def errors_assigned_to_person(self, person: str) -> int:
            class error_query query
            query = new (class error_query)
            query->assigned_to = lower_case(person)
            query->status = [ERROR_STATUS_OPEN, ERROR_STATUS_CONSIDERING,
            ERROR_STATUS_FIXING]
            return setup_query(this_player(), query)


    def errors_assigned_to_me(self, ) -> int:
            return errors_assigned_to_person(this_player()->query_name())


    def errors_in_dir(self, str: str, recursive: int) -> int:
            class error_query query
            string path
            path = this_player()->get_path(str)
            query = new (class error_query)
            query->dir = path
            query->recursive = recursive
            query->status = [ERROR_STATUS_OPEN, ERROR_STATUS_CONSIDERING,
            ERROR_STATUS_FIXING]
            return setup_query(this_player(), query)


    def errors_with_id(self, id: int) -> int:
            class error_query query
            query = new (class error_query)
            query->id = id
            query->status = [ERROR_STATUS_OPEN, ERROR_STATUS_CONSIDERING,
            ERROR_STATUS_FIXING]
            return setup_query(this_player(), query)


    def errors_for_file(self, file: str) -> int:
            class error_query query
            query = new (class error_query)
            query->file_name = file
            query->status = [ERROR_STATUS_OPEN, ERROR_STATUS_CONSIDERING,
            ERROR_STATUS_FIXING]
            return setup_query(this_player(), query)


    def errors_in_this_room(self, ) -> int:
            class error_query query
            query = new (class error_query)
            query->file_name = file_name(environment(this_player()))
            query->status = [ERROR_STATUS_OPEN, ERROR_STATUS_CONSIDERING,
            ERROR_STATUS_FIXING]
            return setup_query(this_player(), query)



class Errors(MudObject):

    _user_query = '([ ])'
