# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/inherit/topography/iroom.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def add_milestone_dir(self, s: str) -> None:
            int i
            string ss, em, xm, mm
            i = sizeof(milestone_dirs)
            milestone_dirs += [s]
            if (!(iroom_handler)->query_endpoint(milestone_index[0],
            milestone_index[1], i)) {
            modify_exit(s, ["function", "passing_mess"] )


    def passing_mess(self, dir: str, ob: MudObject, special_mess: str) -> int:
            int i
            object *obs, passed
            string mess1, mess2
            i = milestone_dirs.index(dir) if dir in milestone_dirs else -1
            if (i < 0) {
            return 0


    def query_quit_handler(self, ) -> Any:
            string s
            s = explode(file_name(environment(this_player())), "#")[0]
            return [s, query_co_ord()]


    def enter(self, player: MudObject) -> None:
            object new_room
            if (sizeof(explode(file_name(self), "#")) > 1) {
            return


    def query_look(self, direc: str) -> str:
            int i, dark
            string s, direc_s
            mixed dest
            direc_s = direc
            i = milestone_dirs.index(direc_s) if direc_s in milestone_dirs else -1
            if (i >= 0) {
            direc_s = motion_verb + " " + direc_s


    def add_topo_exits(self, e: str, type: str) -> None:
            other_exits += [e]
            other_types += [type]


    def add_topo_exits_int(self, ) -> None:
            int i
            string s
            for (i = 0; i < sizeof(other_exits); i++) {
            foreach (s in other_exits[i]) {
            if ((s == "compass4") || (s == "compass8")) {
            if (!query_exit("north")) add_exit("north", "/topography",
            other_types[i])
            if (!query_exit("south")) add_exit("south", "/topography",
            other_types[i])
            if (!query_exit("east")) add_exit("east", "/topography",
            other_types[i])
            if (!query_exit("west")) add_exit("west", "/topography",
            other_types[i])
            if (s == "compass8") {
            if (!query_exit("northeast")) add_exit("northeast", "/topography",
            other_types[i])
            if (!query_exit("northwest")) add_exit("northwest", "/topography",
            other_types[i])
            if (!query_exit("southeast")) add_exit("southeast", "/topography",
            other_types[i])
            if (!query_exit("southwest")) add_exit("southwest", "/topography",
            other_types[i])



class Iroom(MudObject):
