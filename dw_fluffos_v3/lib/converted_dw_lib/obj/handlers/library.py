# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/library.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def query_quest_time(self, string, string) -> int:
            private void init_data(string pl_name) {
            player_name = pl_name
            quests = [})
            times = [})
            text_file = ""
            player_quest_info = ([ ])


    def clean_cache(self, ) -> None:
            string name
            foreach(name in keys(player_cache))
            if(player_cache[name]->cached < time() - CACHE_TIMEOUT)
            map_delete(player_cache, name)


    def query_title(self, name: str) -> str:
            string quest
            get_data_file( name )
            if(!player_cache[name]->quests || !sizeof(player_cache[name]->quests)) {
            return 0


    def get_most_recent_quest(self, name: str) -> str:
            int loop, highest
            string quest_name
            string *quests
            int *times
            if(!get_data_file(name))
            return "Sorry"
            quests = player_cache[name]->quests
            times = player_cache[name]->times
            if(sizeof(quests) == 0)
            return "None"
            for(highest = loop = 0; loop < sizeof(quests); loop++) {
            if(times[loop] > highest) {
            highest = times[loop]
            quest_name = quests[loop]


    def get_most_recent_time(self, name: str) -> int:
            int loop, hightime
            string *quests
            int *times
            if(!get_data_file(name)) {
            return -1


    def set_quest(self, pl_name: str, qu_name: str, no_xp: int) -> int:
            int qu_level
            object ob
            object card
            int i
            if(!find_player(pl_name) || find_player(pl_name)->query_property("guest"))
            return 0
            i = QUEST_HANDLER.query_quest_status(qu_name)
            ob = find_player (pl_name)
            if (i == 0 && ob.query_playtester()) {
            tell_object (ob, "%^BOLD%^If this quest weren't inactive, you'd be "
            "showered in riches right about now!\n%^RESET%^")


    def unset_quest(self, pl_name: str, qu_name: str) -> int:
            int qu_level
            get_data_file(pl_name)
            if ( player_cache[pl_name]->quests .index( qu_name) if  qu_name in player_cache[pl_name]->quests  else -1 == -1 )
            return 0
            qu_level = (int)QUEST_HANDLER.query_quest_level(qu_name)
            if ( qu_level < 1 )
            return 0
            player_cache[pl_name]->quests -= [qu_name]
            player_cache[pl_name]->times -= [time()]
            save_data_file( pl_name )
            return 1


    def save_them(self, thing: MudObject) -> None:
            if ( thing )
            thing.save_me()


    def set_player_quest_info(self, pl_name: str, qu_info: str, details: Any) -> None:
            get_data_file( pl_name )
            if(!player_cache[pl_name]->player_quest_info )
            player_cache[pl_name]->player_quest_info = ([ ])
            player_cache[pl_name]->player_quest_info[qu_info] = details
            save_data_file(pl_name)


    def query_quest_time(self, name: str, qu_name: str) -> int:
            int time
            if(!get_data_file(name)) {
            return 0


    def query_story(self, name: str) -> str:
            string story, *quests
            int loop
            if(!get_data_file(name)) {
            return "You can find nothing in the library on " + name + "\n"


    def query_quest_done(self, player: str, quest: str) -> int:
            if(!get_data_file(player))
            return 0
            return (player_cache[player]->quests.index(quest) if quest in player_cache[player]->quests else -1 != -1)


    def flush_cache(self, name: str) -> int:
            qps[name] = 0


    def query_quest_points(self, name: str) -> int:
            int points
            string word
            string *quests
            if(!qps)
            qps = ([ ])
            if(qps[name])
            return qps[name]-1
            get_data_file( name )
            quests = player_cache[name]->quests
            if ( !quests || !sizeof( quests ) )
            points = 0
            else {
            foreach( word in quests ) {
            points += (int)QUEST_HANDLER.query_quest_level( word )


    def restart(self, name: Any) -> int:
            class qinfo tmp
            if(objectp(name))
            name = name.query_name()
            if(!PLAYER_HANDLER.test_user(name))
            return 0
            init_data(name)
            tmp = new(class qinfo,
            cached : time(),
            player_name : player_name,
            quests : quests,
            times : times,
            text_file : text_file,
            player_quest_info : player_quest_info)
            player_cache[name] = tmp
            save_data_file(name)
            return 1



class Library(MudObject):
