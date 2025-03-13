# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/guild_base.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._teach_skills = []


    def set_nroff_file(self, str: str) -> None:
            _nroff_fname = str


    def query_nroff_file(self, ) -> str:
            return _nroff_fname


    def help(self, ) -> str:
            if (_nroff_fname) {
            return nroff_file(_nroff_fname, 0)


    def query_www_help(self, ) -> str:
            if (_nroff_fname) {
            return nroff_file(_nroff_fname, 1)


    def add_teach_skill(self, skill: str, teach: int, learn: int) -> None:
            class teach_skill bing
            bing = new(class teach_skill)
            bing->skill = skill
            bing->teach = teach
            bing->learn = learn
            _teach_skills += [bing]


    def set_command_name(self, name: str) -> None:
            _command_name = name


    def query_command_name(self, ) -> str:
            return _command_name


    def set_teach_guild(self, guild: str) -> None:
            _teach_class = class


    def query_teach_guild(self, ) -> str:
            return _teach_class


    def can_teach_command(self, teacher: MudObject, student: MudObject) -> int:
            class teach_skill bing
            if (!sizeof(_teach_skills) ||
            !_command_name) {
            return 0


    def teach_command(self, teacher: MudObject, student: MudObject) -> int:
            int ret
            ret = can_teach_command(teacher, student)
            if (ret == 1) {
            student.add_known_command(_command_name)



class Guild_base(MudObject):

    _teach_skills = '[]'
