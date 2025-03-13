# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/living/l_ook.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def finish_bug_summary(self, player: MudObject, type: int, data: Any) -> None:
            class error_complete summ
            class error_complete* errors
            string str
            int pos
            if (type != DB_SUCCESS) {
            return


    def show_error_summary(self, player: MudObject, types: Any) -> None:
            class error_query query
            if (!arrayp(types) || !sizeof(types)) {
            return


    def cmd_look_room(self, ) -> int:
            {
            object room
            int dark
            string ret
            int *coords
            room = environment(TP)
            if (!room) {
            add_failed_mess("You are in limbo... sorry you can't look at " +
            "anything.\n")
            return 0


    def cmd_string(self, arg: str) -> Any:
            {
            object room
            int dark
            int retval
            string ret
            string other
            string orig_arg
            mixed *func
            room = environment(TP)
            if (TP.query_blinded()) {
            add_failed_mess("You are blind and cannot see.\n")
            return 0


    def check_exists(self, file: str) -> int:
            {
            int retval
            if (objectp(find_object(file))) {
            return 1


    def weather_long(self, str: str) -> str:
            {
            object env
            string temp
            string whandler
            env = environment(TP)
            temp = (string) env.query_property("location")
            switch (temp) {
            case ("inside"):
            return "You are not outside.\n"


    def look_around(self, ) -> str:
            {
            int i
            int j
            string prep
            string room
            string *parts
            string *rooms
            object place
            object thing
            object *contents
            mixed *locations
            if (TP.query_blinded()) {
            add_failed_mess("You are blind and cannot see.\n")
            return 0



class L_ook(MudObject):
