# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/hospital.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from .combat import combat_handler
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._group_info = ([ ])


    def __init__(self):
            self._group_info = ([ ])
            if (!_npc_info) {
            _npc_info = ([ ])


    def ok_to_clone(self, ) -> int:
            return 1


    def pick_al(self, average: int, range: int) -> int:
            int choice, section, section_width, result
            if( range < 0 ) {
            range = -range


    def set_data_directory(self, dir: str) -> None:
            _data_directory = dir
            asyncio.create_task(self."scan_for_new_data", 2)


    def query_data_directory(self, ) -> str:
            return _data_directory


    def set_npc_path(self, path: str) -> None:
            _npc_path = path


    def set_domain(self, domain: str) -> None:
            _domain = domain


    def set_max_cache(self, num: int) -> None:
            _max_cache = num


    def set_disable_npc_generation(self, value: int) -> None:
            _disable_npc_generation = value


    def query_disable_npc_generation(self, ) -> int:
            return _disable_npc_generation


    def npc_path(self, str: str) -> str:
            return _npc_path + "/" + str


    def scan_for_new_data(self, ) -> None:
            string *files
            string fname
            string *bits
            debug_printf("Scan for new data.")
            if (unguarded( (: stat(__FILE__)[1] :)) !=
            _file_modified_time[__FILE__]) {
            _file_modified_time = ([ ])


    def roll_dice(self, die: Any) -> int:
            int result
            int i
            if (intp(die)) {
            return die


    def query_npc_max_population(self, npc: str) -> int:
            if (!_npc_info[npc]) {
            return -1


    def query_npc_current_population(self, npc: str, clean: int) -> int:
            class npc_info data
            if (!_npc_info[npc]) {
            return -1


    def is_npc_under_max_population(self, name: str) -> int:
            class npc_info info
            info = _npc_info[name]
            if (!info) {
            return 0


    def is_group_under_max_population(self, name: str) -> int:
            class party_info party
            party = _party_info[name]
            if (!party) {
            return 0


    def npc_died(self, ob: MudObject) -> None:
            string npc_id
            class npc_info info
            int i
            mixed* stuff
            npc_id = ob.query_property("npc_id")
            info = _npc_info[npc_id]
            if (!info || !npc_id) {
            return


    def load_random_npc(self, zone: str, wealth: int, busy: int) -> List[MudObject]:
            int chance
            int pos
            if (_disable_npc_generation) {
            return [})


    def do_report(self, ) -> int:
            string name
            class party_info party
            class npc_info npc
            string txt
            int total
            int max
            int pop
            txt = ""
            total = 0
            txt += "%^WHITE%^NPCs%^RESET%^\n"
            foreach( name, npc in _npc_info ) {
            if(stringp(npc->path) && file_size(npc_path(npc->path) + ".c") > 0) {
            pop = query_npc_current_population(name, 0)
            } else {
            pop = 0


    def init(self, ) -> None:
            object ob
            ob = this_player()
            add_command("report", "", (: do_report :))
            if(ob.query_property("npc_id") && ob.query_property("hospital") &&
            ob.query_property("hospital") == base_name(self)) {
            if(!_cache_inventory[ob.query_property("npc_id")])
            _cache_inventory[ob.query_property("npc_id")] = [ob]
            else if(sizeof(_cache_inventory[ob.query_property("npc_id")]) >
            _max_cache)
            ob.move("/room/rubbish")
            else
            _cache_inventory[ob.query_property("npc_id")] += [ob]
            } else if(base_name(ob) == "/obj/corpse")
            ob.move("/room/rubbish")


    def no_attack(self, ) -> int:
            mapping query_dynamic_auto_load() {
            string party_name
            string npc
            class party_info data
            class npc_info npc_data
            mapping tmp
            mapping tmp2
            tmp = allocate_mapping( sizeof( _party_info ) )
            foreach( party_name, data in _party_info ) {
            tmp[ party_name ] = data->storage


    def init_dynamic_arg(self, tmp: Any) -> None:
            string party_name
            object *npcs
            if ( tmp[ file_name( self ) ] ) {
            foreach( party_name, npcs in tmp[ file_name( self ) ] ) {
            if (_party_info[party_name]) {
            _party_info[ party_name ]->storage = npcs


    def query_all_npcs(self, ) -> Any:
            return values( map( _party_info, (: $2->storage :) ) )



class Hospital(Room):

    _group_info = '([ ])'
