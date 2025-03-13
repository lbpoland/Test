# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/player/news.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def cmd(self, str: str) -> Any:
            int msg
            switch(str) {
            case "help":
            case "?":
            case "h":
            tell_object( this_player(),
            "Usage:\n"
            "To read next news item type: \"news\".\n"
            "To read a specific news item type: \"news <num>\".\n"
            "To list new news items type: \"news list\".\n"
            "To list all news items type: \"news review\".\n")
            break
            case "l":
            case "list":
            do_list(MOST)
            break
            case "r":
            case "review":
            do_list(ALL)
            break
            default:
            if(str) sscanf(str, "%d", msg)
            do_read(msg)


    def do_read(self, num: int) -> int:
            mapping news_rc
            mixed *stuff
            news_rc = BOARD_HAND.query_newsrc(this_player()->query_name())
            if ( !news_rc ) {
            news_rc = ([ ])


    def the_date(self, i: int) -> str:
            return ctime(i)[4..9]


    def do_list(self, all: int) -> None:
            int i, newones
            mixed *stuff
            string ret
            mapping news_rc
            ret = ""
            stuff = (mixed *)BOARD_HAND.get_subjects(board_name)
            if (!sizeof(stuff)) {
            await this_player().send("No news is good news.\n")
            return



class News(MudObject):
