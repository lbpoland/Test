# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/simul_efun/pk_check.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def pk_check(self, thing1: Any, thing2: Any, off_line: int) -> int:
            int pk1
            int pk2
            object ob
            if(objectp(thing1) && objectp(thing2) &&
            interactive(thing1) && interactive(thing2) &&
            sizeof( filter( [thing1, thing2],
            (: $1.query_creator() ||
            $1.query_property("test character") :) )) == 1) {
            self->debug_printf( "PK check between %s and %s failed!\n",
            thing1.query_name(),
            thing2.query_name() )
            return 1


    def pk_assist(self, assister: Any, assistee: Any, off_line: int) -> int:
            object ob
            if(objectp(assistee) && !interactive(assistee) &&
            assistee.query_owner_pk_check()) {
            assistee = assistee.query_owner_pk_check()



class Pk_check(MudObject):
