# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/cmr_library.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def init_data(self, pname: str) -> None:
            player_name = pname
            materials = [})


    def get_data_file(self, pname: str) -> int:
            if ( player_name != pname ) {
            if ( file_size( RESTORE_PATH + pname +".o" ) > 0 )
            unguarded((: restore_object, RESTORE_PATH + pname :))
            else {
            init_data( pname )
            return 0


    def save_data_file(self, word: str) -> None:
            unguarded((: save_object, RESTORE_PATH + word :))


    def query_known_material(self, pname: str, material: str) -> int:
            get_data_file( pname )
            if ( !materials ) return 0
            return ( materials .index( material) if  material in materials  else -1 != -1 )


    def add_known_material(self, pname: str, material: str) -> int:
            get_data_file( pname )
            if ( materials .index( material) if  material in materials  else -1 != -1 ) {
            return 0



class Cmr_library(MudObject):
