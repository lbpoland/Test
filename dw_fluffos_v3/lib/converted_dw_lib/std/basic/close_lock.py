# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/basic/close_lock.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from .utilities import CLOTHING_HANDLER
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._difficulty = 5
            self._pick_skill = "covert.lockpick.doors"


    def set_open(self, ) -> None:
            if (!_closed)
            return
            _closed = 0
            _locked = 0
            if (environment()) {
            event( [environment(), TO,], "open", TP)
            } else if (TO.query_my_room()) {
            event( [TO.query_my_room(), TO,], "open", TP)


    def set_closed(self, ) -> None:
            if (_closed)
            return
            _closed = 1
            if (environment()) {
            event( [environment(), TO,], "close", TP)
            } else if (TO.query_my_room()) {
            event( [TO.query_my_room(), TO,], "close", TP)


    def query_closed(self, ) -> int:
            return _closed


    def query_open(self, ) -> int:
            return !_closed


    def set_locked(self, ) -> None:
            if (!_closed)
            return
            if (_locked)
            return
            _locked = 1
            if (environment()) {
            event( [environment(), TO,], "lock", TP)
            } else if (TO.query_my_room()) {
            event( [TO.query_my_room(), TO,], "lock", TP)


    def set_unlocked(self, ) -> None:
            if (!_locked)
            return
            _locked = 0
            if (environment()) {
            event( [environment(), TO,], "unlock", TP)
            } else if (TO.query_my_room()) {
            event( [TO.query_my_room(), TO,], "unlock", TP)


    def query_locked(self, ) -> int:
            return _locked


    def query_unlocked(self, ) -> int:
            return !_locked


    def set_key(self, val: Any) -> None:
            if (!stringp(val) && !functionp(val))
            return
            _key = val


    def query_key(self, ) -> str:
            if (stringp(_key))
            return _key
            if (functionp(_key))
            return evaluate(_key)
            return 0


    def set_pick_skill(self, str: str) -> None:
            _pick_skill = str


    def query_pick_skill(self, ) -> str:
            return _pick_skill


    def set_difficulty(self, i: int) -> None:
            _difficulty = i


    def query_difficulty(self, ) -> int:
            return _difficulty


    def set_stuck(self, i: int) -> None:
            _stuck = i


    def query_stuck(self, ) -> int:
            return _stuck


    def set_transparent(self, ) -> None:
            _trans = C_TRANS


    def reset_transparent(self, ) -> None:
            _trans = 0


    def query_transparent(self, ) -> int:
            return _trans


    def set_open_trap(self, ob: MudObject, func: str) -> None:
            _trap_open_func =  func
            _trap_open_ob = ob


    def query_open_trap_func(self, ) -> str:
            return _trap_open_func


    def query_open_trap_ob(self, ) -> MudObject:
            return _trap_open_ob


    def set_lock_trap(self, ob: MudObject, func: str) -> None:
            _trap_lock_func = func
            _trap_lock_ob = ob


    def query_lock_trap_func(self, ) -> str:
            return _trap_lock_func


    def query_lock_trap_ob(self, ) -> MudObject:
            return _trap_lock_ob


    def query_closed_locked_status(self, ) -> int:
            if (_closed && _locked) {
            return CLOSED_LOCKED


    def add_close_lock_commands(self, player: MudObject) -> None:
            if(!player)
            return
            player->add_command("open", TO,
            "<direct:object:me-here>",
            (: do_open() :) )
            player->add_command("close", TO,
            "<direct:object:me-here>",
            (: do_close() :) )
            if (TO.query_key()) {
            player->add_command("lock", TO,
            "<direct:object:me-here>",
            (: do_lock(0) :) )
            player->add_command("lock", TO,
            "<direct:object:me-here> with <indirect:object:me>",
            (: do_lock($1) :) )
            player->add_command("unlock", TO,
            "<direct:object:me-here>",
            (: do_unlock(0) :) )
            player->add_command("unlock", TO,
            "<direct:object:me-here> with <indirect:object:me>",
            (: do_unlock($1) :) )


    def init(self, ) -> None:
            add_close_lock_commands(this_player())


    def short_status(self, ) -> str:
            return ""


    def long_status(self, ) -> str:
            if (TO.query_stuck())
            return ""
            switch (query_closed_locked_status()) {
            case CLOSED_LOCKED:
            return "It is closed and locked.\n"
            case CLOSED:
            return "It is closed.\n"
            default:
            return "It is open.\n"


    def check_stealth(self, ) -> int:
            mapping hide_invis
            int hiding, sneaking, difficulty, light, my_light, items_blocking
            hide_invis = (mapping) TP.query_hide_invis()
            hiding = undefinedp(hide_invis["hiding"]) ? 0 : 1
            sneaking = TP.query_sneak_level() ? 1 : 0
            if (!hiding && !sneaking)
            return STEALTH_NONE
            my_light = TP.query_light()
            light = environment(TP)->query_light()
            difficulty = light + (4 * my_light) / (light + 1)
            items_blocking = sizeof(CLOTHING_HANDLER.query_items_blocking(TO, TP))
            if (items_blocking) {
            difficulty += 50 * items_blocking


    def do_unlock(self, keys: MudObject) -> int:
            object *gkeys = [})
            string key = TO.query_key()
            int inv = 0
            if (!_locked) {
            TP->add_failed_mess(TO,
            "$D $V$0=isn't,aren't$V$ locked.\n",
            [}) )
            return 0


    def do_lock(self, keys: MudObject) -> int:
            object *gkeys = [})
            string key = TO.query_key()
            int inv = 0
            if (_locked) {
            TP->add_failed_mess(TO,
            "$D $V$0=is,are$V$ already locked.\n",
            [}) )
            return 0


    def pick_lock(self, player: MudObject) -> int:
            if (_trap_lock_ob
            && !_trap_lock_ob, _trap_lock_func.pick(TO, player)) {
            return 0


    def pick_unlock(self, player: MudObject) -> int:
            if (_trap_lock_ob
            && !_trap_lock_ob, _trap_lock_func.pick(TO, player)) {
            return 0


    def do_open(self, ) -> int:
            if (!_closed) {
            TP->add_failed_mess(TO,
            "$D $V$0=is,are$V$ already open.\n",
            [}) )
            return 0


    def do_close(self, ) -> int:
            if (_closed) {
            TP->add_failed_mess(TO,
            "$D $V$0=is,are$V$ already closed.\n",
            [}) )
            return 0



class Close_lock(MudObject):

    _difficulty = 5

    _pick_skill = '"covert.lockpick.doors"'
