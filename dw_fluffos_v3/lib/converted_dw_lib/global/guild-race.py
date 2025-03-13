# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/global/guild-race.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def race_guild_commands(self, ) -> None:
            string command
            string *bing
            string *paths = [})
            if (!known_commands) {
            known_commands = ["skills", "rearrange", "gp", "newbie"]


    def query_gtitle(self, ) -> str:
            string tmp
            if (class_ob)
            if (catch((tmp = (string)class_ob.query_title(self))))
            tmp = "Has a broken class"
            return tmp


    def set_race_ob(self, str: str) -> None:
            string frog
            if(sscanf(str, "/%s", frog)==1)
            str = extract(str, 1)
            if (str[0..strlen("std/races")-1]!="std/races") {
            write("Illegal path to set_race_ob.\n")
            return


    def set_guild_ob(self, str: str) -> None:
            if(str) {
            if(str[0..10] != "/std/classs") {
            tell_object(self, "Attempt to set invalid class object " +
            str + "\n")
            return
            } else if(!find_object(str)) {
            await self.send("No such object "+ str +"\n")
            return


    def query_guild_ob(self, ) -> str:
            if ( !class_ob ) {
            return 0


    def set_guild_data(self, dat: Any) -> None:
            mixed *query_class_data() {
            return class_data


    def query_race(self, ) -> str:
            if(!_race)
            _race = (string)race_ob.query_name()
            return _race


    def help_command(self, str: str) -> str:
            class command cmd = new(class command, verb : str)
            string path
            mixed func
            if ((known_commands.index(str) if str in known_commands else -1 != -1 ||
            self.query_creator()) &&
            CMD_D.HandleStars(cmd)) {
            path =  CMD_D.GetPaths(cmd->verb)[0] + "/" + cmd->verb
            func = path.help_function()
            if (func) {
            return func


    def query_known_command(self, word: str) -> int:
            return ( known_commands .index( word) if  word in known_commands  else -1 != -1 )


    def add_known_command(self, str: str) -> int:
            string *paths
            if (known_commands.index(str) if str in known_commands else -1 != -1) {
            return 0


    def remove_known_command(self, str: str) -> int:
            int i
            i = known_commands.index(str) if str in known_commands else -1
            if (i == -1) {
            return 0



class Guild-race(MudObject):
