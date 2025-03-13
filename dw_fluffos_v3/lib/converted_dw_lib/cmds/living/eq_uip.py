# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/living/eq_uip.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, ) -> int:
            int no_limbs
            string stuff
            object thing
            object *equipped
            object *things
            equipped = [})
            things = all_inventory( TP ) - TP.query_wearing() -
            TP.query_holding()
            foreach ( thing in things ) {
            no_limbs = thing.query_no_limbs()
            if ( no_limbs > TP.query_free_limbs() ) {
            continue



class Eq_uip(MudObject):
