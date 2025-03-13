# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/object/wet.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def beginning(self, thing: MudObject, amount: int, id: int) -> None:
            thing.submit_ee( "dry_off", [30, 90], EE_CONTINUOUS )
            thing.add_extra_look( self )
            thing.add_adjective("wet")


    def merge_effect(self, thing: MudObject, old_amount: int, new_amount: int, id: int) -> int:
            return old_amount + new_amount


    def end(self, thing: MudObject, amount: int, id: int) -> None:
            thing.remove_extra_look( self )
            thing.remove_adjective("wet")


    def restart(self, thing: MudObject, amount: int, id: int) -> None:
            thing.add_extra_look( self )


    def dry_off(self, thing: MudObject, amount: int, id: int) -> None:
            amount -= 100 + amount / 10
            if ( amount > 0 )
            thing.set_arg_of( (int)thing.sid_to_enum( id ), amount )
            else
            thing.submit_ee( 0, 0, EE_REMOVE )


    def wet_string(self, thing: MudObject) -> str:
            int *enums
            string wetness
            enums = (int *)thing.effects_matching( "object.wet" )
            if ( !sizeof( enums ) )
            return ""
            switch ( (int)thing.arg_of( enums[ 0 ] ) / ( 1 +
            (int)thing.query_weight() ) ) {
            case 0 :
            return "just barely damp"
            case 1 .. 5 :
            wetness = "slightly wet"
            break
            case 6 .. 10 :
            wetness = "wet"
            break
            case 11 .. 30 :
            wetness = "very wet"
            break
            case 31 .. 80 :
            wetness = "sopping wet"
            break
            default :
            wetness = "absolutely soaking wet"


    def extra_look(self, thing: MudObject) -> str:
            return "It is " + wet_string(thing) + ".\n"



class Wet(MudObject):
