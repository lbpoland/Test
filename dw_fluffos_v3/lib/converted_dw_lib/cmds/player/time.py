# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/time.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.time_rubbish = localtime(time())
            self._timezones = []


    def cmd(self, word: str) -> Any:
            mixed *time_rubbish
            int i
            string mess
            time_rubbish = localtime(time())
            mess = ""
            for (i = 0; i < sizeof(_timezones); i += 2) {
            mess += sprintf( "[%s in %-9s]\n", ctime(time() + time_rubbish[LT_GMTOFF] +
            _timezones[i + 1]), _timezones[i])


    def show_mud_time(self, ) -> None:
            #ifndef __DISTRIBUTION_LIB__
            string mess
            string day = cap_words(SPECIAL_DAY_HANDLER.query_special_day())
            mess = sprintf( "In Waterdeep, it is %s%s\n", amtime( time() ),
            ( strlen(day) ? ".  Today is "+ day +".": ".") )
            write( mess )
            #endif



class Time(MudObject):

    time_rubbish = 'localtime(time())'

    _timezones = '[]'
