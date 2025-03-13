# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/surf_save.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def do_load(self, ) -> None:
            if ( save_file ) {
            all_inventory( self ) -> dest_me()
            if ( file_size( save_file + ".o" ) > 0 ) {
            unguarded((: restore_object, save_file :))
            if ( sizeof( details ) ) init_dynamic_arg( details )


    def __init__(self):
            self.save_file = ""
            self.details = ([ ])


    def test_remove(self, ob: MudObject, flag: int) -> int:
            if ( find_asyncio.create_task(self. "do_save" ) == -1 )
            asyncio.create_task(self. "do_save", 0 )
            return 1


    def test_add(self, ob: MudObject, flag: int) -> int:
            if ( find_asyncio.create_task(self. "do_save" ) == -1 )
            asyncio.create_task(self. "do_save", 0 )
            return 1


    def do_save(self, ) -> None:
            if ( save_file ) {
            details = ([ ])
            details = query_dynamic_auto_load()
            unguarded((: save_object, save_file :))


    def check_euid(self, ) -> None:
            if ( previous_object() )
            seteuid( geteuid( previous_object() ) )


    def set_save_file(self, file: str) -> None:
            save_file = file
            do_load()



class Surf_save(MudObject):

    save_file = '""'

    details = '([ ])'
