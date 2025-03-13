# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/living/draw.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, weapon_str: str, : MudObject, hand_str: str) -> int:
            object scabbard, * weapons, weapon
            class obj_match match
            string *limbs
            string *hands
            int *what_in
            int targeted, result
            int hand
            match = new( class obj_match )
            targeted = scabbards ? 1 : 0
            debug_printf( "targeted = %d\nscabbards = %O\n", targeted, scabbards )
            if( !scabbards ) {
            scabbards = filter( all_inventory( this_player() ),
            (: $1.query_scabbard() :) )
            if( !sizeof(scabbards) ) {
            add_failed_mess( "Can't find any scabbards in your inventory.\n" )
            return 0



class Draw(MudObject):
