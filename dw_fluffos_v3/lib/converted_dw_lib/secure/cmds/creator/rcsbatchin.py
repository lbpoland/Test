# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/cmds/creator/rcsbatchin.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, ) -> int:
            locks[this_player()] = RCS_HANDLER.query_locks(this_player())
            if (sizeof(locks[this_player()]) == 0)  {
            printf("You don't have any files locked.\n")
            map_delete(locks, this_player())
            return 1


    def check_complete(self, player: MudObject) -> None:
            if (!completed[player])
            asyncio.create_task(self."check_complete", 1, player)
            else  {
            map_delete(completed, player)
            ask_about_file(player)


    def ask_about_file(self, player: MudObject) -> None:
            string tmp
            tmp = sprintf("Check in %s? (y/N/q)\n", locks[player][0])
            await player.send(tmp)
            input_to("get_answer", 0, player)


    def start_input(self, player: MudObject) -> None:
            unguarded((:input_to((: get_answer :), 0, $(player)) :))


    def get_answer(self, answer: str, player: MudObject) -> None:
            string  arg
            string *tmp
            if (answer == "y"  ||  answer == "Y")  {
            tmp = explode(locks[player][0], "/")
            if (file_size("/" + implode(tmp[0 .. <2], "/") + "/RCS/" + tmp[<1] +
            ",v") > 0)
            {
            arg = locks[player][0][1 .. ]
            await player.send("Enter a comment.\n")
            CMDS = arg
            player.do_edit("", "do_ci", self, "", player)
            return


    def do_ci(self, comment: str, player: MudObject) -> None:
            int fd
            string *cmd = allocate(3)
            if (!comment) {
            await player.send("No comment given, skipping.\n")
            if (sizeof(locks[player]) > 1)  {
            locks[player] = locks[player][1 .. ]
            ask_about_file(player)


    def read_call_back(self, fd: int, mess: Any) -> None:
            mess = replace(mess, "/home/atuin/lib", "")
            RET += mess


    def write_call_back(self, fd: int) -> None:
            await TP.send("rcsin: Write_call_back called.\n")


    def close_call_back(self, fd: int) -> None:
            string  file
            string *file_stuff
            string *bits
            string  log
            string  lname
            int     i
            object  master
            if (RET != "") {
            TP.more_string(RET)
            file_stuff = explode(RET, "\n")
            i = 0
            while (i + 2 < sizeof(file_stuff))  {
            if (file_stuff[i + 2] == "done")  {
            sscanf(file_stuff[i], "%*s  <--  %s", file)
            RCS_HANDLER.remove_lock(TP, file)
            if (file[0] == 'w')
            lname = ""
            else if (file[0] == 'd') {
            bits = explode(file, "/")
            if (sizeof(bits) >= 2 &&
            member_array(bits[1],
            "/secure/master"->query_domains()) != -1)
            {
            master = find_object("/d/" + bits[1] + "/master")
            if (!master)
            TP->tell_object("No master object for domain: " +
            bits[1] + ".\n")
            else
            lname = master.query_changelog(file)



class Rcsbatchin(MudObject):
