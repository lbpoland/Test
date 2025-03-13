# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/basic/stat_adjustments.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._adjs = ([ ])


    def set_stat_adjustment(self, player: MudObject, adjs: Any) -> None:
            _adjs[player] = adjs
            player.add_effect(STAT_ADJUSTMENT_EFFECT, [self, adjs])


    def remove_stat_adjustment(self, player: MudObject) -> None:
            STAT_ADJUSTMENT_EFFECT.remove_stat_adjustment_ob(player, self)
            map_delete(_adjs, player)


    def remove_all_stat_adjustments(self, ) -> None:
            mapping adj
            object play
            foreach (play, adj in _adjs) {
            STAT_ADJUSTMENT_EFFECT.remove_stat_adjustment_ob(play, self)
            map_delete(_adjs, play)



class Stat_adjustments(MudObject):

    _adjs = '([ ])'
