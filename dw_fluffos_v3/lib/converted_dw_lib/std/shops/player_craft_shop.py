# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/player_craft_shop.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def init(self, ) -> None:
            #ifdef __DISTRIBUTION_LIB__
            room::init()
            #else
            player_housing::init()
            #endif
            player_craft_shop::init()


    def dest_me(self, ) -> None:
            #ifdef __DISTRIBUTION_LIB__
            room::dest_me()
            #else
            player_craft_shop::dest_me()
            #endif
            player_housing::dest_me()


    def set_save_dir(self, dir: str) -> None:
            set_save_file(dir + "_main")
            #ifndef __DISTRIBUTION_LIB__
            ::set_save_dir(dir)
            #endif


    def is_allowed(self, name: str) -> int:
            if (name == "pinkfish") {
            return 1


    def event_exit(self, ob: MudObject, mess: str, to: MudObject) -> None:
            #ifdef __DISTRIBUTION_LIB__
            room::event_exit(ob, mess, to)
            #else
            player_housing::event_exit(ob, mess, to)
            #endif
            player_craft_shop::event_exit(ob, mess, to)


    def ownership_change(self, old_owner: str, new_owner: str) -> int:
            player_craft_shop::ownership_change(old_owner, new_owner)
            return player_housing::ownership_change(old_owner, new_owner)



class Player_craft_shop(Room):
