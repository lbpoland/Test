# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/tell!.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, arg: str, thing: Any, silent: int) -> int:
            string word, lang, words, emotion
            #ifdef USE_SMILEYS
            string smiley, smiley_words
            #endif
            string them_mess, temp
            string me_mess
            object *obs
            object *net_dead
            object *fail
            mixed busy
            emotion = ""
            if (pointerp(thing)) {
            words = arg
            } else if ( !objectp( thing ) ) {
            if ( !arg || sscanf( arg, "%s %s", word, words ) != 2 )
            return 0
            word = lower_case( word )
            word = (string)TP.expand_nickname( word )
            thing = find_player( word )
            if ( !thing ) {
            if ( sscanf( word, "%*s@%*s" ) == 2 ) {
            "/net/daemon/out_tell"->do_tell( word+" "+words )
            return 1



class Tell!(MudObject):
