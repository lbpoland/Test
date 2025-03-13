# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/position_base.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def query_position_command(self, ) -> int:
            return 1


    def query_up_down(self, ) -> str:
            return up_down


    def query_position(self, ) -> str:
            return position


    def query_position_type(self, ) -> str:
            return position_type


    def setup_position(self, pos: str, up: str, type: str) -> None:
            position = pos
            up_down = up
            position_type = type


    def position(self, person: MudObject, silent: int) -> int:
            string pos_type
            if (person.query_position() == position_type) {
            if (person == this_player()) {
            add_failed_mess("You are already "+position_type+".\n")


    def position_floor(self, person: MudObject, silent: int) -> int:
            if (!environment(person) ||
            !environment(person)->is_allowed_position(position_type)) {
            if (person == this_player()) {
            add_failed_mess("You cannot " + position +  " " + up_down +
            " here.\n")


    def position_object(self, obs: MudObject, pos_type: str, person: MudObject) -> int:
            int i
            int mult
            string rabbit
            string *pos_strings
            if (!environment(person) ||
            !environment(person)->is_allowed_position(position_type)) {
            if (person == this_player()) {
            add_failed_mess("You cannot " + position +  " " + up_down +
            " here.\n")



class Position_base(MudObject):
