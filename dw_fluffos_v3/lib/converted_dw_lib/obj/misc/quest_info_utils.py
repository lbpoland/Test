# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/quest_info_utils.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def set_quest_name(self, quest_name: str) -> None:
            {
            _quest_name = quest_name


    def set_quest_param(self, player: Any, key: str, value: Any) -> None:
            {
            mixed info
            if (!stringp(player))
            player = player.query_name()
            info = LIBRARY.query_player_quest_info(player, _quest_name)
            if (!mapp(info))
            info = ([ ])
            info[key] = value
            LIBRARY.set_player_quest_info(player, _quest_name, info)


    def query_quest_param(self, player: Any, key: str) -> Any:
            {
            mixed info
            if (!stringp(player))
            player = player.query_name()
            info = LIBRARY.query_player_quest_info(player, _quest_name)
            if (!mapp(info))
            return 0
            return info[key]


    def clear_quest_info(self, player: Any) -> None:
            {
            if (!stringp(player))
            player = player.query_name()
            LIBRARY.set_player_quest_info(player, _quest_name, 0)



class Quest_info_utils(MudObject):
