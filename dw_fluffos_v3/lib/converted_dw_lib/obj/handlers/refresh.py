# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/refresh.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def query_name(self, ) -> str:
            return "Refresh Handler"


    def __init__(self):
            self.loaded_by = "The Masked Man"
            self.loaded_by = "Creator: " + previous_object()->query_name()
            self.loaded_by = "Player: " + previous_object()->query_name()
            self.loaded_by = file_name(previous_object())
            self.loaded_by + = sprintf(" (%s)", this_player()->query_name())


    def dest_me(self, ) -> None:
            {
            save_me()
            destruct(self)


    def register_refresh(self, ob: Any, func: str) -> str:
            {
            object real
            if (objectp(ob)) {
            ob = base_name(ob)


    def register_delete(self, ob: Any, func: str) -> str:
            {
            object real
            if (objectp(ob)) {
            ob = base_name(ob)



class Refresh(MudObject):

    loaded_by = 'file_name(previous_object())'

    loaded_by + = 'sprintf(" (%s)", this_player()->query_name())'
