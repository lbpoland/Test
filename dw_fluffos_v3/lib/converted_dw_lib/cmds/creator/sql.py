# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/sql.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def prompt(self, db: str, user: str, pass: str, player: MudObject) -> None:
            if(!strlen(COM)) {
            await player.send("sql> ")
            } else {
            await player.send("  -> ")


    def cmd(self, arg: str, user: str, passwd: str) -> int:
            string err
            if(!passwd){
            passwd = ""


    def main(self, input: str, db: str, user: str, passwd: str) -> None:
            if(strlen(input)) {
            while(input[<1] == ' ') {
            input = input[0..<2]


    def edfin(self, input: str, args: Any) -> None:
            COM=input
            prompt(args[0], args[1], args[2], this_player())



class Sql(MudObject):
