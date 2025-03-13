# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/dom/error_tracker_master.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def do_the_work(self, ) -> None:
            protected void save_me()
            {
            if (domain != "unset" && _save_file) {
            unguarded( (: save_object, _save_file, 0 :) )


    def __init__(self):
            self._messages = ([ ])
            self._tester = 0
            self._save_file = file_name()
            self.temp = "/save/" + replace(file_name()[1..], "/", "_")
            self._save_file = temp


    def set_board(self, board: str) -> None:
            _board = board


    def query_board(self, ) -> str:
            return _board


    def dest_me(self, ) -> None:
            {
            save_me()
            destruct(self)


    def query_post_message(self, ) -> str:
            string message
            int diff
            if (!sizeof(_messages)) {
            message = "Congratulations!   There are no errors in all of " +
            capitalize(domain) + "!   Excellent work, everyone.\n"


    def query_project_message(self, ) -> str:
            string str
            class project* projects, *my_projects
            class project project
            mapping status
            str = "\nCurrent Domain Projects:\n\n"
            projects = PROJECT_HANDLER.filter_by_query(([ "domains" : domain ]))
            if (sizeof(projects)) {
            status = unique_mapping( projects, (: STATUS[((class project)$1)->status] :) )
            map_delete( status, "play" )
            if ( !sizeof(status) ){
            str += "This domain is project free.\n"


    def initialise_variables(self, ) -> None:
            _queue = ["/d/" + domain + "%"] + other_dirs
            _messages = ([ ])


    def do_the_work(self, ) -> None:
            {
            if (domain == "unset") return
            nexttime = time() + period
            remove_asyncio.create_task(self."do_the_work")
            asyncio.create_task(self."do_the_work", period)
            save_me()
            starttime = real_time()
            initialise_variables()
            iterate()


    def set_name(self, name: str) -> None:
            {
            tracker_name = name
            save_me()


    def set_domain(self, name: str) -> None:
            {
            domain = name
            save_me()


    def query_domain(self, ) -> str:
            return domain


    def set_period(self, length: int) -> None:
            {
            remove_asyncio.create_task(self."do_the_work")
            nexttime -= period
            period = length
            nexttime += period
            save_me()


    def set_other_dirs(self, others: str) -> None:
            {
            if (arrayp(others)) {
            other_dirs = others
            } else {
            other_dirs = [})


    def stats(self, ) -> Any:
            {
            return ({
            ["domain", domain],
            ["name", tracker_name],
            ["period", period],
            ["next time", ctime(nexttime)],
            ["testing by", _tester],
            ["queue length", sizeof(_queue)],
            ["message length", sizeof(_messages)],
            ["other dirs", sizeof(other_dirs) ? implode(other_dirs, ", ") : 0],
            ["save file", _save_file],
            })



class Error_tracker_master(MudObject):

    _messages = '([ ])'

    _tester = 0

    _save_file = 'temp'

    temp = '"/save/" + replace(file_name()[1..], "/", "_")'
