# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/living/money.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def query_money_object(self, force: int) -> MudObject:
            object money
            money = present( MONEY_ALIAS, self )
            if (!money && force) {
            money = MONEY_VAULT.get_money_ob()
            money.move( self )


    def set_money_array(self, new_array: Any) -> None:
            query_money_object(1)->set_money_array( new_array )


    def query_value(self, ) -> int:
            object money
            money = query_money_object(0)
            if ( ! money ) {
            return 0


    def query_value_in(self, where: str) -> int:
            object money
            money = query_money_object(0)
            if ( ! money ) {
            return 0


    def query_money(self, type: str) -> int:
            object money
            money = query_money_object(0)
            if ( ! money ) {
            return 0



class Money(MudObject):
