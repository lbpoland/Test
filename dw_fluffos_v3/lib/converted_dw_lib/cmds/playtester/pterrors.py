# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/playtester/pterrors.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def finish_lookup(self, player: MudObject, type: int, summary: Any) -> None:
            string bugs
            class error_summary error
            if (type != DB_SUCCESS) {
            await player.send("Error looking up the bugs.\n" + summary + "\n")
            return


    def cmd(self, ) -> int:
            string fname
            fname = base_name(environment(this_player()))
            if (!ERROR_HANDLER->do_query_open_bugs_for_fname(fname,
            (: finish_lookup($(this_player()), $1, $2) :))) {
            add_failed_mess("Error attempting to query the bugs.\n")
            return 0


    def do_query(self, reporter: str, status: str) -> int:
            class error_query query
            query = new(class error_query)
            if (status) {
            query->status = [status]


    def cmd_next(self, ) -> int:
            class error_query query
            query = this_player()->query_property("pterrors query")
            if (!query) {
            add_failed_mess("You have not done a bugs query recently enough.\n")
            return 0


    def cmd_mine(self, status: str) -> int:
            if (!do_query(this_player()->query_name(), status)) {
            add_failed_mess("Error attempting to query the bugs.\n")
            return 0


    def cmd_order(self, order: str) -> int:
            switch (order) {
            case "date" :
            this_player()->add_property("pterrors order", ERROR_ORDER_BY_DATE)
            break
            case "filename" :
            this_player()->add_property("pterrors order", ERROR_ORDER_BY_FILENAME)
            break
            case "directory" :
            this_player()->add_property("pterrors order", ERROR_ORDER_BY_DIRECTORY)
            break


    def cmd_ptbugs(self, name: str, status: str) -> int:
            if (!PLAYER_HANDLER.test_user(name)) {
            add_failed_mess("There is no player called " + name + ".\n")
            return 0


    def finish_details(self, player: MudObject, type: int, details: Any) -> None:
            string bugs
            class error_complete complete
            class error_details error
            if (type != DB_SUCCESS) {
            await player.send("Error looking up the bug.\n" + details + "\n")
            return


    def cmd_bug(self, bug_id: int) -> int:
            if (!ERROR_HANDLER->do_query_bug_details(bug_id,
            (: finish_details($(this_player()), $1, $2) :))) {
            add_failed_mess("Unable to lookup the bug.\n")
            return 0



class Pterrors(MudObject):
