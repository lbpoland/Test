# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/inherit/club_owned_room.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def query_owner(self, ) -> str:
            return _club_controller.query_owner_of(_club_owned_id)


    def set_club_controller(self, club_controller: str) -> None:
            _club_controller = club_controller


    def query_club_controller(self, ) -> str:
            return _club_controller


    def set_owned_id(self, id: str) -> None:
            _club_owned_id = id


    def query_owned_id(self, ) -> str:
            return _club_owned_id



class Club_owned_room(MudObject):
