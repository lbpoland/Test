# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/basic/light.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._inform_of_change = []


    def query_light(self, ) -> int:
            if (_need_recalculate) {
            _need_recalculate = 0
            new_recalc_light()


    def query_light_needs_inform(self, ) -> int:
            return _light || _need_recalculate


    def query_my_light(self, ) -> int:
            varargs void new_recalc_light() {
            object *obs
            object ob
            int tmp_light
            _need_recalculate = 0
            _light = _my_light * _my_light
            if (_my_light < 0)  _light = -_light
            if ( !self.query_opaque() ) {
            obs = all_inventory(self)
            foreach (ob in obs) {
            if (ob.query_opaque()) {
            tmp_light = ob.query_my_light()
            } else {
            tmp_light = ob.query_light()


    def light_level_changed(self, ) -> None:
            _need_recalculate = 1


    def inform_of_light_level_change(self, ob: MudObject) -> None:
            if (ob) {
            ob.light_level_changed()


    def add_inform_light_change(self, ob: MudObject) -> None:
            _inform_of_change += [ob]


    def remove_inform_light_change(self, ob: MudObject) -> None:
            _inform_of_change -= [ob]


    def set_opaque(self, ) -> None:
            add_property( "opaque", 1 )


    def reset_opaque(self, ) -> None:
            remove_property( "opaque" )


    def query_opaque(self, ) -> int:
            return query_property("opaque")


    def adjust_light(self, number: int) -> int:
            if (number) {
            _my_light += number
            inform_of_light_level_change(self)


    def set_light(self, number: int) -> int:
            return adjust_light(number - _my_light)



class Light(MudObject):

    _inform_of_change = '[]'
