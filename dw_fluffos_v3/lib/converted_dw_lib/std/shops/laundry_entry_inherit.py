# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/laundry_entry_inherit.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def set_laundry_exit(self, direc: str, dest: Any, type: str) -> None:
            laundry_room = dest
            add_exit(direc, dest, type)
            modify_exit( direc, ["function", "check_customer"] )
            modify_exit( direc, ["closed", 1}))


    def check_customer(self, verb: str, thing: MudObject, special: str) -> int:
            string owner
            object vroom
            if(!laundryowner || environment(laundryowner) != self)
            return notify_fail("Since the owner of this laundry is missing "
            "you think twice before entering the laundry.\n")
            if( !interactive(thing) )
            return 0
            owner = (string)thing.query_name()
            if ( !( vroom = find_object( laundry_room ) ) )  {
            laundry_room.load_me()
            vroom = find_object( laundry_room )


    def player_quitting(self, who: MudObject, env: MudObject) -> None:



class Laundry_entry_inherit(Room):
