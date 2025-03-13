# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/basic/holdable.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._no_limbs = 1


    def query_static_auto_load(self, ) -> Any:
            return ([ "no limbs" : _no_limbs
            ])


    def init_static_arg(self, arg: Any) -> None:
            if (!arg) {
            return


    def query_dynamic_auto_load(self, ) -> Any:
            return ([ "limb"       : (_holder ? _my_limb : -1),
            "limbs used" : (_holder ?
            sizeof(find_member(self,
            _holder.query_holding())) : 0)
            ])


    def init_dynamic_arg(self, arg: Any, new_arg: Any) -> None:
            if (!arg) {
            return


    def held_this_item(self, held: int, holder: MudObject, arg: Any) -> int:
            return 1


    def set_holder(self, ob: MudObject, limb: int) -> int:
            if (ob && environment() != ob) {
            return 0


    def set_no_limbs(self, num: int) -> None:
            if (num < 0) {
            return


    def move(self, ob: Any) -> int:
            if ( ob != _holder && _holder ) {
            if ( !sizeof( _holder.set_unhold( self ) ) ) {
            return MOVE_NO_UNHOLD


    def dest_me(self, ) -> None:
            if (_holder) {
            _holder.set_unhold(self)



class Holdable(MudObject):

    _no_limbs = 1
