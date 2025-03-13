# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/room/magic_octogram.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def beginning(self, thing: MudObject, number: int, id: int) -> None:
            tell_room( thing, "An octogram begins to glow "+
            (string)thing.query_property( "here" ) +".\n" )
            thing.submit_ee( 0, number, EE_REMOVE )
            thing.add_extra_look( self )
            thing->add_item( "octogram", "The octogram glows in eldritch fashion, "
            "and that has nothing to do with being oblong." )


    def merge_effect(self, thing: MudObject, old_arg: int, new_arg: int, id: int) -> int:
            tell_room( thing, "The octogram pulses for a moment.\n" )
            thing.submit_ee( 0, new_arg + (int)thing.expected_tt(), EE_REMOVE )
            return old_arg + new_arg


    def end(self, thing: MudObject, number: int, id: int) -> None:
            if ( !sizeof( filter_array( previous_object( -1 ),
            (: $1.query_magic_spell() :) ) ) )
            tell_room( thing, "The octogram flickers and disappears.\n" )
            thing.remove_extra_look( self )


    def extra_look(self, thing: MudObject) -> str:
            return "An octogram "+ (string)thing.query_property( "here" ) +
            " glows in eldritch fashion.\n"



class Magic_octogram(MudObject):
