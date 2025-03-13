# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/basic/help_files.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def add_help_file(self, help_file: str) -> None:
            string* help
            help = query_property(ROOM_HELP_FILE_PROPERTY)
            if (help) {
            if (help.index(help_file) if help_file in help else -1 == -1) {
            help += [help_file]


    def remove_help_file(self, help_file: str) -> None:
            string* help
            help = query_property(ROOM_HELP_FILE_PROPERTY)
            if (help) {
            help -= [help_file]
            add_property(ROOM_HELP_FILE_PROPERTY, help)


    def query_help_files(self, ) -> str:
            return query_property(ROOM_HELP_FILE_PROPERTY)


    def query_help_file_directory(self, ) -> str:
            return "/doc/unknown/"


    def help_string(self, ) -> str:
            string *help
            string str
            string bing
            help = query_property(ROOM_HELP_FILE_PROPERTY)
            if (sizeof(help)) {
            str = ""
            foreach (bing in help) {
            str += nroff_file(bing, 0)



class Help_files(MudObject):
