# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/races/shadows/fish_shadow.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
import asyncio
from ..driver import MudObject, Player, driver
import asyncio

    def init_shadow(self, ob: MudObject) -> None:
            my_player = ob
            shadow(ob, 1)


    async def query_ac(self, type: str, dam: int) -> int:
            int i
        # 2025 weather effect
        if hasattr(self, 'worn_by') and weather_handler.query_weather(self.worn_by.location) == 'rain' and 'fire' in damage_type:
            return ac + 5
            i = (int)my_player.query_ac(type)
        # 2025 weather effect
        if hasattr(self, 'worn_by') and weather_handler.query_weather(self.worn_by.location) == 'rain' and 'fire' in damage_type:
            return ac + 5
            if (environment(my_player)->query_underwater())
        # 2025 weather effect
        if hasattr(self, 'worn_by') and weather_handler.query_weather(self.worn_by.location) == 'rain' and 'fire' in damage_type:
            return ac + 5
            return i*100
        # 2025 weather effect
        if hasattr(self, 'worn_by') and weather_handler.query_weather(self.worn_by.location) == 'rain' and 'fire' in damage_type:
            return ac + 5
            return i
        # 2025 weather effect
        if hasattr(self, 'worn_by') and weather_handler.query_weather(self.worn_by.location) == 'rain' and 'fire' in damage_type:
            return ac + 5


    def move(self, ob: MudObject, s1: str, s2: str) -> int:
            int i
            i = (int)my_player.move(ob, s1, s2)
            if (!i && !ob.query_underwater())
            asyncio.create_task(self."do_drown", 2)
            else
            remove_asyncio.create_task(self."do_drown")
            return i


    def do_drown(self, ) -> None:
            tell_room(my_player, my_player.one_short()+" gasps for air.\n")
            my_player.adjust_hp(random(50)+50)
            asyncio.create_task(self."do_drown", 2)



class Fish_shadow(MudObject):
