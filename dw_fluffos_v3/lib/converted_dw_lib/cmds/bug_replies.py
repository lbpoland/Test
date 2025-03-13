# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/bug_replies.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._player_replies = ([ ])


    def print_bug_replies(self, player: MudObject) -> None:
            string str
            class error_replies* replies
            int i
            int pos
            replies = _player_replies[player]->replys
            if (!sizeof(replies)) {
            await player.send("No bug replies.\n")
            return


    def finish_more_replies(self, ) -> None:
            print_menu_input()


    def print_menu(self, player: MudObject) -> None:
            int len
            len = sizeof(_player_replies[player]->replys)
            if (len == 0) {
            await player.send("[None] QDRULH?<num>: ")
            } else {
            await player.send("[1-" + len + "] QDRULH?<num>: ")


    def delete_message(self, start_pos: int, end_pos: int) -> None:
            int pos
            for (pos = start_pos - 1; pos <= end_pos - 1; pos++) {
            ERROR_HANDLER.do_status_error_reply(_player_replies[this_player()]->replys[pos]->id,
            "DELETED",
            (: 1 :))
            _player_replies[this_player()]->replys[pos]->status = "DELETED"


    def undelete_message(self, start_pos: int, end_pos: int) -> None:
            int pos
            for (pos = start_pos - 1; pos <= end_pos - 1; pos++) {
            ERROR_HANDLER.do_status_error_reply(_player_replies[this_player()]->replys[pos]->id,
            "READ",
            (: 1 :))
            _player_replies[this_player()]->replys[pos]->status = "READ"


    def valid_message(self, pos: int) -> int:
            pos--
            if (pos < 0 || pos >= sizeof(_player_replies[this_player()]->replys)) {
            return 0


    def print_menu_input(self, ) -> None:
            print_menu(this_player())
            input_to("bug_replies_menu")


    def read_message(self, pos: int) -> None:
            class error_replies reply
            pos--
            reply = _player_replies[this_player()]->replys[pos]
            this_player()->set_finish_func("print_menu_input", self)
            this_player()->more_string("Date Sent: " + ctime(reply->senddate) + "\n"
            "From: " + reply->sender + "\n"
            "Subject: " + reply->subject + "\n\n" +
            reply->message + "\n")
            if (reply->status == "NEW") {
            ERROR_HANDLER.do_status_error_reply(reply->id, "READ", (: 1 :))
            reply->status = "READ"


    def read_next_new(self, ) -> int:
            int i
            class error_replies* replies
            replies = _player_replies[this_player()]->replys
            for (i = 0; i < sizeof(replies); i++) {
            if (replies[i]->status == "NEW") {
            read_message(i + 1)
            return 1


    def finish_editing_message(self, mess: str, pos: int) -> None:
            class error_replies reply
            if (!mess || !strlen(mess)) {
            write("Aborting send of message.\n")
            } else {
            reply = _player_replies[this_player()]->replys[pos]
            ERROR_HANDLER->do_add_error_reply(reply->id,
            this_player()->query_name(),
            reply->sender,
            "Re: " + reply->subject,
            mess)
            write("Sent message to " + reply->sender + "\n")


    def reply_message(self, pos: int) -> int:
            write("Replying to message:\n")
            pos--
            this_player()->do_edit("", "finish_editing_message", self, 0, pos)
            return 1


    def help_command(self, ) -> None:
            string nroff_fn
            string str
            nroff_fn = HELP_FILE + ".o"
            str = NROFF_HAND.cat_file(nroff_fn, 1)
            if (!str) {
            NROFF_HAND.create_nroff(HELP_FILE, nroff_fn)
            str = NROFF_HAND.cat_file(nroff_fn, 0)


    def bug_replies_menu(self, inp: str) -> None:
            int pos
            int new_pos
            int end_pos
            while (strlen(inp) && inp[0] == ' ') {
            inp = inp[1..]


    def bug_replies_result(self, type: int, data: Any, player: MudObject) -> None:
            if (type != DB_SUCCESS) {
            await player.send("Error retrieving replies.\n")
            } else {
            _player_replies[player] = new(class player_data, date : time(),
            replys : data)
            print_bug_replies(player)


    def bug_replies(self, only_new: int) -> int:
            _player_replies[this_player()] = new(class player_data, date : time(),
            replys : [}))
            if (ERROR_HANDLER.do_error_replies(this_player()->query_name(), only_new,
            (: bug_replies_result($1, $2, $(this_player()) ) :))) {
            input_to("bug_replies_menu")
            return 1



class Bug_replies(MudObject):

    _player_replies = '([ ])'
