# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/ear_muffs.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._normal_types = ['shout', 'newbie', 'cryer', 'remote-soul']
            self._cre_types = ['cre', 'lord', 'code', 'liaison']
            self._player_format = "{" + implode(_normal_types, "|") + "}"


    def check_earmuffs(self, ) -> int:
            string *on
            string *types
            on = TP.query_property(PLAYER_EARMUFF_PROP)
            if (!on) {
            on = [})


    def do_earmuff_control(self, str: str) -> int:
            string *types
            string *on
            types = _normal_types
            if (TP.query_creator()) {
            types += _cre_types + TP.channel_list()
            } else if (NEWBIEHELPERS_HANDLER.query_can_chat(TP)) {
            types += ({"newbiehelpers"})


    def do_earmuff(self, str: str, onOff: str) -> int:
            string *types, *on, *off
            types = _normal_types
            if (TP.query_creator()) {
            types += _cre_types



class Ear_muffs(MudObject):

    _normal_types = "['shout', 'newbie', 'cryer', 'remote-soul']"

    _cre_types = "['cre', 'lord', 'code', 'liaison']"

    _player_format = '"{" + implode(_normal_types, "|") + "}"'
