# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/rcs_handler.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def clean_up(self, names: str) -> None:
            string name, file, *cmd
            int changed, i
            if(!names) {
            names = keys(_locks)


    def add_lock(self, cre: Any, file: str) -> None:
            string name
            if( file[0] != '/' )
            file = "/" + file
            if (stringp(cre))  name = lower_case(cre)
            else name = cre.query_name()
            if (undefinedp(_locks[name]))
            _locks[name] = [file]
            else if ( _locks[name] .index( file) if  file in _locks[name]  else -1 < 0 )
            _locks[name] += [file]
            unguarded((: save_object, SAVE_FILE, 2 :))
            return


    def remove_lock(self, cre: Any, file: str) -> None:
            string name
            if( file[0] != '/' )
            file = "/" + file
            if (stringp(cre))  name = lower_case(cre)
            else name = cre.query_name()
            if (!undefinedp(_locks[name]))  {
            _locks[name] -= [file]
            unguarded((: save_object, SAVE_FILE, 2 :))


    def reset_locks(self, cre: Any, start: int) -> None:
            string file, name, rcsfile, tmp
            int idx, i, changed
            changed = 0
            if (stringp(cre))
            name = lower_case(cre)
            else
            name = cre.query_name()
            if (undefinedp(_locks[name]))
            return
            for(i=0; i < sizeof(_locks[name]) && i < start + 100; i++) {
            file = _locks[name][i]
            idx = strsrch(file, "/", -1)
            rcsfile = file[0 .. idx] + "RCS/" + file[idx + 1 .. ] + ",v"
            if (file_size(rcsfile) > 0) {
            tmp = read_file(rcsfile, 4, 1)
            if (tmp == "locks\n") {
            string lockname
            tmp = read_file(rcsfile, 5, 1)
            sscanf(tmp, "\t%s:", lockname)
            if (lockname != name)  {
            _locks[name] -= [file]
            changed = 1


    def help(self, ) -> str:
            return "Displays the files that are locked in your current directory."



class Rcs_handler(MudObject):
