# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/corpse_handler.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._corpses = ([ ])
            self._corpse_id = 1
            self._to_save = ([ ])


    def find_player_corpses(self, player: str) -> List[MudObject]:
            object* corpses
            corpses = filter( children( "/obj/corpse" ),
            (: $1 && $1.query_property( "player" ) &&
            $1.query_ownership() == $2 :), player )
            return corpses


    def save_corpse(self, ob: MudObject) -> None:
            class corpse_data corpse
            if (!ob.query_property("player") || !ob.query_ownership()) {
            return


    def create_corpse(self, name: str, id: int) -> MudObject:
            class corpse_data corpse
            string data, fname
            object ob
            corpse = find_corpse_data(name, id)
            #ifdef USE_RAMDISK
            if(unguarded( (: file_size(CORPSE_RAM_DIR + $(corpse->id)) :)) > 0)
            fname = CORPSE_RAM_DIR + corpse->id
            #endif
            if(!fname)
            fname = CORPSE_SAVE_DIR + corpse->id
            data = unguarded( (: read_file($(fname)) :))
            if (data) {
            ob = clone_object(CORPSE_OBJECT)
            ob.setup_corpse_from_save(data, name, id)
            return ob


    def check_corpses(self, ) -> None:
            class corpse_data* corpses
            string name
            object* obs
            int i
            int j
            foreach (name, corpses in _corpses) {
            obs = find_player_corpses(name)
            for (i = 0; i < sizeof(corpses); i++) {
            for (j = 0; j < sizeof(obs); j++) {
            if (obs[j]->query_corpse_id() == corpses[i]->id) {
            corpses = corpses[0..i -1] + corpses[i+1..]
            i--


    def query_next_corpse_id(self, ) -> int:
            int id
            id = _corpse_id++
            save_me()
            return id


    def register_corpse(self, ob: MudObject) -> None:
            string name
            int id
            class corpse_data corpse
            tell_creator("Registering %O (%O)\n", ob, ob.query_ownership())
            name = ob.query_ownership()
            if(PLAYER_HANDLER.test_creator(name)) {
            tell_creator("pinkfish", "Not registering creator corpse %O (%O)\n",
            ob, ob.query_ownership())
            return


    def deregister_corpse(self, ob: MudObject) -> None:
            string name
            int id
            class corpse_data corpse
            int i
            if (!ob.query_property("player")) {
            return



class Corpse_handler(MudObject):

    _corpses = '([ ])'

    _corpse_id = 1

    _to_save = '([ ])'
