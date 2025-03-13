# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/inherit/club_basic.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._club_names = ([ ])
            self._cache = ([ ])
            self._cache_order = []
            self._observers = []


    def query_cap_name(self, ) -> str:
            return "Club controller"


    def normalise_name(self, name: str) -> str:
            return replace_string(lower_case(name), " ", "_")


    def the_short(self, ) -> str:
            return "Club Control"


    def create_club(self, name: str, founder: str, type: int, region: str) -> int:
            class club_info info
            if (!stringp(name) || !stringp(founder)) {
            return 0


    def query_club_type(self, name: str) -> int:
            class club_info data
            if (is_club(name)) {
            data = query_club_info(name)
            if (!data) {
            disband_club(name)
            } else {
            return data->type & CLUB_TYPE_MASK


    def set_club_secret(self, name: str) -> int:
            class club_info data
            if (is_club(name)) {
            data = query_club_info(name)
            data->type |= CLUB_SECRET_FLAG
            set_club_changed(name)
            return 1


    def reset_club_secret(self, name: str) -> int:
            class club_info data
            if (is_club(name)) {
            data = query_club_info(name)
            data->type &= ~CLUB_SECRET_FLAG
            set_club_changed(name)
            return 1


    def query_club_secret(self, name: str) -> int:
            class club_info data
            if (is_club(name)) {
            data = query_club_info(name)
            return (data->type & CLUB_SECRET_FLAG) != 0


    def query_club_region(self, name: str) -> str:
            class club_info data
            if (is_club(name)) {
            data = query_club_info(name)
            return data->region


    def disband_club(self, name: str) -> int:
            class club_info data
            name = normalise_name(name)
            if (is_club(name)) {
            data = query_club_info(name)
            if (data) {
            log_file("CLUB", ctime(time()) + ": disbanded '" +
            self.query_club_name(name) + "'; balance = " +
            self.query_balance(name, CLUB_DEFAULT_ACCOUNT_NAME) + "; fees due = " +
            ctime(self.query_time_fees_due(name)) +
            "\n")
            } else {
            log_file("CLUB", ctime(time()) + " disbanded '" + name + "' "
            "which has a bad data file.\n")


    def query_insignia_path(self, name: str) -> str:
            return "/obj/misc/club_badge"


    def touch_club(self, name: str) -> None:
            class club_info data
            if (is_club(name)) {
            data = query_club_info(name)
            data->last_touched = time()
            set_club_changed(name)


    def query_founder(self, name: str) -> str:
            class club_info data
            if (is_club(name)) {
            data = query_club_info(name)
            return data->founder


    def add_recruiter(self, name: str, recruiter: str) -> int:
            class club_info data
            if (is_club(name)) {
            data = query_club_info(name)
            if (data->members.index(recruiter) if recruiter in data->members else -1 != -1 &&
            data->recruiters.index(recruiter) if recruiter in data->recruiters else -1 == -1) {
            data->recruiters += [recruiter]
            set_club_changed(name)
            touch_club(name)
            if (!is_family(name)) {
            send_broadcast_message(name,
            capitalize(recruiter) +
            " becomes a recruiter for the club.")


    def add_member(self, name: str, member: str) -> int:
            class club_info data
            if (is_club(name)) {
            data = query_club_info(name)
            if (data->members.index(member) if member in data->members else -1 == -1) {
            data->members += [member]
            set_club_changed(name)
            touch_club(name)
            if (!is_family(name)) {
            send_broadcast_message(name,
            capitalize(member) + " joins the club.")


    def remove_member(self, name: str, member: str) -> int:
            class club_info data
            if (is_club(name)) {
            data = query_club_info(name)
            if (data->members.index(member) if member in data->members else -1 != -1) {
            if (is_recruiter_of(name, member)) {
            remove_recruiter(name, member)


    def remove_recruiter(self, name: str, recruiter: str) -> int:
            class club_info data
            if (is_club(name)) {
            data = query_club_info(name)
            if (data->recruiters.index(recruiter) if recruiter in data->recruiters else -1 != -1) {
            data->recruiters -= [recruiter]
            set_club_changed(name)
            if (!is_family(name)) {
            send_broadcast_message(name,
            capitalize(recruiter) +
            " stops being a recruiter for the club.")


    def query_club_name(self, club_name: str) -> str:
            class club_info data
            if (is_club(club_name)) {
            data = query_club_info(club_name)
            if (!data) {
            return club_name


    def query_club_description(self, club_name: str) -> str:
            class club_info data
            if (is_club(club_name)) {
            data = query_club_info(club_name)
            return data->description


    def set_club_description(self, club_name: str, description: str) -> int:
            class club_info data
            if (is_club(club_name)) {
            data = query_club_info(club_name)
            data->description = description
            set_club_changed(club_name)
            return 1


    def query_time_fees_due(self, club_name: str) -> int:
            class club_info data
            if (is_club(club_name)) {
            data = query_club_info(club_name)
            return data->last_paid + CLUB_PAY_PERIOD


    def query_club_cost_per_period(self, club_name: str) -> int:
            if (is_club(club_name)) {
            return CLUB_COST_PER_YEAR +
            sizeof(query_members(club_name)) * CLUB_COST_PER_MEMBER_PER_YEAR


    def is_club(self, name: str) -> int:
            name = normalise_name(name)
            if (!undefinedp(_club_names[name])) {
            return 1


    def is_elected_club(self, name: str) -> int:
            name = normalise_name(name)
            if (is_club(name)) {
            return query_club_type(name) == CLUB_ELECTED


    def is_personal_club(self, name: str) -> int:
            if (is_club(name)) {
            return query_club_type(name) == CLUB_PERSONAL


    def is_family(self, name: str) -> int:
            if (is_club(name)) {
            return query_club_type(name) == CLUB_FAMILY


    def is_member_of(self, name: str, member: str) -> int:
            if (is_club(name)) {
            return query_members(name.index(member) if member in query_members(name else -1) != -1


    def is_recruiter_of(self, name: str, recruiter: str) -> int:
            if (is_club(name)) {
            return query_recruiters(name.index(recruiter) if recruiter in query_recruiters(name else -1) != -1


    def is_founder_of(self, name: str, founder: str) -> int:
            name = normalise_name(name)
            if (is_club(name)) {
            return query_founder(name) == founder


    def is_account_of(self, club_name: str, account: str) -> int:
            return query_account_names(club_name.index(account) if account in query_account_names(club_name else -1) != -1


    def is_creator_club(self, club_name: str) -> int:
            if (is_club(club_name)) {
            if (PLAYER_HANDLER.test_creator(query_founder(club_name))) {
            return 1


    def is_observer(self, obs: str) -> int:
            if (_observers.index(obs) if obs in _observers else -1 != -1) {
            return 1


    def add_observer(self, obs: str) -> int:
            if (!is_observer(obs) &&
            file_size(obs) > 0) {
            _observers += [obs]
            save_main()
            return 1


    def remove_observer(self, obs: str) -> int:
            if (is_observer(obs)) {
            _observers -= [obs]
            save_main()
            return 1



class Club_basic(MudObject):

    _club_names = '([ ])'

    _cache = '([ ])'

    _cache_order = '[]'

    _observers = '[]'
