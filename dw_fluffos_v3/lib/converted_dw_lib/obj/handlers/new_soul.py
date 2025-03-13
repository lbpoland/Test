# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/new_soul.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.soul_commands = 0
            self.soul_command_names = ([ ])
            self.pattern_cache = ([ "" : NO_ARGUMENT ])
            self.pcache_order = []
            self.scache_order = []
            self.soul_cache = ([ ])


    def clean_cache(self, ) -> None:
            int i
            for (i = 0; i < (sizeof(pcache_order) - PCACHE_MAX_SIZE); i++) {
            map_delete(pattern_cache, pcache_order[i])


    def add_soul_command(self, name: str, data: Any) -> None:
            if (file_name(previous_object()) != SOUL_COMPILER)
            return
            save_soul_command(name, data)
            map_delete(soul_cache, name)
            save_it()


    def delete_soul_command(self, name: str) -> None:
            map_delete(soul_cache, name)
            map_delete(soul_command_names, name)
            unguarded((: rm, SOUL_DATA_DIR + name + ".os" :))
            save_it()


    def save_it(self, ) -> None:
            unguarded((: save_object, SAVE_FILE :))


    def load_it(self, ) -> None:
            string *names
            int i
            unguarded((: restore_object, SAVE_FILE :))
            if (mapp(soul_commands)) {
            soul_command_names = ([ ])
            names = keys(soul_commands)
            for (i = 0; i < sizeof(names); i++) {
            reset_eval_cost()
            save_soul_command(names[i], soul_commands[names[i]])


    def get_name(self, ob: MudObject, use_name: int, type: int) -> str:
            if(ob == previous_object())
            return ob.query_objective() + "self"
            if(userp(ob) && use_name && environment(ob) != environment(previous_object()))
            return "$mirror_short:" + file_name(ob) + "$"
            return ob.one_short(use_name)


    def add_start(self, pat: str, verb: str) -> str:
            return verb + " " + pat


    def help_list(self, ) -> str:
            return "$P$Soul$P$The commands available in this soul currently number " +
            sizeof(soul_command_names) +
            ".\nHere is a nice list of them.\nGood luck!\n" +
            sprintf("%-#*s\n\n", (int) this_player()->query_cols(),
            implode(sort_array(keys(soul_command_names), 1), "\n"))


    def help_string(self, verb: str) -> str:
            string ret, arg
            int i
            mixed target
            mixed *data
            if (!soul_command_names[verb])
            return 0
            data = query_soul_command_data(verb)
            ret = sprintf("Allowed command patterns:\n%-#*s\n\n",
            (int) this_player()->query_cols(),
            implode(map_array(data[PATTERNS],
            "add_start", self, verb), "\n"))
            if (data[SINGLE]) {
            if (data[SINGLE][NO_ARGUMENTS]) {
            ret += "Has a no arguments mode.\nSelf:   " +
            create_message(0, "", data[SINGLE][NO_ARGUMENTS][SELF], 0, 0,
            0, 0, this_player(), 0) +
            "Others: " +
            create_message(0, "", data[SINGLE][NO_ARGUMENTS][REST], 1, 0,
            0, 0, this_player(), 0) + "\n"


    def do_force(self, arr: Any) -> None:
            string cmd
            cmd = explode(arr[1], " ")[0]
            if (soul_command_names[cmd] &&
            !arr[0]->query_property("dead") &&
            userp(arr[0]))
            arr[0]->eventForce(arr[1])


    def query_pcache_size(self, ) -> int:
            return sizeof(keys(pattern_cache))


    def query_scache_size(self, ) -> int:
            return sizeof(keys(soul_cache))



class New_soul(MudObject):

    soul_commands = 0

    soul_command_names = '([ ])'

    pattern_cache = '([ "" : NO_ARGUMENT ])'

    pcache_order = '[]'

    scache_order = '[]'

    soul_cache = '([ ])'
