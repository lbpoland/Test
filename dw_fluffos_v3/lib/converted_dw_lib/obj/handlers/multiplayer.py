# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/obj/handlers/multiplayer.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self.int changed = 0
            self.denied_parcels = []
            self.allowed = ([ ])


    def add_git(self, git: str) -> int:
            PLAYERINFO_HANDLER.add_entry(this_player(), git, "multiplay",
            "Caught multiplaying.\n")
            return 1


    def add_allowed(self, user: str, other: str) -> int:
            int oldsize, changed
            if (!(PLAYER_HANDLER.test_user(user) && PLAYER_HANDLER.test_user(other))) {
            return 0


    def delete_allowed(self, user: str) -> int:
            if(PLAYERINFO_HANDLER.query_alt_of(user))
            user = PLAYERINFO_HANDLER.query_alt_of(user)
            if (undefinedp(allowed[user]))
            return 0
            map_delete(allowed, user)
            asyncio.create_task(self.(: save_me :), 1)
            PLAYERINFO_HANDLER.add_entry(this_player(), user, "multiplay",
            "Deleted from multiplayer handler "
            "(allowed).\n")
            return 1


    def add_denied_parcel(self, user: str) -> int:
            if (!"/secure/master"->query_lord(geteuid(previous_object())) &&
            !"/d/liaison/master"->query_deputy(geteuid(previous_object()))) {
            write("You do not have permission to add a user to this list.\n")
            return 0


    def remove_denied_parcel(self, user: str) -> int:
            if (!"/secure/master"->query_lord(geteuid(previous_object())) &&
            !"/d/liaison/master"->query_deputy(geteuid(previous_object()))) {
            write("You do not have permission to remove a user to this list.\n")
            return 0


    def member_denied_parcel(self, user: str) -> int:
            if (denied_parcels.index(user) if user in denied_parcels else -1 == -1)
            return 0
            return 1


    def query_name(self, ) -> str:
            return "Multiplayer handler"


    def record_object(self, action: str, player: MudObject, item: MudObject) -> None:
            mixed stuff
            stuff = item.query_property("dropped")
            if(sizeof(stuff) && player.query_name() != stuff[0])
            stuff = [player.query_name(), query_ip_number(player), time(),
            stuff[0]]
            else
            stuff = [player.query_name(), query_ip_number(player), time()]
            item.add_property("dropped", stuff, 1800)


    def check_multiplayers(self, action: str, player: MudObject, item: MudObject) -> int:
            mixed stuff
            string direction, verb, res, is
            if(objectp(player) && !interactive(player))
            return 0
            stuff = item.query_property("dropped")
            if(!stuff)
            return 0
            is = ""
            switch(action) {
            case "get":
            verb = " got "
            direction = " from "
            break
            case "give":
            verb = " was given "
            direction = " by "
            is = "is "
            break
            case "slip":
            verb = " was slipped "
            direction = " by "
            is = "is "
            break
            case "palm":
            verb = " palmed "
            direction = " from "
            break
            case "plant":
            verb = " planted "
            direction = " on "
            is = "is "
            break
            case "recover":
            verb = " recovered "
            direction = " from "
            break



class Multiplayer(MudObject):

    int changed = 0

    denied_parcels = '[]'

    allowed = '([ ])'
