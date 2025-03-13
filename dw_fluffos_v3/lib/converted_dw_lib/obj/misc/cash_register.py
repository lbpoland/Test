# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/cash_register.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def long(self, word: str, dark: int) -> str:
            int i
            string ret, *coins
            object cash
            ret = query_long()
            cash = present( MONEY_ALIAS, self )
            if ( !cash )
            return ret +"There is no money in the register.\n"
            coins = (string *)cash.half_short( 1 )
            if ( !sizeof( coins ) )
            return ret +"There is no money in the register.\n"
            ret += "The register contains:\n"
            for ( i = 0; i < sizeof( coins ); i++ )
            ret += "      "+ coins[ i ] +"\n"
            return ret


    def test_add(self, thing: MudObject, flag: int) -> int:
            if ( !thing.id( MONEY_ALIAS ) )
            return 0
            if ( shop )
            shop.save_register()
            return 1


    def test_remove(self, thing: MudObject, flag: int) -> int:
            if ( shop )
            shop.save_register()
            return 1



class Cash_register(Inventory):
