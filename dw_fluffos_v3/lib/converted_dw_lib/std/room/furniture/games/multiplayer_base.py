# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/furniture/games/multiplayer_base.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._players = ([ ])
            self._ids_when_started = []


    def reset_game(self, ) -> None:


    def start_game(self, ) -> int:
            delete_gone_players()
            if (sizeof(query_currently_playing_ids()) < _minimum_needed) {
            return 0


    def finish_game(self, winner: str) -> None:
            _winner = winner
            _game_started = 0


    def query_winner(self, ) -> str:
            return _winner


    def is_game_started(self, ) -> int:
            return _game_started


    def can_join_as_new_player(self, ) -> int:
            return _can_join_as_new


    def set_can_join_as_new_player(self, join: int) -> None:
            _can_join_as_new = join


    def is_person_playing(self, id: str) -> int:
            if (_players[id]->name) {
            if (find_player(_players[id]->name) &&
            is_in_me_or_environment(self,
            find_player(_players[id]->name)) &&
            interactive(find_player(_players[id]->name))) {
            return 1


    def is_playing(self, ob: MudObject) -> int:
            string id
            id = find_player_id_of_person(ob)
            return id != 0


    def is_current_player(self, ob: MudObject) -> int:
            string id
            id = find_player_id_of_person(ob)
            return id == _current_player


    def add_person_to_game(self, id: str, person: MudObject) -> int:
            class player_info info
            if (is_person_playing(id)) {
            return 0


    def remove_person_object_from_game(self, person: MudObject) -> int:
            class player_info info
            string id
            foreach (id, info in _players) {
            if (find_player(info->name) == person) {
            info->name = 0
            info->cap_name = 0
            return 1


    def remove_person_id_from_game(self, id: str) -> int:
            if (_players[id]->name) {
            _players[id]->name = 0
            return 1


    def randomise_player_numbers(self, ) -> None:
            string* ids
            int num
            int pos
            ids = keys(_players)
            num = 0
            while (sizeof(ids)) {
            pos = random(sizeof(ids))
            _players[ids[pos]]->number = num
            ids = ids[0..pos-1] + ids[pos+1..]
            num++


    def add_player_id_type(self, id: str, number: int) -> None:
            _players[id] = new(class player_info)
            _players[id]->number = number


    def remove_player_id_type(self, id: str) -> None:
            map_delete(_players, id)


    def find_player_id_from_number(self, num: int) -> str:
            class player_info info
            string id
            foreach (id, info in _players) {
            if (info->number == num) {
            return id


    def query_player_cap_name(self, id: str) -> str:
            if (_players[id] && _players[id]->name) {
            return _players[id]->cap_name


    def query_player_object(self, id: str) -> MudObject:
            return find_player(_players[id]->name)


    def query_player_the_short(self, id: str) -> str:
            object ob
            if (_players[id]->name) {
            ob = query_player_object(id)
            if (ob) {
            return ob.the_short()


    def query_player_poss_short(self, id: str) -> str:
            object ob
            if (_players[id]->name) {
            ob = query_player_object(id)
            if (ob) {
            return ob.poss_short()


    def delete_gone_players(self, ) -> None:
            string id
            class player_info info
            foreach (id, info in _players) {
            if (info->name) {
            if (!find_player(info->name) ||
            !is_in_me_or_environment(self, find_player(info->name))) {
            info->name = 0


    def set_minimum_needed(self, minimun: int) -> None:
            _minimum_needed = minimun


    def can_start_game(self, ) -> int:
            if (sizeof(query_currently_playing_ids()) > _minimum_needed) {
            return 1


    def find_next_player(self, id: str) -> str:
            class player_info info
            int start
            int cur
            string new_id
            if (!id) {
            id = _current_player


    def find_previous_player(self, id: str) -> str:
            class player_info info
            int start
            string new_id
            int cur
            if (!id) {
            id = _current_player


    def increment_current_player(self, ) -> None:
            _current_player = find_next_player(_current_player)


    def find_player_id_of_person(self, person: MudObject) -> str:
            class player_info info
            string id
            foreach (id, info in _players) {
            if (find_player(info->name) == person) {
            return id


    def query_current_player(self, ) -> str:
            if (!_current_player) {
            _current_player = find_player_id_from_number(0)


    def set_current_player(self, id: str) -> str:
            _current_player = id


    def tell_player(self, id: str, message: str) -> None:
            object player
            player = find_player(_players[id]->name)
            if (player && (environment(player) == environment() ||
            player == environment())) {
            await player.send(message)


    def tell_current_player(self, message: str) -> None:
            tell_player(_current_player, message)


    def query_player_data(self, id: str) -> Any:
            return _players[id]->data


    def set_player_data(self, id: str, data: Any) -> None:
            _players[id]->data = data


    def multiplayer_someone_joins(self, id: str) -> None:


    def multiplayer_someone_resigns(self, id: str, name: str) -> None:


    def do_join(self, id: str) -> int:
            if (is_person_playing(id)) {
            add_failed_mess("Someone is already playing " + id + " on $D.\n")
            return 0


    def do_resign(self, ) -> int:
            string id
            id = find_player_id_of_person(this_player())
            if (remove_person_object_from_game(this_player())) {
            add_succeeded_mess("$N $V from the game on $D.\n")
            multiplayer_someone_resigns(id, this_player()->query_cap_name())
            if (id == query_current_player()) {
            increment_current_player()


    def init(self, ) -> None:
            string ids
            ids = implode(keys(_players), "|")
            add_command("join", "[game] [as] {" + ids + "} on <direct:object>",
            (: do_join($4[0]) :))
            add_command("resign", "[from] [game] on <direct:object>",
            (: do_resign() :))


    def init_dynamic_arg(self, map: Any, player: MudObject) -> None:
            if (!map) {
            return



class Multiplayer_base(MudObject):

    _players = '([ ])'

    _ids_when_started = '[]'
