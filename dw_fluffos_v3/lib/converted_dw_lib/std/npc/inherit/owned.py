# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/npc/inherit/owned.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def set_owner(self, owner: Any) -> MudObject:
            if( stringp(owner) )
            _owner = owner
            if( objectp(owner) && living(owner) ){
            if( userp(owner) )
            _owner = owner.query_name()
            else
            _owner = owner


    def query_owner(self, ) -> MudObject:
            if( stringp(_owner) )
            return find_player(_owner)
            else
            return _owner


    def query_owner_pk_check(self, ) -> MudObject:
            return query_owner()



class Owned(MudObject):
