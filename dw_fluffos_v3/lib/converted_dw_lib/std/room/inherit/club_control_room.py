# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/inherit/club_control_room.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._percentage_cut = 5
            self._room_type = CLUB_ROOM_CLUB_OR_FAMILY


    def __init__(self):
            self._percentage_cut = 5
            self._room_type = CLUB_ROOM_CLUB_OR_FAMILY
            private int club_commands_allowed() {
            return _room_type != CLUB_ROOM_FAMILY_ONLY


    def init(self, ) -> None:
            string bit
            if (club_commands_allowed()) {
            add_help_file("club_control_room")
            bit = "club name"
            add_command("create", "club called <string'club name'>",
            (: do_create($4[0]) :))
            add_command("list", "clubs",
            (: club_list(this_player()->query_name(), 0, 0) :) )
            add_command("list", "clubs [with member] <string'member name'>",
            (: do_club_list_member($4[0]) :))
            add_command("list", "club <string'club name'>",
            (: club_info($4[0], 1, this_player()->query_name()) :) )
            add_command("vote",
            "<word'person'> for <string:small'position'> in <string'club name'>",
            (: do_vote($4[0], $4[1], $4[2]) :))
            add_command("nominate",
            "<word'person'> for <string:small'position'> in <string'club name'>",
            (: do_nominate($4[0], $4[1], $4[2]) :))
            add_command("disband", "<string'club name'>", (: do_disband($4[0]) :))
            add_command("change", "<string'club name'> to {elected}",
            (: do_change($4[0], "elected") :) )
            add_command("change", "<string'club name'> option {secret|open}",
            (: do_change_option($4[0], $4[1]) :) )
            add_command("replace", "<number> insignia for <string'club name'>",
            (: do_insignia($4[1], $4[0]) :))
            add_command("replace", "insignia for <string'club name'>",
            (: do_insignia($4[0], 1) :))
            add_command("recruiter", "add <string'member'> for <string'club'>",
            (: do_recruiter_add($4[1], $4[0]) :))
            add_command("recruiter", "remove <string'member'> for <string'club'>",
            (: do_recruiter_remove($4[1], $4[0]) :))
            add_command("financials", "<string'club'>",
            (: do_financials($4[0], CLUB_DEFAULT_ACCOUNT_NAME) :))
            add_command("financials", "<string'club'> account <string'account name'>",
            (: do_financials($4[0], $4[1]) :))
            add_command("description", "of club <string'club name'>",
            (: do_describe($4[0]) :))
            add_command("announce", "for club <string'club name'>",
            (: do_announcement($4[0]) :))
            add_command("withdraw", "<string'money'> from <string'club name'> for <string:small'reason'>",
            (: do_withdrawl($4[0], $4[1], CLUB_DEFAULT_ACCOUNT_NAME, $4[2]) :))
            add_command("withdraw", "<string'money'> from <string'club name'> for <string:quoted'reason'>",
            (: do_withdrawl($4[0], $4[1], CLUB_DEFAULT_ACCOUNT_NAME, $4[2]) :))
            add_command("withdraw", "<string'money'> from <string'club name'> account <string'account name'> for <string:small'reason'>",
            (: do_withdrawl($4[0], $4[1], $4[2], $4[3]) :))
            add_command("withdraw", "<string'money'> from <string'club name'> account <string'account name'> for <string:quoted'reason'>",
            (: do_withdrawl($4[0], $4[1], $4[2], $4[3]) :))
            add_command("transfer", "<string'money'> from <string'club name'> account <string'source account'> to <string'desination account'> for <string:small'reason'>",
            (: do_transfer($4[0], $4[1], $4[2], $4[3], $4[4]) :))
            add_command("transfer", "<string'money'> from <string'club name'> account <string'source account'> to <string'desination account'> for <string:quoted'reason'>",
            (: do_transfer($4[0], $4[1], $4[2], $4[3], $4[4]) :))
            add_command("election", "force in <string'club'>",
            (: do_force_election($4[0]) :))
            club_discuss::init()


    def is_valid_club_name(self, name: str) -> int:
            int i
            if (strlen(name) > CLUB_MAX_NAME_LEN) {
            return 0


    def set_club_control_type(self, room_type: int) -> None:
            _room_type = room_type


    def query_club_control_type(self, ) -> int:
            return _room_type


    def set_club_region(self, region: str) -> None:
            _region = region


    def query_club_region(self, ) -> str:
            return _region


    def is_valid_family_name(self, name: str) -> int:
            if (PLAYER_HANDLER.test_user(lower_case(name))) {
            add_failed_mess("Cannot use the family name '" + name + "' since "
            "a player is already using it.\n")
            return 0


    def set_percentage_cut(self, value: int) -> None:
            _percentage_cut = value


    def query_percentage_cut(self, ) -> int:
            return _percentage_cut


    def query_club_warning_message(self, ) -> str:
            string place
            string ret
            place = query_property("place")
            if (!place) {
            place = "default"



class Club_control_room(MudObject):

    _percentage_cut = 5

    _room_type = 'CLUB_ROOM_CLUB_OR_FAMILY'
