# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/attached/stat_adjustment.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._stats = ['str', 'dex', 'wis', 'int', 'con']


    def update_adjustments(self, player: MudObject, stat_class: Any) -> None:
            mapping stats
            mapping bing
            string stat
            int i
            int num
            if (sizeof(arg) == 4 && arg->me != player) {
            arg->me = player
            arg->current_adjustments = ([ ])


    def query_indefinite(self, ) -> int:
            class stat_class merge_effect( object player, class stat_class old_arg, mixed new_arg ) {
            int i
            if (pointerp(old_arg)) {
            player.submit_ee(0, 0, EE_REMOVE)
            return old_arg


    def restart(self, player: MudObject, stat_class: Any) -> None:
            update_adjustments(player, edible)


    def quiting(self, player: MudObject, stat_class: Any) -> None:
            womble->obs = [})
            womble->adjs = [})
            update_adjustments(player, womble)


    def end(self, player: MudObject, stat_class: Any) -> None:
            bing->obs = [})
            bing->adjs = [})
            update_adjustments(player, bing)


    def remove_stat_adjustment_ob(self, player: MudObject, ob: MudObject) -> None:
            class stat_class fluff
            int *ids
            int i
            ids = player.effects_matching(query_classification())
            if (sizeof(ids)) {
            fluff = player.arg_of(ids[0])
            for (i = 0; i < sizeof(fluff->obs); i++) {
            if (fluff->obs[i] == ob) {
            fluff->adjs = fluff->adjs[0..i-1] + fluff->adjs[i+1..]
            fluff->obs = fluff->obs[0..i-1] + fluff->obs[i+1..]



class Stat_adjustment(MudObject):

    _stats = "['str', 'dex', 'wis', 'int', 'con']"
