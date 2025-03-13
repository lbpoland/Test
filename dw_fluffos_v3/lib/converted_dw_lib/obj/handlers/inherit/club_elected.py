# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/inherit/club_elected.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def query_club_board_name(self, club_name: str) -> str:
            class election_info {
            string treasurer
            string president
            string vice_president
            string secretary
            mapping account_info
            mapping positions
            int last_election
            int election_period
            mapping options
            class discussion_idea *discussion
            class club_archive *archives
            string announcement
            int announce_time


    def __init__(self):
            self._elections = ([ ])
            self._boards = []
            self._boards = []


    def disband_club(self, name: str) -> int:
            if (::disband_club(name)) {
            map_delete(_elections, name)
            _boards -= [query_club_board_name(name)]
            save_main()
            return 1


    def remove_member(self, club: str, member: str) -> int:
            class election_info bing
            class account_info fluff
            string account
            string person
            string position
            string name
            mapping nominations
            string *people
            if (::remove_member(club, member)) {
            bing = query_elected_info(club)
            if (bing) {
            foreach (account, fluff in bing->account_info) {
            fluff->allowed_people -= [member]


    def query_last_election(self, name: str) -> int:
            class election_info info
            info = query_elected_info(name)
            if (info) {
            return info->last_election


    def query_next_election(self, name: str) -> int:
            int bing
            bing = query_last_election(name)
            if (bing) {
            return bing + CLUB_ELECTION_PERIOD


    def query_minimum_next_election(self, name: str) -> int:
            int bing
            bing = query_last_election(name)
            if (bing) {
            return bing + CLUB_MINIMUM_ELECTION_PERIOD


    def is_president_of(self, name: str, president: str) -> int:
            class election_info info
            info = query_elected_info(name)
            if (info) {
            return holds_position_of(name, info->president, president)


    def is_vice_president_of(self, name: str, vice_president: str) -> int:
            class election_info info
            info = query_elected_info(name)
            if (info) {
            return holds_position_of(name, info->vice_president, vice_president)


    def is_secretary_of(self, name: str, secretary: str) -> int:
            class election_info info
            info = query_elected_info(name)
            if (info) {
            return holds_position_of(name, info->secretary, secretary)


    def is_treasurer_of(self, name: str, treasurer: str) -> int:
            class election_info info
            info = query_elected_info(name)
            if (info) {
            return holds_position_of(name, info->treasurer, treasurer)


    def holds_any_position_of(self, name: str, person: str) -> int:
            class election_info info
            string pos_name
            string per_name
            info = query_elected_info(name)
            if (info) {
            foreach (pos_name, per_name in info->positions) {
            if (per_name == person) {
            return 1


    def holds_position_of(self, name: str, position: str, person: str) -> int:
            class election_info info
            info = query_elected_info(name)
            if (info) {
            position = query_position_name(name, position)
            return info->positions[position] == person


    def create_account(self, name: str, account: str) -> int:
            if (!account) {
            account = CLUB_DEFAULT_ACCOUNT_NAME


    def query_transaction_type_name(self, type: int) -> str:
            switch (type) {
            case CLUB_TRANSACTION_UPKEEP :
            return "upkeep"
            case CLUB_TRANSACTION_DEPOSIT :
            return "player deposit"
            case CLUB_TRANSACTION_INSIGNIA :
            return "insignia"
            case CLUB_TRANSACTION_START_BALANCE :
            return "start balance"
            case CLUB_TRANSACTION_WITHDRAWL :
            return "player withdrawl"
            case CLUB_TRANSACTION_TRANSFER :
            return "player transfer"
            default :
            return "unknown"


    def add_account_allowed_person(self, club_name: str, account: str, person: str) -> int:
            class account_info frog
            frog = query_account_info(club_name, account)
            if (frog &&
            frog->allowed_people.index(person) if person in frog->allowed_people else -1 == -1) {
            frog->allowed_people += [person]
            set_club_changed(club_name)
            return 1


    def remove_account_allowed_person(self, club_name: str, account: str, person: str) -> int:
            class account_info frog
            frog = query_account_info(club_name, account)
            if (frog &&
            frog->allowed_people.index(person) if person in frog->allowed_people else -1 != -1) {
            frog->allowed_people -= [person]
            set_club_changed(club_name)
            return 1


    def add_account_allowed_position(self, club_name: str, account: str, position: str) -> int:
            class account_info frog
            frog = query_account_info(club_name, account)
            if (frog &&
            frog->allowed_positions.index(position) if position in frog->allowed_positions else -1 == -1) {
            frog->allowed_positions += [position]
            set_club_changed(club_name)
            return 1


    def remove_account_allowed_position(self, club_name: str, account: str, position: str) -> int:
            class account_info frog
            frog = query_account_info(club_name, account)
            if (frog &&
            frog->allowed_positions.index(position) if position in frog->allowed_positions else -1 != -1) {
            frog->allowed_positions -= [position]
            set_club_changed(club_name)
            return 1


    def start_election(self, club_name: str) -> int:
            string name
            string pos
            class election_info bing
            string *stuff
            name = normalise_name(club_name)
            if (is_elected_club(name)) {
            if (!_elections[name]) {
            bing = query_elected_info(name)
            _elections[name] = new(class election_data)
            _elections[name]->people = ([ ])
            _elections[name]->nominated = ([ ])
            _elections[name]->voted_for = ([ ])
            _elections[name]->time_of_event = time() + CLUB_NOMINATION_TIME
            _elections[name]->state = CLUB_NOMINATION
            foreach (pos, stuff in bing->positions) {
            _elections[name]->people[pos] = ([ ])
            _elections[name]->nominated[pos] = ([ ])
            _elections[name]->voted_for[pos] = [})


    def finish_nomination(self, club_name: str) -> Any:
            string name
            string position_name
            mapping position_data
            string *data
            string person
            string *bad_positions
            class election_info frog
            name = normalise_name(club_name)
            bad_positions = [})
            if (is_elected_club(name)) {
            frog = query_elected_info(name)
            if (_elections[name] &&
            (_elections[name]->state == CLUB_NOMINATION ||
            _elections[name]->state == CLUB_NOMINATION_SECOND)) {
            foreach (position_name,
            position_data in _elections[name]->nominated) {
            _elections[name]->people[position_name] = ([ ])
            foreach (person, data in position_data) {
            if (is_nomination_accepted(club_name, position_name, person)) {
            _elections[name]->people[position_name][person] = 0


    def complete_election(self, club_name: str) -> int:
            string name
            string position
            mapping people
            string person_name
            int count
            int max_count
            string *max_people
            mapping elected_positions
            int pos
            class election_info frog
            name = normalise_name(club_name)
            if (is_elected_club(name) &&
            _elections[name] &&
            _elections[name]->state = CLUB_ELECTION) {
            elected_positions = ([ ])
            foreach (position, people in _elections[name]->people) {
            max_count = 0
            max_people = [})
            if (sizeof(people) > 1) {
            foreach (person_name, count in people) {
            if (count > max_count) {
            max_count = count
            max_people = [person_name]
            } else if (count == max_count) {
            max_people += [person_name]


    def is_election_in_progress(self, club: str) -> int:
            string name
            name = normalise_name(club)
            if (is_elected_club(name) &&
            _elections[name]) {
            return 1


    def is_nomination_in_progress(self, club: str) -> int:
            string name
            name = normalise_name(club)
            if (is_elected_club(name) &&
            _elections[name] &&
            (_elections[name]->state == CLUB_NOMINATION ||
            _elections[name]->state == CLUB_NOMINATION_SECOND)) {
            return 1


    def is_voting_in_progress(self, club: str) -> int:
            string name
            name = normalise_name(club)
            if (is_elected_club(name) &&
            _elections[name] &&
            _elections[name]->state == CLUB_ELECTION) {
            return 1


    def query_position_members(self, club_name: str, position: str) -> str:
            class election_info frog
            if (is_elected_club(club_name) &&
            is_valid_position(club_name, position)) {
            position = query_position_name(club_name, position)
            frog = query_elected_info(club_name)
            if (frog->positions[position]) {
            return frog->positions[position]


    def query_next_event_time(self, club_name: str) -> int:
            if (is_club(club_name)) {
            club_name = normalise_name(club_name)
            if (_elections[club_name]) {
            return _elections[club_name]->time_of_event


    def query_election_status(self, club_name: str) -> str:
            if (is_elected_club(club_name)) {
            if (is_election_in_progress(club_name)) {
            club_name = normalise_name(club_name)
            return _elections[club_name]->election_status


    def query_announcement(self, club_name: str) -> str:
            class election_info bing
            bing = query_elected_info(club_name)
            if (bing) {
            return bing->announcement


    def query_announcement_time(self, club_name: str) -> int:
            class election_info bing
            bing = query_elected_info(club_name)
            if (bing) {
            return bing->announce_time


    def query_club_board(self, club_name: str) -> int:
            string name
            name = query_club_board_name(club_name)
            return _boards.index(name) if name in _boards else -1 != -1


    def query_club_board_name(self, club_name: str) -> str:
            return CLUB_BOARD_PREFIX + normalise_name(club_name)


    def create_club_board(self, club_name: str) -> int:
            string name
            name = query_club_board_name(club_name)
            if(is_elected_club(club_name) || this_player()->query_director()) {
            if (BOARD_HAND.is_board(name)) {
            return 0


    def remove_club_board(self, club_name: str) -> int:
            string name
            if (query_club_board(club_name)) {
            name = query_club_board_name(club_name)
            BOARD_HAND.delete_board(name)
            _boards -= [name]
            save_main()
            return 1



class Club_elected(MudObject):

    _elections = '([ ])'

    _boards = '[]'
