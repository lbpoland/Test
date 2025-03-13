# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/inherit/topography/milestone.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from .environment import weather_handler
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def add_milestone_dir(self, handler: str, dir: str) -> None:
            if (undefinedp(milestone_dirs[handler])) {
            milestone_dirs[handler] = [dir]
            } else {
            milestone_dirs[handler] += [dir]


    def query(self, s): str) -> Any:
            varargs void set_milestone_index(string handler, int index) {
            milestone_index[handler] = index


    def setup_milestone(self, ) -> None:
            string handler
            foreach (handler in keys(milestone_index)) {
            handler.setup_milestone(self)


    def add_milestone_exit(self, s: str, dest: str, type: str) -> int:
            string ss, em, xm, mm
            add_exit(s, dest, type)
            add_exit(motion_verb + " " + s, "interroom", "hidden")
            if (!undefinedp(shorten[s])) {
            ss = shorten[s]
            add_alias(motion_verb + " " + ss, motion_verb + " " + s)
            } else {
            ss = s


    def passing_mess(self, dir: str, ob: MudObject, special_mess: str) -> int:
            int i
            object *obs, passed
            string mess1, mess2, handler
            foreach (handler in keys(milestone_dirs)) {
            i = milestone_dirs[handler].index(dir) if dir in milestone_dirs[handler] else -1
            if (i < 0) {
            continue


    def query_look(self, direc: str) -> str:
            int i, dark
            string s, direc_s, h
            mixed dest
            direc_s = direc
            foreach (h in keys(milestone_dirs)) {
            i = milestone_dirs[h].index(direc_s) if direc_s in milestone_dirs[h] else -1
            if (i >= 0) {
            direc_s = motion_verb + " " + direc_s
            break


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



class Milestone(MudObject):
