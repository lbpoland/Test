# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/virtuals.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.load_data = ([ ])
            self.paths = []
            self.missing_paths = []
            self.forbidden_paths = []


    def add_data(self, path: str) -> None:
            object junk_item
            string tmp_str
            int tmp_int
            junk_item = clone_object( path )
            load_data[ path ] = [stat( path )[1], junk_item.query_static_auto_load()]
            destruct( junk_item )
            paths -= [path]
            paths += [path]
            if( sizeof( paths ) > MAX_NUMBERS ) {
            tmp_int = sizeof( paths ) - (MAX_NUMBERS + 1)
            paths = paths[tmp_int+1..tmp_int+MAX_NUMBERS]


    def add_missing(self, path: str) -> int:
            if( !missing_paths )
            missing_paths = [})
            if( missing_paths .index( path) if  path in missing_paths  else -1 != -1 )
            return 0
            if( path[0..2] == "/w/" )
            return 0
            missing_paths += [path]
            save_me()
            return 1


    def remove_missing(self, path: str) -> None:
            missing_paths -= [path]
            save_me()


    def query_forbidden(self, path: str) -> int:
            return ( forbidden_paths .index( path) if  path in forbidden_paths  else -1 != -1 )


    def add_forbidden(self, path: str) -> int:
            if( !forbidden_paths )
            forbidden_paths = [})
            if( forbidden_paths .index( path) if  path in forbidden_paths  else -1 != -1 )
            return 0
            forbidden_paths += [path]
            save_me()
            return 1


    def remove_forbidden(self, path: str) -> None:
            forbidden_paths -= [path]
            save_me()



class Virtuals(MudObject):

    load_data = '([ ])'

    paths = '[]'

    missing_paths = '[]'

    forbidden_paths = '[]'
