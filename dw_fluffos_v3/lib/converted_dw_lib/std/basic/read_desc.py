# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/basic/read_desc.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def query_cur_size(self, ) -> int:
            varargs void set_read_mess(mixed str, string lang, int size) {
            if ( pointerp( str ) ) {
            _read_mess = str
            return


    def remove_read_mess(self, str: str, type: str, lang: str) -> int:
            int i
            for (i=0;i<sizeof(_read_mess);i++) {
            if (str && _read_mess[i][READ_STR] != str)
            continue
            if (type && _read_mess[i][READ_TYPE] != type)
            continue
            if (lang && _read_mess[i][READ_LANG] != lang)
            continue
            _cur_size -= _read_mess[i][READ_SIZE]
            *((int)LANGUAGE_HAND->query_language_size(lang,
            _read_mess[i][READ_STR]))
            _read_mess = _read_mess[0..i - 1] + _read_mess[i + 1..]
            return 1


    def query_readable_message(self, player: MudObject, ignore_labels: int) -> str:
            string message
            string file
            string type
            string lang
            mixed mess
            mixed *bit
            mixed *read_mess
            int pos
            if(!player)
            player = this_player()
            read_mess = query_read_mess()
            if ( !sizeof( read_mess ) ) {
            return 0


    def query_read_short(self, player: MudObject, ignore_labels: int) -> str:
            string id
            string *read_mess
            read_mess = query_read_mess()
            if ( !arrayp(read_mess) || !sizeof( read_mess ) ) {
            return 0



class Read_desc(MudObject):
