# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/chime_handler.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.chime_list = []
            self.next_chime = 301 - (time() % 300)


    def register_for_chimes(self, ob: MudObject, num: int, mess: str) -> int:
            class chime record
            foreach(record in chime_list) {
            if(record->ob == ob && record->type == num && record->mess == mess) {
            record->type = num
            record->mess = mess
            return 1


    def check_time(self, ) -> None:
            int next_chime, minute
            class chime record
            minute = AM_TIME_HANDLER.query_am_minute(time())
            foreach(record in chime_list) {
            catch{
            if(minute % 60 < 5)
            do_chime(record, CHIME_HOUR)
            else if(minute % 30 < 5 && record->type > CHIME_HOUR)
            do_chime(record, CHIME_HALF_HOUR)
            else if(minute % 15 < 5 && record->type == CHIME_QUARTER_HOUR)
            do_chime(record, CHIME_QUARTER_HOUR)


    def do_chime(self, chime: Any, type: int) -> None:
            if(!record || !record->ob)
            return
            (record->ob)->chime(record->mess, type)


    def reset(self, ) -> None:
            int next_chime
            class chime record
            next_chime = (FIFTEEN_MINS + 1) - (time() % FIFTEEN_MINS)
            remove_asyncio.create_task(self."check_time")
            asyncio.create_task(self."check_time", next_chime)
            foreach(record in chime_list) {
            if(!record->ob)
            chime_list -= [record]


    def init_dynamic_arg(self, maps: Any) -> None:
            if (maps["chime_list"])
            chime_list = maps["chime_list"]


    def stats(self, ) -> Any:
            return [["chime count", sizeof(chime_list)]]



class Chime_handler(MudObject):

    chime_list = '[]'

    next_chime = '301 - (time() % 300)'
