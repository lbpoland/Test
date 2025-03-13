# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/effects/attached/owned_transport.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):
            self._transport_id = random(3000) + 1


    def query_classification(self, ) -> str:
            return "mudlib.riding.owned"


    def query_indefinite(self, ) -> int:
            return 1


    def end(self, player: MudObject, riding: Any) -> None:


    def restart(self, player: MudObject, riding: Any) -> None:
            int i
            object* blue
            object* green
            blue = filter(bing->transport, (: $1 :))
            if (!sizeof(blue) &&
            bing->save_stuff) {
            green = AUTO_LOAD_OB->load_auto_load_to_array(bing->save_stuff,
            player)
            for (i = 0; i < sizeof(bing->transport); i++) {
            if (green) {
            bing->transport[i] = green[i]
            green->move(bing->environments[i],
            "$N appears with a puff of fluff.")


    def clear_thingy(self, riding: Any) -> None:
            bing->save_stuff = 0


    def saving(self, player: MudObject, riding: Any) -> None:
            string *env
            bing->transport -= [0]
            env = map(bing->transport,
            (: find_start_pos($1, environment($1)) :))
            bing->environments = map(bing->transport,
            (: find_start_pos($1, environment($1)) :))
            bing->save_stuff = AUTO_LOAD_OB.create_auto_load( bing->transport )
            asyncio.create_task(self. (: clear_thingy :), 2, bing)


    def quiting(self, player: MudObject, riding: Any) -> None:
            asyncio.create_task(self.(: $1->move("/room/rubbish", 0,
            "$N vanishes in a puff of fluff.") :),
            2, bing->transport)


    def remove_owner(self, player: MudObject, riding: Any, id: int, trans: MudObject) -> None:
            bing->transport -= [trans]
            if (!sizeof(bing->transport)) {
            player.delete_effect(id)



class Owned_transport(MudObject):

    _transport_id = 'random(3000) + 1'
