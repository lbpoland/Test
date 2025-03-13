# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/colo_urs.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._colours = []


    def is_valid_colour(self, name: str) -> int:
            if (_colours.index(name) if name in _colours else -1 != -1) {
            return 1


    def show_allowed_colours(self, ) -> int:
            write("The allowed colour codes are " +
            query_multiple_short(map(_colours, (: lower_case($1) :)), 0, 0, 1) +
            ".\n")
            return 1


    def set_colours(self, inform: int, event_type: str, colour: str, force: int) -> Any:
            mapping my_colours
            string *colour_list
            string *bad
            string tmp
            string name
            colour_list = query_colour_list(inform)
            if (inform == 2) {
            name = CLUB_HANDLER.query_club_name(event_type)
            event_type = "club_" + event_type
            } else {
            name = lower_case(event_type)



class Colo_urs(MudObject):

    _colours = '[]'
