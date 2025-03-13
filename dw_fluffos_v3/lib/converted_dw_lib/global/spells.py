# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/global/spells.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._spell_effects = []


    def queue_commands(self, {: Any) -> int:
            int add_spell_effect(int no_rnds, string type, string name, object callee,
            string func, mixed params) {
            int i,j
            if (strsrch(file_name(self),"global")==-1)
            tell_object(find_living("olorin"),
            sprintf("add_spell_effect in %s\n",
            file_name(self)))
            if ((i=_spell_effects.index(type) if type in _spell_effects else -1) != -1)
            if ((j=_spell_effects[i+1].index(name) if name in _spell_effects[i+1] else -1) == -1)
            _spell_effects[i+1] += [name, [no_rnds, callee, func, params]]
            else
            _spell_effects[i+1][j+1] = [no_rnds, callee, func, params]
            else
            _spell_effects += [type, [name, [no_rnds, callee, func, params]]]


    def remove_spell_effect(self, name: str) -> int:
            int i, j
            if (strsrch(file_name(self),"global")==-1)
            tell_object(find_living("olorin"),
            sprintf("remove_spell_effect in %s\n",
            file_name(self)))
            for (i=0;i<sizeof(_spell_effects);i+=2)
            if ((j=_spell_effects[i+1].index(name) if name in _spell_effects[i+1] else -1) != -1) {
            _spell_effects[i+1] = delete(_spell_effects[i+1], j, 2)
            if (!sizeof(_spell_effects[i+1])) {
            _spell_effects = delete(_spell_effects, i, 2)
            i -= 2


    def query_spell_effect(self, name: str) -> Any:
            int i
            if (strsrch(file_name(self),"global")==-1)
            tell_object(find_living("olorin"),
            sprintf("query_spell_effect in %s\n",
            file_name(self)))
            if ((i=_spell_effects.index(name) if name in _spell_effects else -1) == -1)
            return 0
            if (sizeof(_spell_effects[i+1]))
            return _spell_effects[i..i]+_spell_effects[0..1]
            return 0


    def do_spell_effects(self, attacker: MudObject) -> int:
            int i, j
            self.remove_property("casting")
            for (i=0;i<sizeof(_spell_effects);i+=2)
            for (j=0;j<sizeof(_spell_effects[i+1]);j+=2) {
            asyncio.create_task(self."do_call_out_effect", 1, [_spell_effects[i+1][j+1], attacker])
            _spell_effects[i+1][j+1][SP_NO_RNDS]--
            if ( !_spell_effects[i+1][j+1][SP_NO_RNDS] || !_spell_effects[i+1][j+1][SP_OBJECT]) {
            _spell_effects[i+1] = delete(_spell_effects[i+1], j, 2)
            j -= 2
            if (!sizeof(_spell_effects[i+1])) {
            _spell_effects = delete(_spell_effects, i, 2)
            i -= 2
            break


    def do_call_out_effect(self, params: Any) -> None:
            if (params[0][SP_OBJECT])
            call_other(params[0][SP_OBJECT],
            params[0][SP_FUNC],
            params[1],
            params[0][SP_PARAM],
            params[0][SP_NO_RNDS])



class Spells(MudObject):

    _spell_effects = '[]'
