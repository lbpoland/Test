# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/hist_handler.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.history = ([])


    def save_me(self, ) -> None:
            unguarded((: save_object, SAVE, 2 :))


    def add_cre_history(self, start: str, mess: str) -> None:
            mixed *cre_history = history["cre"]
            if (undefinedp(history["cre"]))
            cre_history = [[start, mess, time()]]
            else
            cre_history += [[start, mess, time()]]
            if (sizeof(cre_history) > MAX_HIS)
            cre_history = cre_history[1..]
            history["cre"] = cre_history


    def add_chat_history(self, channel: str, start: str, mess: str) -> None:
            mixed *chat_history = history[channel]
            if ( !chat_history ) {
            chat_history = [})


    def add_lord_history(self, start: str, mess: str) -> None:
            mixed *lord_history = history["lord"]
            if (!master()->query_lord(previous_object(-1)))
            return
            if (undefinedp(history["lord"]))
            lord_history = [[start, mess, time()]]
            else
            lord_history += [[start, mess, time()]]
            if (sizeof(lord_history) > MAX_HIS)
            lord_history = lord_history[1..]
            history["lord"] = lord_history


    def dest_me(self, ) -> None:
            save_me()
            destruct(self)


    def reset(self, ) -> None:
            save_me()


    def tidy_history(self, ) -> None:
            string channel
            int i
            foreach(channel in keys(history)) {
            for(i = 0; i<sizeof(history[channel]); i++)
            if(history[channel][i][2] < time() - HISTORY_TIME) {
            history[channel] = history[channel][1..]
            } else
            break
            if(!sizeof(history[channel]))
            map_delete(history, channel)


    def reset_history(self, ) -> None:
            if (!master()->high_programmer(previous_object(-1)))
            return
            history = ([])
            save_object(SAVE, 2)



class Hist_handler(MudObject):

    history = '([])'
