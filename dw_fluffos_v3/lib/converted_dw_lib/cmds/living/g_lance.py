# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/living/g_lance.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def check_pre_stuff(self, ) -> int:
            int dark
            object room
            room = environment(previous_object())
            if (!room) {
            return notify_fail("You are in limbo... sorry you can't look at "+
            "anything.\n")


    def cmd_ob(self, obs: Any) -> Any:
            object thing
            int retval
            int dark
            object room
            retval = check_pre_stuff()
            if (retval != 2) {
            return retval


    def cmd_direction(self, dir: str, from_string: int) -> Any:
            object room
            int dark
            int retval
            string ret
            string dest
            mixed *func
            retval = check_pre_stuff()
            if (retval != 2) {
            return retval


    def room_glance(self, person: MudObject, room: MudObject, dark: int) -> str:
            string ret
            string sees
            object mirror
            ret = ""
            if (person.query_creator()) {
            ret += " %^CYAN%^" + file_name(room) + "%^RESET%^"
            sees=(string)room.query_property("creator sees")
            if (sees) {
            ret += sees +"\n"+ (string)room.query_contents()


    def cmd_here(self, ) -> int:
            object room
            int dark
            int retval
            string str
            retval = check_pre_stuff()
            if (retval != 2) {
            return retval


    def check_exists(self, file: str) -> int:
            if ( objectp( find_object( file ) ) )
            return 1
            if (file_size(file+".c") > 0) {
            return 1



class G_lance(MudObject):
