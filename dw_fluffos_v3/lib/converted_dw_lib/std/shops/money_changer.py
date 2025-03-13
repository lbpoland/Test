# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shops/money_changer.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def init(self, ) -> None:
            ::init()
            add_command("change", "<string> {into|to} <string>",
            (: change($4[0], $4[2]) :) )


    def change(self, words: str, type: str) -> int:
            int val_index
            int value
            int value_type
            int value_unit
            int value_change
            int i
            string place
            mixed money
            object changed
            object *monies
            mixed *change
            mixed *values
            place = query_property( "place" )
            if ( !place || ( place == "" ) ) {
            place = "default"



class Money_changer(MudObject):
