# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/cmds/creator/zcat.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, fname: str, list: int) -> int:
            string *files
            string euid
            string args
            int fd
            int count
            files = this_player()->get_files( fname )
            if ( !sizeof( files ) ) {
            files += [this_player()->get_path( fname )]


    def read_call_back(self, fd: int, mess: Any) -> None:
            int max_len
            int new_total
            mess = replace(mess, "/bin/", "")
            max_len = get_config( __MAX_STRING_LENGTH__ )
            new_total = strlen( RET ) + strlen( mess )
            if ( new_total > max_len ) {
            mess = mess[ 0.. (new_total - max_len - 1) ]


    def write_call_back(self, fd: int) -> None:
            tell_object(TP, "zcat: A fatal error has occurred -- write_call_back "
            "was called.\n")


    def close_call_back(self, fd: int) -> None:
            if ( RET != "" ) {
            if ( catch( TP.more_string(strip_colours(RET)) ) ) {
            efun::await  TP.send(RET )



class Zcat(MudObject):
