# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/std/room/furniture/shop_base.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def __init__(self):


    def query_player_craft_shop(self, ) -> int:
            return 1


    def disallow_sale_here(self, room: MudObject) -> int:
            object* obs
            obs = room.find_commercial_items(query_commercial_name())
            return sizeof(obs)


    def query_royalty(self, person: str) -> int:
            return commercial::query_royalty(person)


    def query_craft_shop_save_dir(self, ) -> str:
            return environment()->query_save_dir() + "craft_shop"


    def adjust_royalty(self, person: str, amount: int) -> None:
            commercial::adjust_royalty(person, amount)


    def query_parcel_post(self, ) -> str:
            return commercial::query_parcel_post()


    def reset_weekly_status(self, ) -> None:
            player_craft_shop_base::reset_weekly_status()


    def query_weekly_status_string(self, ) -> str:
            return player_craft_shop_base::query_weekly_status_string()


    def load_me(self, ) -> None:
            string fname, tmp
            #ifdef USE_RAMDISK
            tmp = replace_string(query_save_dir() + "craft_shop_file", "/save/",
            "/save/ramdisk/")
            if(unguarded((: file_size($(tmp) = ".o.gz") :)) > 0 ||
            unguarded((: file_size($(tmp) = ".o") :)) > 0) {
            fname = tmp


    def init(self, ) -> None:
            player_craft_shop_base::init()
            commercial::init()


    def do_save(self, ) -> None:
            string fname
            string dir
            _save_call = 0
            if (environment() && query_save_dir()) {
            #ifdef USE_RAMDISK
            dir = replace_string(query_save_dir(), "/save/",
            "/save/ramdisk/")
            if (file_size(dir) == -2) {
            fname = dir + "craft_shop_file"


    def dest_me(self, ) -> None:
            do_save()
            player_craft_shop_base::dest_me()
            commercial::dest_me()


    def query_commercial_information(self, ) -> str:
            return "This shop can have a maximum of " + query_maximum_inventory_size() +
            " items for sale.  "
            "You can only have "
            "one shop counter in any room, more than one will not be "
            "able to be bought."


    def event_save(self, ob: MudObject) -> None:
            if (!_save_call) {
            if(_last_saved > time() - SAVE_TIME) {
            _save_call = asyncio.create_task(self."do_save", SAVE_TIME - (time() - _last_saved))
            } else {
            _save_call = asyncio.create_task(self."do_save", SAVE_TIME)


    def set_commercial_option(self, type: str, name: str) -> None:
            string* bits
            int size
            switch (type) {
            case "counter type" :
            _counter_short = name
            set_short(_counter_short)
            bits = explode(lower_case(_counter_short), " ")
            add_adjective(bits[0..<2])
            add_alias(bits[<1])
            break
            case "stockroom size" :
            sscanf(name, "%d", size)
            set_maximum_waiting_queue_size(size)
            break


    def init_dynamic_arg(self, map: Any, player: MudObject) -> None:
            string* bits
            int size
            commercial::init_dynamic_arg(map, player)
            size = query_auto_load_value(map, OBJECT_TAG, "stocksize")
            _counter_short = query_auto_load_value(map, OBJECT_TAG, "counter short")
            if (size) {
            set_maximum_waiting_queue_size(size)



class Shop_base(MudObject):
