# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/inherit/error_handler.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def __init__(self):
            protected void setup_error_handler(string user, string db, string password) {
            _user = user
            _db = db
            _password = password
            save_object(SAVE_FILE)


    def build_sql_update(self, id: int, field: str, value: Any) -> str:
            string ret
            ret = "update errors set " + field + " = "
            if (stringp(value)) {
            ret += "'" + value + "'"
            } else {
            ret += "" + value


    def finish_summary(self, type: int, data: Any, finished: Any, query: str) -> None:
            class error_summary* errors
            mapping map
            if (type != DB_SUCCESS) {
            evaluate(finished, type, data, query)
            } else {
            errors = [})
            foreach (map in data) {
            errors += [create_error_summary(map)]


    def finish_details(self, type: int, data: Any, finished: Any, query: str) -> None:
            class error_complete* errors
            mapping map
            string str
            if (type != DB_SUCCESS) {
            evaluate(finished, type, data, query)
            } else {
            errors = [})
            str = "("
            foreach (map in data) {
            errors += [create_error_complete(create_error_details(map))]
            str += map["id"] + ","


    def finish_update(self, type: int, data: Any, finished: Any, query: str) -> None:
            evaluate(finished, type, data, query)


    def finish_error_replies(self, type: int, data: Any, finished: Any, query: str) -> None:
            class error_replies* replies
            mapping map
            if (type != DB_SUCCESS) {
            evaluate(finished, type, data)
            } else {
            replies = [})
            foreach (map in data) {
            replies += [create_error_replies(map)]


    def do_query_bug_summary(self, error_query: Any, finished: Any) -> int:
            string str
            str = build_sql_query(ERROR_SUMMARY_FIELDS,
            query)
            if (!str) {
            return 0


    def do_query_bug_details(self, bug_id: int, finished: Any) -> int:
            string str
            class error_query query
            query = new(class error_query)
            query->id = bug_id
            str = build_sql_query(ERROR_DETAILS_FIELDS, query)
            if (!str) {
            return 0


    def do_query_open_bugs_in_dir(self, dir: str, finished: Any) -> int:
            class error_query query
            query = new(class error_query)
            query->dir = dir
            query->status = ["OPEN", "FIXING", "CONSIDERING"]
            return do_query_bug_summary(query, finished)


    def do_query_open_bugs_for_fname(self, fname: str, finished: Any) -> int:
            class error_query query
            query = new(class error_query)
            query->file_name = fname
            query->status = ["OPEN", "FIXING", "CONSIDERING"]
            return do_query_bug_summary(query, finished)


    def do_query_open_bugs_by_reporter(self, reporter: str, finished: Any) -> int:
            class error_query query
            query = new(class error_query)
            query->reporter = reporter
            query->status = ["OPEN", "FIXING", "CONSIDERING"]
            return do_query_bug_summary(query, finished)


    def do_change_type(self, id: int, type: str, finished: Any) -> int:
            string str
            str = build_sql_update(id, "type", type)
            if (!str) {
            return 0


    def do_change_category(self, id: int, category: str, finished: Any) -> int:
            string str
            str = build_sql_update(id, "category", category)
            if (!str) {
            return 0


    def do_assign_bug_to(self, id: int, assigned_to: str, finished: Any) -> int:
            string str
            str = build_sql_update(id, "assignedto", assigned_to)
            if (!str) {
            return 0


    def do_forward(self, id: int, user: str, dir: str, finished: Any) -> int:
            string str
            class error_query query
            if (!strlen(dir)) {
            return 0


    def do_comment(self, id: int, user: str, comment: str, finished: Any) -> int:
            string str
            str = "insert into comments (id,commentdate,commenter,comment) values (" +
            id + ", " + time() + ", '" + user + "', '" + db_escape(comment) +
            "')"
            DB_HANDLER->make_sql_request(_db, _user, _password, str,
            (: finish_update($1, $2, $(finished), $(str)) :))
            return 1


    def do_error_replies(self, recipient: str, only_new: int, finished: Any) -> int:
            string str
            str = "select * from error_replies where recipient = '" + recipient +
            "'"
            if (only_new) {
            str += " and status = 'NEW'"
            } else {
            str += " and status != 'DELETED'"


    def do_status_error_reply(self, id: int, status: str, finished: Any) -> int:
            string str
            str = "update error_replies set status = '" + status + "' where id = " +
            id
            DB_HANDLER->make_sql_request(_db, _user, _password, str,
            (: finish_update($1, $2, $(finished), $(str)) :))
            return 1


    def do_add_error_reply(self, bug_id: int, from: str, to: str, subject: str, message: str) -> int:
            string str
            str = "insert into error_replies (bug_id,status,sender,recipient,senddate,message,subject) "
            "values (" + bug_id + ", 'NEW', '" + from + "', '" + to + "', " +
            time() + ", '" +
            db_escape(message) + "', '" + db_escape(subject) + "')"
            DB_HANDLER->make_sql_request(_db, _user, _password, str,
            (: 1 :) )
            return 1



class Error_handler(MudObject):
