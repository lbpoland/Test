# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/cmds/creator/ls.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> Any:
            string *bits, path
            int mask, i
            mask = (MASK_C|MASK_F)
            if (str) {
            if ( this_player()->query_property( LS_COMMAND_NICKNAME_PROPERTY ) ) {
            str = this_player()->expand_nickname( str )


    def dir_entry(self, path: str, name: str, size: int, mask: int) -> str:
            string tmp
            tmp = ""
            if(size == -2) {
            if(mask & MASK_F)
            name += "/"
            return "   - " + name


    def ls(self, str: str, mask: int) -> int:
            string *bit, *bing, bong, path
            int i, j, k, size
            mixed *direc
            path = str
            if (file_size(str) == -2 && str[strlen(str)-1] != '/' &&
            !(mask & MASK_D)) {
            path += "/"


    def check_dots(self, arg: Any) -> int:
            return arg[0][0] != '.'


    def is_dir(self, arg: Any, path: str) -> int:
            return (file_size(this_player()->get_path(sprintf("%s/%s", path, arg)))
            == -2)



class Ls(MudObject):
