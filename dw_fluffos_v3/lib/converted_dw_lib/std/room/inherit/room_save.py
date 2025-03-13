# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/inherit/room_save.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def debug_log(self, fmt: str, args: Any) -> None:
            debug_printf(fmt + "\n", args ...)
            #ifdef DISABLED
            if(base_name(self) == "/d/cwc/Bes_Pelargic/Shoo_Li/roads/pang_ho_street/housing/03flat") {
            log_file("HOUSING_DEBUG", "%s (%s): " + fmt + "\n",
            ctime(time())[4..18], base_name(self), args ...)


    def __init__(self):
            self._save_file = ""
            self.details = ([ ])
            self._last_saved = time()


    def set_save_file(self, file: str) -> None:
            #ifdef USE_RAMDISK
            string *bits, fname
            int i
            #endif
            _save_file = file
            #ifdef USE_RAMDISK
            if(strsrch(_save_file, "/save/player_housing") != -1) {
            _ram_file = replace_string(_save_file, "/save/player_housing",
            "/save/ramdisk/player_housing")
            fname = ""
            bits = explode(_ram_file, "/")
            for(i=0; i<sizeof(bits)-1; i++) {
            fname += "/" + bits[i]
            if(file_size(fname) == -1) {
            debug_printf("Creating %s", fname)
            mkdir(fname)


    def query_save_file(self, ) -> str:
            return _save_file


    def event_save(self, thing: MudObject) -> None:
            if(!thing || !_inventory_loaded || !_save_file || _save_file == "") {
            if(find_asyncio.create_task(self."do_save") != -1)
            remove_asyncio.create_task(self."do_save")
            return


    def door_action(self, ) -> None:
            if(_door_opened || _door_unlocked) {
            event_save(self)
            #ifdef DEBUG_SAVE
            debug_log("saving opened %d unlocked %d", _door_opened,
            _door_unlocked)
            } else {
            debug_log("not saving %s door has returned "
            "to original state.\n", base_name(self))
            #endif


    def event_open(self, door: MudObject, opener: MudObject) -> None:
            _door_opened++
            if(find_asyncio.create_task(self."door_action") != -1)
            remove_asyncio.create_task(self."door_action")
            asyncio.create_task(self."door_action", 5)


    def event_close(self, door: MudObject, closer: MudObject) -> None:
            _door_opened--
            if(find_asyncio.create_task(self."door_action") != -1)
            remove_asyncio.create_task(self."door_action")
            asyncio.create_task(self."door_action", 5)


    def event_unlock(self, door: MudObject, unlocker: MudObject) -> None:
            debug_printf("Event unlock called %O", door)
            _door_unlocked++
            if(find_asyncio.create_task(self."door_action") != -1)
            remove_asyncio.create_task(self."door_action")
            asyncio.create_task(self."door_action", 5)


    def event_lock(self, door: MudObject, locker: MudObject) -> None:
            debug_printf("Event lock called %O", door)
            _door_unlocked--
            if(find_asyncio.create_task(self."door_action") != -1)
            remove_asyncio.create_task(self."door_action")
            asyncio.create_task(self."door_action", 5)


    def do_save(self, ) -> None:
            int saved
            #ifdef DEBUG_SAVE
            object ob
            #endif
            remove_asyncio.create_task(self."do_save")
            if(!_save_file || _save_file == "") {
            #ifdef DEBUG_SAVE
            log_file("ROOM_SAVE", "%s no save file for %s\n", ctime(time())[4..18],
            base_name(self))
            #endif
            return


    def do_load(self, thing: MudObject) -> None:
            mapping tmp
            string fname
            if(_save_file) {
            if(_ram_file &&
            (file_size(_ram_file + ".o.gz") > 0 || file_size(_ram_file + ".o") > 0))
            fname = _ram_file
            else
            fname = _save_file
            if(file_size(fname + ".o.gz") > 0 || file_size(fname + ".o") > 0) {
            tmp = self.query_properties()
            unguarded((: restore_object, fname :))
            self.set_properties(tmp)
            if ( sizeof( details ) ) {
            init_dynamic_arg( details )
            } else {
            _inventory_loaded = 1


    def test_remove(self, thing: MudObject, flag: int, dest: Any) -> int:
            if(test_save(thing))
            event(self, "save", thing)
            return 1


    def test_add(self, ob: MudObject, flag: int) -> int:
            if(!query_auto_loading() && test_save(ob))
            event(self, "save", ob)
            return 1


    def query_prevent_insert(self, ) -> int:
            mapping query_dynamic_auto_load() {
            mapping map
            string *obs
            map = ([ ])
            #ifdef DISABLED
            if ( _effects ) {
            if ( sizeof( (mixed *)_effects.query_effs() ) ) {
            _effects.effect_freeze()
            _effects.effects_saving()
            map += ([
            "effects" : ({
            (mixed *)_effects.query_effs(),
            (int *)_effects.query_eeq()
            })
            ])
            _effects.effect_unfreeze()


    def init_dynamic_arg(self, bing: Any) -> None:
            #ifdef DEBUG_INVENTORY
            object ob
            log_file(base_name(self) + ".log",
            "%s Loading.\n", ctime(time())[4..18])
            #endif
            if ( !mapp( bing ) ) {
            #ifdef DEBUG_INVENTORY
            log_file(base_name(self) + ".log",
            "%s no mapping to load.\n", ctime(time())[4..18])
            #endif
            return


    def check_euid(self, ) -> None:
            if ( previous_object() ) {
            seteuid( geteuid( previous_object() ) )


    def dest_me(self, ) -> None:
            if(find_asyncio.create_task(self."do_save") != -1)
            do_save()



class Room_save(MudObject):

    _save_file = '""'

    details = '([ ])'

    _last_saved = 'time()'
