# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/basic/hide_invis.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._hide_invis = ([])


    def add_hide_invis(self, type: str, who: MudObject, see: Any, gone: str) -> int:
            if( _hide_invis[type] ) {
            return 0


    def perception_check(self, thing: MudObject) -> int:
            int perception
            perception = thing.query_skill_bonus( SKILL )
            if( !environment( thing ) || !perception )
            return perception
            switch( thing.check_dark( (int)environment( thing )->query_light() ) ) {
            case -2:
            case 2:
            perception /= 4
            break
            case -1:
            case 1:
            perception /= 2
            break
            default:
            break


    def query_visible(self, thing: MudObject) -> int:
            int i
            string *types
            mixed see
            if( thing == self ) {
            return 1


    def hide_invis_string(self, ) -> str:
            int i
            string list
            string *types
            types = keys( _hide_invis )
            if( !sizeof( types ) ) {
            return ""



class Hide_invis(MudObject):

    _hide_invis = '([])'
