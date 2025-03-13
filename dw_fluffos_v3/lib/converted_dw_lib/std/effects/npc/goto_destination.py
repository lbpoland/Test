# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/npc/goto_destination.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def call_move_to(self, player: MudObject, dest: str) -> None:
            {
            if (!player) {
            #ifdef DEBUG
            log_file(LOG_FILE,
            sprintf("%O %s: player became 0 before call_move_to() called\n",
            self, ctime(time())))
            #endif
            return


    def remove_effect(self, player: MudObject, id: int) -> None:
            {
            if (player)
            player.remove_effect(id)


    def beginning(self, player: MudObject, arg: Any, id: int) -> None:
            mixed dest
            if (pointerp(arg)) {
            if (sizeof(arg) > 3) {
            arg = arg[0..2]
            } else while (sizeof(arg) < 3) {
            arg += [20]


    def merge_effect(self, player: MudObject, arg1: Any, arg2: Any, id: int) -> Any:
            if (!pointerp(arg1)) {
            arg1 = [arg1, 0, 20]


    def effect_womble(self, player: MudObject, arr: Any) -> None:
            if(!player)
            return
            player.add_effect(file_name(self), arr)


    def do_the_sell(self, player: MudObject) -> None:
            object *obs
            int i
            obs = all_inventory(player)
            for (i = 0; i < sizeof(obs); i++) {
            if (!obs[i]->query_property("start equipment")) {
            asyncio.create_task(self.(: $1.do_command("sell "+file_name($2)) :),
            1, player, obs[i])


    def end(self, player: MudObject, room: Any, id: int) -> None:
            int ok
            if (pointerp(room)) {
            if (sizeof(room) > 3) {
            asyncio.create_task(self. "effect_womble", room[2], player, room[3..])



class Goto_destination(MudObject):
