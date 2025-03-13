# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/furniture/inherit/furniture_base.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._allowed_positions = []


    def __init__(self):
            self._allowed_positions = []
            self.set_max_cond(100000)
            self.set_cond(100000)


    def query_furniture(self, ) -> int:
            return 1


    def set_allowed_positions(self, positions: str) -> None:
            _allowed_positions = positions


    def remove_allowed_positions(self, positions: str) -> None:
            _allowed_positions -= positions


    def set_allowed_room_verbs(self, allowed: Any) -> None:
            _allowed_room_verbs = allowed


    def query_position_string(self, position_type: str) -> str:
            if(_allowed_positions.index(position_type) if position_type in _allowed_positions else -1 != -1) {
            return one_short()


    def set_bonded(self, person: str) -> None:
            _bonded = person


    def query_bonded(self, ) -> str:
            return _bonded


    def query_owner(self, ) -> str:
            return _bonded


    def is_allowed_to_mess(self, player: MudObject) -> int:
            mixed *stuff
            string occupier
            if(environment() && !function_exists("query_owner", environment()))
            return 1
            if(player.query_creator())
            return 1
            if(player.query_caster())
            player = find_player(player.query_caster())
            if(player.query_owner())
            player = player.query_owner()
            if (player && player.query_name() == _bonded)
            return 1
            stuff = self.query_property("dropped")
            if(player && sizeof(stuff) && stuff[0] == player.query_name())
            return 1
            if(player && environment()) {
            if(environment()->test_occupier(player.query_name()))
            return 1
            if(environment()->query_owner() == "For Sale" ||
            environment()->query_owner() == "Under Offer")
            return 1
            occupier = HOUSING.query_owner(base_name(environment()))
            if(pk_check(player, occupier, 1))
            return 0


    def move_check(self, dest: MudObject) -> int:
            if (living(dest)) {
            if (!is_allowed_to_mess(dest)) {
            return 0


    def query_placement_verb(self, ) -> str:
            return query_property(PLACEMENT_CURRENT_ROOM_VERB)


    def query_placement_other(self, ) -> str:
            return query_property(PLACEMENT_CURRENT_ROOM_OTHER)


    def query_placement_position(self, ) -> str:
            return query_property(PLACEMENT_CURRENT_ROOM_POSITION)


    def query_placement_immovable(self, ) -> int:
            return query_property(PLACEMENT_IMMOVABLE)


    def is_placed(self, ) -> int:
            return query_placement_position() &&
            stringp(query_placement_verb()) &&
            stringp(query_placement_other())


    def set_placement_verb(self, verb: str) -> None:
            add_property(PLACEMENT_CURRENT_ROOM_VERB, verb)


    def set_placement_other(self, other: str) -> None:
            add_property(PLACEMENT_CURRENT_ROOM_OTHER, other)


    def set_placement_position(self, position: str) -> None:
            add_property(PLACEMENT_CURRENT_ROOM_POSITION, position)


    def set_placement_immovable(self, ) -> int:
            return query_property(PLACEMENT_IMMOVABLE)



class Furniture_base(MudObject):

    _allowed_positions = '[]'
