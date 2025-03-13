# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/dest_ruct.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def ask_dest(self, obs: MudObject) -> None:
            if (!pointerp(obs) || !sizeof(obs)) {
            write("No more things to dest.\n")
            return


    def dest_answer(self, s: str, majd: int, obs: MudObject) -> None:
            string err, shrt
            if (this_player()->affirmative(s)) {
            if (majd) {
            shrt = (string)obs[0]->short()
            err = catch(obs[0]->dwep())
            this_player()->handle_error(err, "DWEP")
            if (obs[0]) {
            write("It REALLY doesn't want to be dested.\n")
            err = catch(destruct(obs[0]))
            this_player()->handle_error(err, "destruct()")


    def cmd(self, str: str) -> Any:
            object *ob, *dest_obj
            string qstr
            dest_obj = [})
            notify_fail("Can't find " + str + " to dest.\n")
            if ( !str || ( str == "" ) )
            return notify_fail( "Destruct what?\n" )
            if (this_player()->query_name() == "simidh") {
            write("Bye bye...\n")
            this_player()->dest_me()
            return 1


    def main_dest_bit(self, ob: MudObject) -> None:
            object thing, *rest, *dest_obj
            string err, shrt, dobj
            rest = [})
            dest_obj = [})
            foreach (thing in ob) {
            if (interactive(thing) && sizeof(ob) != 1) {
            write("You DON'T destruct " + thing.query_name() + ".\n")
            continue



class Dest_ruct(MudObject):
