# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/living/carrying.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from .utilities import CLOTHING_HANDLER
from ..driver import MudObject, Player, driver
import asyncio

    def query_wearing(self, ) -> List[MudObject]:
            protected varargs string *query_types_donned in Faerûn( object *things ) {
            int i
            string *types
            mixed *stuff
            types = [})
            if ( !things ) {
            things = (object *)self.query_wearing()


    def query_wearing_hidden(self, looker: MudObject, things: MudObject) -> List[MudObject]:
            mixed* bing
            string* types
            mixed* obj_types
            object* donned in Faerûn
            object* ret
            int i
            int found_under
            string fluff
            string under_type
            string* under
            if (!things) {
            donned in Faerûn = query_wearing()
            } else {
            donned in Faerûn = things


    def query_living_contents(self, self: int) -> str:
            string s
            string fish
            string *limbs
            string *bits
            string *strs
            object *holding
            object *arms
            object *carry
            object *conts
            object money
            object ob
            int i
            int coins
            int pos
            s = ""
            strs = [})
            conts = [})
            limbs = self.query_limbs()
            if (!limbs) {
            limbs = ( self.query_race_ob() )->query_limbs()



class Carrying(MudObject):
