# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/friend_s.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd_display(self, person: str, pattern: str) -> int:
            string* friends
            string ret
            if (person == "online") {
            friends = filter(this_player()->query_friends(), (: find_player($1) :))
            } else if (person != "") {
            person = this_player()->expand_nickname(person)
            if (!this_player()->is_friend(person)) {
            add_failed_mess(person + " is not your friend.\n")
            return 0


    def cmd_add(self, person: str, tag: str) -> int:
            person = lower_case(person)
            person = this_player()->expand_nickname(person)
            if(person == this_player()->query_name()) {
            add_failed_mess("Are you really that lonely?\n")
            return 0


    def cmd_remove(self, person: str) -> int:
            person = lower_case(person)
            person = this_player()->expand_nickname(person)
            if (!this_player()->is_friend(person)) {
            add_failed_mess("Sorry, " + person + " is not your friend to remove.\n")
            return 0


    def cmd_clear(self, ) -> int:
            write("This will clear all of your friends.  Are you sure you want to do "
            "this? ")
            input_to("clear_check")
            add_succeeded_mess("")
            return 1


    def clear_check(self, str: str) -> None:
            string friend
            if (!strlen(str) || str[0] != 'y') {
            write("Ok, aborting.\n")
            return



class Friend_s(MudObject):
