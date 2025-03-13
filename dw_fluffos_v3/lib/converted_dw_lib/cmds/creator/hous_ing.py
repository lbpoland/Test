# Generated from /mnt/home2/test/Test/dw_fluffos_v3/lib/cmds/creator/hous_ing.c (2003 FluffOS v3) for Forgotten Realms MUD
# Date: 2025-03-12 12:51:30
from typing import Dict, List, Optional, Any
from ..driver import MudObject, Player, driver
from ..driver import MudObject, Player, driver
import asyncio

    def do_remove(self, house: str) -> int:
            house = get_file(house)
            if(!HOUSING.query_house(house))
            return notify_fail("No such house.\n")
            HOUSING.remove_house(house)
            write("House removed.\n")
            return 1


    def do_add(self, house: str, region: str, rented: int, address: str) -> int:
            object ob
            house = get_file(house)
            if(house == "")
            return notify_fail("House does not exist.\n")
            load_object(house)
            ob = find_object(house)
            if(!ob || !function_exists("query_owner", ob)) {
            add_failed_mess("The file " + house + " is not a player house.\n")
            return 0


    def do_modify(self, house: str, region: str, rented: int, address: str) -> int:
            string *rooms
            house = get_file(house)
            if(house == "")
            return notify_fail("House does not exist.\n")
            if(!HOUSING.query_house(house))
            return notify_fail("That house is not registered.\n")
            rooms = HOUSING.query_rooms(house) - [house]
            HOUSING.modify_house(house, rooms, address, region, rented)
            write("House modified.\n")
            return 1


    def add_room(self, house: str, room: str) -> int:
            string *files, file
            object ob
            int added
            house = get_file(house)
            if(!HOUSING.query_house(house)) {
            return notify_fail("No such house.\n")


    def remove_room(self, house: str, room: str) -> int:
            house = get_file(house)
            if(!HOUSING.query_house(house))
            return notify_fail("No such house.\n")
            if(!HOUSING.remove_rooms(house, [room]))
            return notify_fail("Error removing room.\n")
            write("Room removed.\n")
            return 1


    def do_owner(self, house: str, owner: str) -> int:
            if(owner == "none")
            owner = "For Sale"
            if(owner != "For Sale" && owner != "Under Offer" &&
            !PLAYER_HANDLER.test_user(owner))
            return notify_fail("No such user " + owner + ".\n")
            house = get_file(house)
            if(!HOUSING.set_owner(house, owner))
            return notify_fail("Error changing owner.\n")
            write("Owner set to " + owner + ".\n")
            return 1


    def do_list(self, search: str) -> int:
            string house
            string str
            string tmp
            int num, negative
            debug_printf("search: %s", search)
            if(search) {
            house = get_file(search)
            if(HOUSING.query_house(house)) {
            printf("House: %s\n  Owner: %s\n  Address: %s\n  Region: %s\n  "
            "Type: %s\n  Value: %d\n  Rooms: %s\n",
            house,
            HOUSING.query_owner(house),
            HOUSING.query_address(house),
            HOUSING.query_region(house),
            (HOUSING.query_type(house) ? "Rented" : "Owned"),
            HOUSING.query_value(house),
            implode(HOUSING.query_rooms(house), ", "))
            return 1


    def do_sell(self, house: str) -> int:
            house = get_file(house)
            if (!HOUSING.set_for_sale(house)) {
            add_failed_mess("Unable to set the house " + house + " up for sale.\n")
            return 0


    def do_list_address(self, search: str) -> int:
            string house
            string str
            string tmp
            int num
            int negative
            str = ""
            if(search && strlen(search) > 4 && search[0..3] == "not ") {
            search = search[4..]
            negative = 1



class Hous_ing(MudObject):
