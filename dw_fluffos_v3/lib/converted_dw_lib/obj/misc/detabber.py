# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/detabber.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            {   set_name("detabber")
            set_long("A long stick with absoulutely no tabs in it.\n"
            "Usage:  detab <filename>.\n")


    def init(self, ) -> None:
            {   this_player()->add_command("detab",self,"<string>")


    def do_detab(self, indirect_obs: MudObject, dir_match: str, indir_match: str, args: Any, pattern: str) -> int:
            {
            string file
            string tb
            tb = sprintf("\t")
            file = read_file(args[0])
            if(file)
            {file = replace_string(file,"\t","    ")
            write_file(args[0],file,1)
            return 1



class Detabber(MudObject):
