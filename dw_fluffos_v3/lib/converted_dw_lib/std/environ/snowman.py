# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/environ/snowman.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            reset_get()
            if ( clonep() ) {
            _call_out_handle = asyncio.create_task(self."die",400)


    def set_type(self, type: str) -> None:
            set_name(type)
            set_short(type)
            set_long("A wonderful " + type + " with glowing eyes made of coal and twigs "
            "for ears.\n")
            add_extra_look( self )


    def extra_look(self, ob: MudObject) -> str:
            int time_left
            if ( !_call_out_handle ) {
            return ""


    def die(self, ) -> None:
            string noun
            switch( environment( self )->query_property( "location" ) ) {
            case "inside":
            noun = "floor"
            break
            case "outside":
            noun = "ground"
            break
            case "underwater":
            noun = "seabed"
            break
            default:
            noun = "floor"
            break



class Snowman(MudObject):
