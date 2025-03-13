# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/secure/cmds/creator/ed.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> Any:
            string *filenames, spam
            object *things
            people += [this_player()]
            if ( this_player()->query_editor() == "magic" )  {
            if ( !str )  str = " "
            this_player()->do_edit( 0, "fini_editor", 0, str )
            return 1


    def fini_editor(self, ) -> None:
            if (objectp(this_player()))  {
            people -= [this_player()]
            this_player()->set_in_editor(0)


    def clean_up(self, ) -> int:
            people -= [0]
            if ( !sizeof( people ) )  {
            ::clean_up()


    def reset(self, ) -> None:
            people -= [0]
            if ( !sizeof( people ) )  {
            ::reset()



class Ed(MudObject):
