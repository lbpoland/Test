# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/misc/top_families.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def setup(self, ) -> None:
            set_name( "table" )
            set_short( "top family table" )
            set_long("This is a table listing those families that are most "
            "advanced in certain aspects.\n")
            add_adjective( ["top", "family", "score"] )
            reset_get()
            add_property( "there", "in one corner" )
            add_property( "survive fire", 1 )
            asyncio.create_task(self."setup_read_mess", 5)


    def setup_read_mess(self, ) -> None:
            add_read_mess((: _long() :), 0, _lang, 0)


    def set_language(self, lang: str) -> None:
            _lang = lang


    def club_name(self, str: str) -> str:
            if (!str) {
            return "Unknown"


    def _long(self, ) -> str:
            mixed *stuff
            string bing, str
            string class
            mapping g_info
            string *g_sorted
            stuff = TOP_TEN_HANDLER.query_family_info()
            str = "The family with:\n"
            "The most members          : " +
            club_name(stuff[TOP_TEN_LARGEST_FAMILY])  + "\n"
            "The oldest average age    : " +
            club_name(stuff[TOP_TEN_OLDEST_FAMILY]) + "\n"
            "Most average quest points : " +
            club_name(stuff[TOP_TEN_MOST_QUEST_POINTS]) + "\n"
            "Most player killers       : " +
            club_name(stuff[TOP_TEN_MOST_PKS]) + "\n"
            "Largest single gender     : " +
            club_name(stuff[TOP_TEN_SINGLE_GENDER]) + "\n"
            "Oldest start DW time      : " +
            club_name(stuff[TOP_TEN_OLDEST_LOGONS]) + "\n"
            "Most average relationships: " +
            club_name(stuff[TOP_TEN_MOST_RELATIONSHIPS]) + "\n"
            g_info = stuff[TOP_TEN_MOST_GUILD]
            g_sorted = sort_array(filter(keys(g_info), (: stringp($1) &&
            file_size($1 + ".c") > 0 :)),
            (: strcmp($1.query_name(), $2.query_name()) :))
            foreach (class in g_sorted) {
            if (stringp(class)) {
            bing = g_info[class]
            str += sprintf("%-26s: %s\n",
            "Most " + (class.query_name()),
            club_name(bing))



class Top_families(MudObject):
