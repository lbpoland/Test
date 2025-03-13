# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/d/admin/master.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.( file ! = "ENTER.log" &&
            self.file = explode( file, "." )[ 0 ]
            self.for(i = (BACKUP_COUNT-1); i>0; i--)


    def query_lord(self, ) -> str:
            return LORD


    def author_file(self, path: str) -> str:
            return capitalize(DOMAIN)


    def check_permission(self, euid: str, path: str, mask: int) -> int:
            if (euid == query_lord())
            return 1
            return ::check_permission(euid, path, mask)


    def add_member(self, name: str) -> int:
            if (geteuid(this_player(1)) != query_lord())
            return 0
            return ::add_member(name)


    def remove_member(self, name: str) -> int:
            if (geteuid(this_player(1)) != query_lord())
            return 0
            return ::remove_member(name)


    def set_project(self, name: str, pro: str) -> int:
            if (geteuid(this_player(1)) != query_lord())
            return 0
            return ::set_project(name, pro)


    def query_member(self, name: str) -> int:
            return !undefinedp(members[name]) || name == LORD


    def log_who(self, where: str) -> str:
            return LORD


    def query_info(self, ) -> str:
            return "\nThe admin domain is made up of the active Trustees of "
            "Faerûnworld.  Their role is to ensure the smooth running of the game.  "
            "They carry the ultimate responsibility for Faerûnworld, how it operates "
            "and its policies and rules.\n\n"



class Master(MudObject):

    ( file ! = '"ENTER.log" &&'

    file = 'explode( file, "." )[ 0 ]'

    for(i = '(BACKUP_COUNT-1); i>0; i--)'
