# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/key_handler.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def set_key_permissions(self, group: str, key: str, types: str) -> None:
            get_data_file( party )
            if (sizeof(types)) {
            keys[ key ] = types
            } else {
            map_delete(keys, key)


    def query_key_permission(self, group: str, key: str, type: str) -> int:
            get_data_file( party )
            if ( !keys[ key ] ) {
            return 0


    def add_key_permission(self, group: str, key: str, type: str) -> int:
            get_data_file( party )
            if ( !keys[ key ] ) {
            keys[ key ] = [})


    def remove_key_permission(self, group: str, key: str, type: str) -> int:
            int i
            get_data_file( party )
            if ( !keys[ key ] ) {
            return 0


    def query_key_name(self, group: str, key: str) -> str:
            get_data_file( party )
            return key_names[ key ]


    def set_key_name(self, group: str, key: str, name: str) -> None:
            get_data_file( party )
            key_names[ key ] = name
            save_data_file( )


    def delete_key_name(self, group: str, key: str) -> None:
            get_data_file( party )
            if ( !key_names[ key ] ) {
            return



class Key_handler(MudObject):
