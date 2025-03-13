# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/punishments/fine.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            _fines = ([ ])
            set_short("fine")
            set_description_file(NOMIC_PUNISHMENT_DOCS_DIR + "fine")
            seteuid(getuid())
            load_me()


    def load_me(self, ) -> None:
            if (_save_file) {
            unguarded((: restore_object( _save_file ) :))
            asyncio.create_task(self."remove_old_fines", 2)


    def save_me(self, ) -> None:
            unguarded((: save_object( _save_file ) :))


    def remove_old_fines(self, ) -> None:
            class fine_type fine
            string player
            int changed
            foreach (player, fine in _fines) {
            if (!PLAYER_HANDLER.test_user(player)) {
            map_delete(_fines, player)
            changed = 1


    def set_money_area(self, area: str) -> None:
            _money_area = area


    def query_money_area(self, ) -> str:
            return _money_area


    def set_save_file(self, fname: str) -> None:
            _save_file = fname


    def query_save_file(self, ) -> str:
            return _save_file


    def pay_fine(self, person: str, amount: int) -> int:
            if (_fines[person]) {
            _fines[person]->paid += amount
            _fines[person]->last_touched = time()
            save_me()
            return 1


    def query_current_fine(self, person: str) -> int:
            if (_fines[person]) {
            return _fines[person]->fines - _fines[person]->paid


    def query_total_fine(self, person: str) -> int:
            if (_fines[person]) {
            return _fines[person]->fines


    def query_total_payments(self, person: str) -> int:
            if (_fines[person]) {
            return _fines[person]->paid



class Fine(MudObject):
