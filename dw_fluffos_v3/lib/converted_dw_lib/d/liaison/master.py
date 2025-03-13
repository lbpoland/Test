# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/liaison/master.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def query_lord(self, ) -> str:
            return LORD


    def author_file(self, path: str) -> str:
            return capitalize(DOMAIN)


    def check_permission(self, euid: str, path: str, mask: int) -> int:
            if (euid == query_lord())
            return 1
            return ::check_permission(euid, path, mask)


    def query_member(self, name: str) -> int:
            return !undefinedp(members[name]) || name == LORD


    def log_who(self, where: str) -> str:
            return "eron"


    def query_info(self, ) -> str:
            if (file_size(LIAISON_DOMAIN_INFO) < 0) {
            return "\nFor information on this domain, please visit "
            "http:


    def add_member_alias(self, name: str, alias: str) -> int:
            if ( !members[ name ] )
            return 0
            if ( !"/secure/login"->test_user( alias ) )
            return 0
            if ( !member_alias )
            member_alias = ([ ])
            if ( !member_alias[ name ])
            member_alias[ name ] = [})
            member_alias[ name ] -= [alias]
            member_alias[ name ] += [alias]
            save_me()
            return 1


    def delete_member_alias(self, name: str, alias: str) -> int:
            if ( !members[ name ] )
            return 0
            if ( !member_alias )
            member_alias = ([ ])
            if ( !member_alias[ name ])
            member_alias[ name ] = [})
            member_alias[ name ] -= [alias]
            save_me()
            return 1



class Master(MudObject):
