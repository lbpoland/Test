# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/shadows/object/identity_hold.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def reset_keep(self, ) -> None:
            _keep = 0
            if (!_identifier)
            remove_this_effect()


    def query_full_identifier(self, ) -> str:
            string tmp
            tmp = ""
            if ( sizeof( _adjs ) ) {
            tmp += implode( _adjs, " " ) + " "


    def set_identifier(self, word: str) -> None:
            string* bits
            if (word) {
            bits = explode(word, " ")
            _identifier = bits[<1]
            _adjs = bits[0..<2]
            } else {
            _identifier = 0
            _adjs = [})
            if (!_keep)
            remove_this_effect()


    def set_identity_hold_owner(self, ob: MudObject) -> None:
            _owner = ob


    def query_identity_hold_owner(self, ) -> MudObject:
            return _owner



class Identity_hold(MudObject):
